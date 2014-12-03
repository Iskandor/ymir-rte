/* 
 * File:   RecSOM.cpp
 * Author: Matej Pechac
 * 
 * Created on April 6, 2013, 3:27 PM
 */

#include "RecSOM.h"
#include "main.h"
#include <cstring>
#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;

RecSOM::RecSOM(int input_dim, int map_dim_x, int map_dim_y) {
  this->input_dim = input_dim;
  this->input_layer = new float[input_dim];
  
  this->map_dim_x = map_dim_x;
  this->map_dim_y = map_dim_y;
  
  this->context_layer = new float[map_dim_x*map_dim_y];
  this->output_layer = new float[map_dim_x*map_dim_y];
  memset(this->context_layer, 0, sizeof(float));
  this->map_layer = new Neuron*[map_dim_x*map_dim_y];
  
  for(int i = 0; i < map_dim_y; i++) {
    for(int j = 0; j < map_dim_x; j++) {
      this->map_layer[i*map_dim_y+j] = new Neuron(input_dim, map_dim_x*map_dim_y, j, i);
    }
  }
  
  this->sigma0 = sqrt((float)map_dim_x);
}

RecSOM::RecSOM(const RecSOM& orig) {
}

RecSOM::~RecSOM() {
  delete map_layer;
  //delete input_layer;
  delete context_layer;
  delete output_layer;
}

void RecSOM::insert_dataset(CDataSet* data) {
	trn_dataset = data;
}

void RecSOM::train(int epochs, float alpha, float beta, float gama, int dec_fn, bool loging) {
	list<sSequence>                 *trn_data = trn_dataset->get_trn_data();
	list<sSequence>::iterator       seq_it;
  list< vector<float> >::iterator	sam_it;
	float	qerr;

	lambda = (float)epochs / log((float)max(map_dim_x, map_dim_y)/2.0f);
	eta = (float)epochs;

	gama0 = gama;
	this->alpha = alpha;
  this->beta = beta;

	ofstream qerr_file;

  if (loging) {
    qerr_file.open ("recsom_qerr.log");
  }

  for(int i = 0; i < epochs; i++) {
    qerr = 0;
    switch(dec_fn) {
      case EXP:
        gama_decay_exp(i);
        break;
      case LIN:
        gama_decay_lin(i);
        break;
    }
		
    sigma_decay(i);
    
    for (seq_it=trn_data->begin(); seq_it != trn_data->end(); seq_it++) {
      sSequence sample = *seq_it;

      memset(context_layer, 0, sizeof(float));
      
      for (sam_it = sample.seq.begin(); sam_it != sample.seq.end(); sam_it++) {
        qerr += train_one_sample(*sam_it, GAUSSIAN);
      }
    }
    utils.calc_wd(map_dim_x*map_dim_y);
    cout << i << ". Qerr = " << qerr  << " WD = " << utils.get_wd() << endl;
    if (loging) {
      qerr_file << i << " " << qerr << endl;
    }
    utils.reset_wd();
	}
  
	utils.update_qerr(qerr);

  if (loging) {
    qerr_file.close();
  }
}

float RecSOM::train_one_sample(vector<float> sample, int nf) {
	Neuron*		w     = NULL;
  float     qerr  = 0.0;

	input_layer = &sample[0];

	w = activate_find_winner(output_layer);
	qerr = w->recursive_distance(alpha, beta, input_layer, context_layer);

	for(int i = 0; i < map_dim_x*map_dim_y; i++) {
		map_layer[i]->update_weights(gama, w, input_layer, context_layer, sigma, nf);
	}
  
  update_context(output_layer);

	return qerr;
}

Neuron* RecSOM::activate_find_winner(float* layer) {
	int		mini = 0;
	float	mind = -1;

	for (int i = 1; i < map_dim_x*map_dim_y; i++) {
		float d = map_layer[i]->recursive_distance(alpha, beta, input_layer, context_layer);
    layer[i] = exp(-d);
		if (mind > d || mind == -1) {
			mini = i;
			mind = d;
		}
	}
  
  utils.update_wd(mini);

	return map_layer[mini];
}

void RecSOM::update_context(float* layer) {
	for (int i = 1; i < map_dim_x*map_dim_y; i++) {
		context_layer[i] = layer[i];
	}
}

void RecSOM::gama_decay_exp(int t) {
  gama = gama0 * exp(-(float)t / eta);
}

void RecSOM::gama_decay_lin(int t) {
  gama = gama0 * ((float)(eta-t) / eta);
}

void RecSOM::sigma_decay(int t) {
  sigma = sigma0 * exp(-(float)t / lambda);
}

void RecSOM::save_to_file3(const char* file_1, const char* file_2, int n_views, int mode) {
	list<sSequence>*                trn_data = trn_dataset->get_trn_data();
	list<sSequence>::iterator	seq_it;
  list< vector<float> >::iterator   sam_it;
  char tmp[20+1];
  char line[100+1];

	ofstream myfile_1, myfile_2;
	myfile_1.open (file_1);
  myfile_2.open (file_2);


  double *map_magnitude = new double[map_dim_y*map_dim_x*N_GRASPS];
  double *map_magnitude_view = new double[map_dim_y*map_dim_x*n_views];
  double *map_normal_dist = new double[map_dim_y*map_dim_x];
  Neuron* w = NULL;

  memset(map_magnitude, 0, sizeof(double)*map_dim_y*map_dim_x*N_GRASPS);
  memset(map_magnitude_view, 0, sizeof(double)*map_dim_y*map_dim_x*n_views);
  memset(map_normal_dist, 0, sizeof(double)*map_dim_y*map_dim_x);


	for (seq_it=trn_data->begin(); seq_it != trn_data->end(); seq_it++) {
		sSequence sample = *seq_it;
    for (sam_it = sample.seq.begin(); sam_it != sample.seq.end(); sam_it++) {
      vector<float> input = *sam_it;
      input_layer = &input[0];
      w = activate_find_winner(output_layer);
      for (int i = 0; i < map_dim_y; i++) {
        for (int j = 0; j < map_dim_x; j++) {
            double dist = map_layer[i*map_dim_x+j]->recursive_distance(alpha, beta, input_layer, context_layer);
            double val = 0.0;
            
            if (mode == LIN) {
              val = dist;
            }
            if (mode == EXP) {
              val = exp(-dist);
            }
            
            map_magnitude[i*map_dim_x*N_GRASPS+j*N_GRASPS+sample.seq_class] += val;
            if (n_views > 0) {
              map_magnitude_view[i*map_dim_x*n_views+j*n_views+sample.seq_view] += val;
            }
            map_normal_dist[i*map_dim_x+j] += val;
        }
      }
      update_context(output_layer);
    }
	}
  sprintf(tmp, "#%i %i", map_dim_x, map_dim_y);
  myfile_1 << tmp << endl;
  myfile_2 << tmp << endl;
	for (int i = 0; i < this->map_dim_y; i++) {
		for (int j = 0; j < this->map_dim_x; j++) {
      line[0] = '\0';
			for (int g = 0; g < N_GRASPS; g++) {
        map_magnitude[i*map_dim_x*N_GRASPS+j*N_GRASPS+g] /= map_normal_dist[i*map_dim_x+j];
        if (mode == LIN) {
          map_magnitude[i*map_dim_x*N_GRASPS+j*N_GRASPS+g] = 1 - map_magnitude[i*map_dim_x*N_GRASPS+j*N_GRASPS+g];
        }
        sprintf(tmp, "%f ", map_magnitude[i*map_dim_x*N_GRASPS+j*N_GRASPS+g]);
        strcat(line, tmp);
      }
      myfile_1 << line << endl;
      line[0] = '\0';
      for(int v = 0; v < n_views; v++) {
        map_magnitude_view[i*map_dim_x*n_views+j*n_views+v] /= map_normal_dist[i*map_dim_x+j];
        if (mode == LIN) {
          map_magnitude_view[i*map_dim_x*n_views+j*n_views+v] = 1 - map_magnitude_view[i*map_dim_x*n_views+j*n_views+v];
        }
        sprintf(tmp, "%f ", map_magnitude_view[i*map_dim_x*n_views+j*n_views+v]);
        strcat(line, tmp);
      }
      myfile_2 << line << endl;
    }
	}
	myfile_1.close();
  myfile_2.close();
}

