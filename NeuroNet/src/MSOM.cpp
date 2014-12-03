#include "MSOM.h"
#include "Neuron.h"
#include "main.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <math.h>

using namespace std;


MSOM::MSOM(int input_dim, int map_dim_x, int map_dim_y)
{
	map_layer		= new Neuron*[map_dim_x*map_dim_y];
	input_layer		= new float[input_dim];
	context_weight	= new float[input_dim];
  output = new float[map_dim_x*map_dim_y];


	this->map_dim_x = map_dim_x;
	this->map_dim_y = map_dim_y;
	this->input_dim = input_dim;
	
  reset_context();

	for(int i = 0; i < map_dim_y; i++) {
		for(int j = 0; j < map_dim_x; j++) {
			map_layer[i*map_dim_x+j] = new Neuron(input_dim, j, i);
		}
	}

	sigma0 = sqrt((float)map_dim_x);

	max_entropy = 0;
}


MSOM::~MSOM(void)
{
	for(int i = 0; i < map_dim_y; i++) {
		for(int j = 0; j < map_dim_x; j++) {
			delete map_layer[i*map_dim_x+j];
		}
	}
	delete[] map_layer;
  // tu to vzdy drbne na pamatovku!
	//delete[] input_layer;
	delete[] context_weight;

	//delete entropy_histogram;
}

void MSOM::insert_dataset(CDataSet* data) {
	trn_dataset = data;
}

void MSOM::init_training(int epochs, float alpha, float beta, float gama, float dalpha) {
	lambda = (float)epochs / log((float)max(map_dim_x, map_dim_y)/2.0f);
	eta = (float)epochs;
	gama0 = gama;
	this->alpha = alpha;
  this->beta = beta;
	this->dalpha = dalpha;
}

void MSOM::train(int epochs, sMSOMTrnConfig config, bool loging) {
	list<sSequence>                 *trn_data = trn_dataset->get_trn_data();
	list<sSequence>::iterator       seq_it;
  list< vector<float> >::iterator	sam_it;
	float	qerr;

	entropy_histogram = new vector<int>(map_dim_x * map_dim_y);

  init_training(epochs, config.alpha, config.beta, config.gama, config.dalpha);


	ofstream qerr_file;
  ofstream wd_file;
  ofstream entropy_file;

  if (loging) {
      qerr_file.open ("msom_qerr.log");
      wd_file.open("msom_wd.log");
      entropy_file.open("msom_entropy.log");
  }

  for(int i = 0; i < epochs; i++) {
    bool _entropy = (i % 10 == 0);

    qerr = 0;
    param_decay(i, config.dec_fn);
    winner_set.clear();
    for (seq_it=trn_data->begin(); seq_it != trn_data->end(); seq_it++) {
      sSequence sample = *seq_it;

      reset_context();
      for (sam_it = sample.seq.begin(); sam_it != sample.seq.end(); sam_it++) {
        qerr += train_one_sample(*sam_it, GAUSSIAN, 0);
      }
    }
    if (_entropy) {
      cout << i << ". Qerr = " << qerr << " Alpha = " << this->alpha << " WD = " << winner_differentiation() << " Entropy = " << entropy() << endl;
      //entropy_drive();
      if (loging) {
          entropy_file << i << " " << entropy() << endl;
      }
      entropy_histogram->clear();
      entropy_histogram->resize(trn_dataset->get_length());
    }
    else {
      cout << i << ". Qerr = " << qerr << " Alpha = " << this->alpha << " WD = " << winner_differentiation() << endl;
    }
    if (loging) {
        qerr_file << i << " " << qerr << endl;
        wd_file << i << " " << winner_differentiation() << endl;
    }
	}

  /*
 	ofstream myfile;
	myfile.open ("output.txt");
  for (seq_it=trn_data->begin(); seq_it != trn_data->end(); seq_it++) {
    sSequence sample = *seq_it;

    for (sam_it = sample.seq.begin(); sam_it != sample.seq.end(); sam_it++) {
      write_output(myfile, *sam_it);
    }
    myfile << "& " << sample.seq_class; //<< " " << sample.seq_view << endl;
  }
  myfile.close();
   * */
  
	this->qerr = qerr;

  if (loging) {
      qerr_file.close();
      wd_file.close();
      entropy_file.close();
  }
}

void MSOM::write_output(ofstream& myfile, vector<float> *activation) {

  for (int i = 0; i < map_dim_y*map_dim_x; i++) {
      myfile << activation->at(i) << " ";
  }
  myfile << endl;
}

void MSOM::activate(vector<float> sample, vector<float>* output, int mode) {
	Neuron*		w = NULL;
  float     d;

	input_layer = &sample[0];

	w = find_winner(mode);
  
  output->clear();

	for(int i = 0; i < map_dim_x*map_dim_y; i++) {
		d = map_layer[i]->recursive_distance(alpha, input_layer, context_weight);
    if (mode == LIN) output->push_back(d);
    if (mode == EXP) output->push_back(exp(-d));
	}

	update_context(w, beta);  
}

float* MSOM::activate(vector<float> sample, int mode) {
	Neuron*		w = NULL;

	input_layer = &sample[0];

	w = find_winner(mode);
	update_context(w, beta);
  
  return output;
}

void MSOM::reverse_activate(float* output, vector<float> *sample) {
  Neuron* w   = NULL;
  double  w_a = 0.0;
  
  for(int i = 0; i < map_dim_x*map_dim_y; i++) {
    if (w_a < output[i]) {
      w_a = output[i];
      w = map_layer[i];
    } 
  }
  
  for(int i = 0; i < w->get_dim(WEIGHT); i++) {
    sample->at(i) = w->get_weight(WEIGHT)[i];
  }
}

float MSOM::train_one_sample(vector<float> sample, int nf, int a_mode) {
	Neuron*		w = NULL;

	input_layer = &sample[0];

	w = find_winner(a_mode);

	float qerr = w->recursive_distance(alpha, input_layer, context_weight);

	for(int i = 0; i < map_dim_x*map_dim_y; i++) {
		map_layer[i]->update_weights(gama, w, input_layer, context_weight, sigma, nf);
	}

	update_context(w, beta);

	return qerr;
}

Neuron* MSOM::find_winner(int mode) {
	int		mini = 0;
	float	mind = -1;

	for (int i = 0; i < map_dim_x*map_dim_y; i++) {
		float i_d = map_layer[i]->recursive_distance(alpha, input_layer, context_weight);
    switch(mode) {
      case EXP: output[i] = exp(-i_d); break;
      case LIN: output[i] = i_d; break;
      default:
        output[i] = 0.0f;
    }
		if (mind > i_d || mind == -1) {
			mini = i;
			mind = i_d;
		}
	}

	//if (entropy) entropy_histogram->at(mini) = 1;
  //entropy_histogram->at(mini) = 1;
	//winner_set.insert(mini);

	return map_layer[mini];
}

void MSOM::update_context(Neuron* winner, float beta) {
	for(int i = 0; i < input_dim; i++) {
		context_weight[i] = (1 - beta) * winner->get_weight(WEIGHT)[i] + beta * winner->get_weight(CONTEXT)[i]; 
	}
}

void MSOM::reset_context() {
  for(int i = 0; i < input_dim; i++) {
    context_weight[i] = 0;
  }  
}

void MSOM::save_to_file(const char* file) {
	ofstream myfile;
	myfile.open (file);

	list<sSequence>*                  trn_data = trn_dataset->get_trn_data();
	list<sSequence>::iterator         seq_it;
  list< vector<float> >::iterator   sam_it;
  Neuron* w = NULL;

	for (seq_it=trn_data->begin(); seq_it != trn_data->end(); seq_it++) {
		sSequence sample = *seq_it;
    for (sam_it = sample.seq.begin(); sam_it != sample.seq.end(); sam_it++) {
      vector<float> input = *sam_it;
      input_layer = &input[0];
      w = this->find_winner(0);
      update_context(w, beta);
    }
	}

	for (int i = 0; i < this->map_dim_y; i++) {
		char row[1000+1] = "";
		for (int j = 0; j < this->map_dim_x; j++) {
			char tmp[100+1];
      float w = *map_layer[i*map_dim_x+j]->get_weight(WEIGHT);
      float c = *map_layer[i*map_dim_x+j]->get_weight(CONTEXT);
			sprintf(tmp, "%.2f ", w);
			strcat(row,  tmp);
      //myfile << tmp << endl;
		}
		myfile << row << endl;
	}
	myfile.close();
}

void MSOM::save_to_file2(const char* file_1, const char* file_2, int n_views) {
	list<sSequence>*                trn_data = trn_dataset->get_trn_data();
	list<sSequence>::iterator         seq_it;
  list< vector<float> >::iterator   sam_it;
  char tmp[100+1];
  
	ofstream myfile_1, myfile_2;
	myfile_1.open (file_1);
  myfile_2.open (file_2);

  int *map_magnitude = new int[map_dim_y*map_dim_x*N_GRASPS];
  int *map_magnitude_view = new int[map_dim_y*map_dim_x*n_views];
  Neuron* w = NULL;

  memset(map_magnitude, 0, sizeof(int)*map_dim_y*map_dim_x*N_GRASPS);
  if (n_views > 0) {
    memset(map_magnitude_view, 0, sizeof(int)*map_dim_y*map_dim_x*n_views);
  }

	for (seq_it=trn_data->begin(); seq_it != trn_data->end(); seq_it++) {
		sSequence sample = *seq_it;
    for (sam_it = sample.seq.begin(); sam_it != sample.seq.end(); sam_it++) {
      vector<float> input = *sam_it;
      input_layer = &input[0];
      w = this->find_winner(0);
      map_magnitude[w->get_y()*map_dim_x*N_GRASPS+w->get_x()*N_GRASPS+sample.seq_class]++;
      if (n_views > 0) {
        map_magnitude_view[w->get_y()*map_dim_x*n_views+w->get_x()*n_views+sample.seq_view]++;
      }
      update_context(w, beta);
    }
	}

  sprintf(tmp, "#%i %i", map_dim_x, map_dim_y);
  myfile_1 << tmp << endl;
  myfile_2 << tmp << endl;
	for (int i = 0; i < this->map_dim_y; i++) {
		char row[1000+1] = "";
		for (int j = 0; j < this->map_dim_x; j++) {
			sprintf(tmp, "%i %i %i", map_magnitude[i*map_dim_x*N_GRASPS+j*N_GRASPS+0], map_magnitude[i*map_dim_x*N_GRASPS+j*N_GRASPS+1], map_magnitude[i*map_dim_x*N_GRASPS+j*N_GRASPS+2]);
			//strcat(row,  tmp);
      myfile_1 << tmp << endl;
      if (n_views > 0) {
        sprintf(tmp, "%i %i %i %i", map_magnitude_view[i*map_dim_x*n_views+j*n_views+0], map_magnitude_view[i*map_dim_x*n_views+j*n_views+1], map_magnitude_view[i*map_dim_x*n_views+j*n_views+2], map_magnitude_view[i*map_dim_x*n_views+j*n_views+3]);
      }
      //sprintf(tmp, "%i %i %i", map_magnitude_view[i*map_dim_x*3+j*3+0], map_magnitude_view[i*map_dim_x*3+j*3+1], map_magnitude_view[i*map_dim_x*3+j*3+2]);
      myfile_2 << tmp << endl;
    }
		//myfile << row << endl;
	}
	myfile_1.close();
  myfile_2.close();
}

void MSOM::save_to_file3(const char* file_1, const char* file_2, int n_views, int mode) {
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
      w = find_winner(0);
      for (int i = 0; i < map_dim_y; i++) {
        for (int j = 0; j < map_dim_x; j++) {
            double dist = map_layer[i*map_dim_x+j]->recursive_distance(alpha, input_layer, context_weight);
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
      update_context(w, beta);
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

float* MSOM::get_activation() {
  return output;
}

void MSOM::get_size(int* size) {
  size[0] = map_dim_x;
  size[1] = map_dim_y;
}

void MSOM::test(char* filename, float alpha, float beta) {
	list<sSequence>*                  trn_data = trn_dataset->get_trn_data();
	list<sSequence>::iterator         seq_it;
  list< vector<float> >::iterator   sam_it;

	Neuron *w = NULL;

	ofstream myfile;
	myfile.open (filename);

  int c = 0;
  int class_instance = 0;
  int sequence_length = 0;

	for (seq_it=trn_data->begin(); seq_it != trn_data->end(); seq_it++) {
		sSequence sample = *seq_it;
    sequence_length = 0;
    class_instance++;
    for (sam_it = sample.seq.begin(); sam_it != sample.seq.end(); sam_it++) {
      c = 0;
      sequence_length++;
      vector<float> input = *sam_it;
      input_layer = &input[0];
      w = find_winner(0);
      for (int i = 0; i < map_dim_y; i++) {
        for (int j = 0; j < map_dim_x; j++) {
          myfile << map_layer[i*map_dim_x+j]->recursive_distance(alpha, input_layer, context_weight) << " ";
        }
      }
      update_context(w, beta);
      myfile << endl;
    }
    cout << class_instance << " | " << sequence_length << endl;
    if (c == 0) {
      myfile << "& " << sample.seq_class << " " << sample.seq_view << endl;
    }
    c++;
	}
	myfile.close();
}

void MSOM::param_decay(int epoch, int mode) {
  sigma_decay(epoch);
  gama_decay(epoch, mode);
}

void MSOM::sigma_decay(int t) {
	sigma = sigma0 * exp(-(float)t / lambda);
}

void MSOM::gama_decay(int t, int mode) {
  if (mode == EXP) {
    gama = gama0 * exp(-(float)t / eta);
  }
  if (mode == LIN) {
    gama = gama0 * ((float)(eta-t) / eta);
  }
}

float MSOM::entropy() {
	float sum = 0;

	for(int i = 0; i < map_dim_x*map_dim_y; i++) {
    float p = (float)entropy_histogram->at(i)/(float)trn_dataset->get_length();

		if (p > 0) {
			sum += p * log(p);
		}
	}

	return -sum;
}

void MSOM::entropy_drive() {
	float h = entropy(); 

	if (h > max_entropy && (alpha - dalpha) > 0) {
		alpha -= dalpha;
	}
	if (h < max_entropy  && (alpha + dalpha) < 1) {
		alpha += dalpha;
	}
	max_entropy = h;
}

float MSOM::winner_differentiation() {
	return (float)winner_set.size()/(float)(map_dim_x * map_dim_y) ;
}

float MSOM::qerror() {
	return qerr;
}