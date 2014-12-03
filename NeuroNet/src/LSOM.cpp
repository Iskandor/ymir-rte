/* 
 * File:   LSOM.cpp
 * Author: Matej Pechac
 * 
 * Created on June 11, 2013, 5:58 PM
 */

#include "LSOM.h"

#include <cmath>

LSOM::LSOM(int input_dim, int map_dim_x, int map_dim_y) {
  	map_layer		= new Neuron*[map_dim_x*map_dim_y];
  output_layer  = new float[map_dim_x*map_dim_y];
	input_layer		= new float[input_dim];

	this->map_dim_x = map_dim_x;
	this->map_dim_y = map_dim_y;
	this->input_dim = input_dim;


	for(int i = 0; i < map_dim_y; i++) {
		for(int j = 0; j < map_dim_x; j++) {
			map_layer[i*map_dim_x+j] = new Neuron(input_dim, 0, map_dim_x*map_dim_y, j, i);
		}
	}

	sigma0 = sqrt((float)map_dim_x);
  sigma_l = sqrt((float)map_dim_x);
}

LSOM::LSOM(const LSOM& orig) {
}

LSOM::~LSOM() {
  delete[] map_layer;
}

void LSOM::insert_dataset(CDataSet* data) {
  trn_dataset = data;
}

void LSOM::init_training(int epochs, float gama, float _gama_l, float _alpha) {
	lambda = (float)epochs / log((float)max(map_dim_x, map_dim_y)/2.0f);
	eta = (float)epochs;
	gama0 = gama;
  gama_l = _gama_l;
  alpha = _alpha;
}

void LSOM::train(int epochs, sLSOMTrnConfig config, bool loging) {
	list<sSequence>                 *trn_data = trn_dataset->get_trn_data();
	list<sSequence>::iterator       seq_it;
  list< vector<float> >::iterator	sam_it;
	float	qerr;
  
  init_training(epochs, config.gama, config.gama_l, config.alpha);
  
  for(int i = 0; i < epochs; i++) {
    bool _entropy = (i % 10 == 0);

    qerr = 0;
    param_decay(i, config.dec_fn);

    for (seq_it=trn_data->begin(); seq_it != trn_data->end(); seq_it++) {
      sSequence sample = *seq_it;

      for (sam_it = sample.seq.begin(); sam_it != sample.seq.end(); sam_it++) {
        qerr += train_one_sample(*sam_it, GAUSSIAN, EXP);
      }
    }
    cout << i << ". Qerr = " << qerr << endl;
  }
}

void LSOM::activate(vector<float> sample, vector<float>* output, int mode) {
	Neuron*		w = NULL;
  float     d;
  float     matrix[map_dim_x*map_dim_y];
	input_layer = &sample[0];
  
	w = find_winner(mode);
  
  output->clear();

	for(int i = 0; i < map_dim_x*map_dim_y; i++) {
		d = map_layer[i]->distance(input_layer);
    output->push_back(output_layer[i]);
	}
  
  for(int i = 0; i < map_dim_x*map_dim_y; i++) {
    calc_weight_matrix(i, matrix);
    output_layer[i] += map_layer[i]->activate(output, matrix);
  }
  
  output->clear();
  for(int i = 0; i < map_dim_x*map_dim_y; i++) {
    output->push_back(output_layer[i]);
  }
}

void LSOM::get_activation(vector<float> *output, int mode) {
  double val = 0.0;
  double dist = 0.0;
  
  output->clear();
  
  for (int i = 0; i < map_dim_y; i++) {
    for (int j = 0; j < map_dim_x; j++) {
        dist = map_layer[i*map_dim_x+j]->distance(input_layer);

        if (mode == LIN) {
          val = dist;
        }
        if (mode == EXP) {
          val = exp(-dist);
        }
        output->push_back(val);
    }
  }  
}

void LSOM::get_size(int* size) {
  size[0] = map_dim_x;
  size[1] = map_dim_y;
}


float LSOM::train_one_sample(vector<float> sample, int nf, int a_mode) {
	Neuron*		w = NULL;

	input_layer = &sample[0];

	w = find_winner(a_mode);

	float qerr = w->distance(input_layer);

	for(int i = 0; i < map_dim_x*map_dim_y; i++) {
		map_layer[i]->update_weights(gama, w, input_layer, sigma, nf);
	}
  
	for(int i = 0; i < map_dim_x*map_dim_y; i++) {
		map_layer[i]->update_lateral_weights(gama_l, map_layer, output_layer, sigma_l, nf, alpha);
	}

	return qerr;
}

Neuron* LSOM::find_winner(int mode) {
	int		mini = 0;
	float	mind = -1;
  
	for (int i = 0; i < map_dim_x*map_dim_y; i++) {
		float i_d = map_layer[i]->distance(input_layer);
    
    switch(mode) {
      case EXP: output_layer[i] = exp(-i_d); break;
      case LIN: output_layer[i] = i_d; break;
      default:
        output_layer[i] = 0.0f;
    }
    
		if (mind > i_d || mind == -1) {
			mini = i;
			mind = i_d;
		}
	}

	return map_layer[mini];
}

void  LSOM::calc_weight_matrix(int i, float* matrix) {
  for(int j = 0; j < map_dim_x * map_dim_y; j++) {
    matrix[j] = map_layer[j]->get_weight(LATERAL)[i];
  }
}

void LSOM::param_decay(int epoch, int mode) {
  sigma_decay(epoch);
  gama_decay(epoch, mode);
}

void LSOM::sigma_decay(int t) {
	sigma = sigma0 * exp(-(float)t / lambda);
}

void LSOM::gama_decay(int t, int mode) {
  if (mode == EXP) {
    gama = gama0 * exp(-(float)t / eta);
  }
  if (mode == LIN) {
    gama = gama0 * ((float)(eta-t) / eta);
  }
}

void LSOM::write_output(ofstream& myfile, vector<float> *activation) {

  for (int i = 0; i < map_dim_y*map_dim_x; i++) {
      myfile << activation->at(i) << " ";
  }
  myfile << endl;
}


