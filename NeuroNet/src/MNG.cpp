#include "MNG.h"
#include "Neuron.h"
#include "DataSet.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <math.h>

using namespace std;


MNG::MNG(int input_dim, int map_dim_x, int map_dim_y)
{
	map_layer		= new Neuron*[map_dim_x*map_dim_y];
	rnk_matrix		= new int[map_dim_x*map_dim_y];
	input_layer		= new float[input_dim];
	context_weight	= new float[input_dim];
	//entropy_histogram = new int[map_dim_x*map_dim_y];

	memset(rnk_matrix, 0, sizeof(int)*map_dim_x*map_dim_y);
	

	this->map_dim_x = map_dim_x;
	this->map_dim_y = map_dim_y;
	this->input_dim = input_dim;
	

	for(int i = 0; i < input_dim; i++) {
		context_weight[i] = 0;
	}

	for(int i = 0; i < map_dim_y; i++) {
		for(int j = 0; j < map_dim_x; j++) {
			map_layer[i*map_dim_x+j] = new Neuron(input_dim, i*map_dim_x+j);
		}
	}

	sigma0 = sqrt((float)map_dim_x);

	max_entropy = 0;
}


MNG::~MNG(void)
{
	for(int i = 0; i < map_dim_y; i++) {
		for(int j = 0; j < map_dim_x; j++) {
			delete map_layer[i*map_dim_x+j];
		}
	}
	delete[] map_layer;
	//delete[] input_layer;
	delete[] context_weight;

	delete entropy_histogram;
}

void MNG::insert_dataset(CDataSet* data) {
	trn_dataset = data;
}

void MNG::train(int epochs, float alpha, float beta, float gama, float dalpha, int dec_fn, bool loging) {
	list<sSequence>                 *trn_data = trn_dataset->get_trn_data();
	list<sSequence>::iterator	seq_it;
        list< vector<float> >::iterator	sam_it;
	float	qerr;

	entropy_histogram = new vector<int>(trn_dataset->get_size());

	lambda = (float)epochs / log((float)max(map_dim_x, map_dim_y)/2.0f);
	eta = (float)epochs;

	gama0 = gama;
	this->alpha = alpha;
	this->dalpha = dalpha;

	ofstream qerr_file;
        ofstream wd_file;
        ofstream entropy_file;

        if (loging) {
            qerr_file.open ("mng_qerr.log");
            wd_file.open("mng_wd.log");
            entropy_file.open("mng_entropy.log");
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

                        for (sam_it = sample.seq.begin(); sam_it != sample.seq.end(); sam_it++) {
                            qerr += train_one_sample(*sam_it, beta);
                        }
		}
		if (i % 10 == 0) {
			cout << i << ". Qerr = " << qerr << " Alpha = " << this->alpha << " WD = " << winner_differentiation() << " Entropy = " << entropy() << endl;

                        if (loging) {
                            entropy_file << i << " " << entropy() << endl;
                        }
			//entropy_drive();
			//memset(entropy_histogram, 0, sizeof(int)*map_dim_x*map_dim_y);
			entropy_histogram->clear();
			entropy_histogram->resize(trn_dataset->get_size());
		}
		else {
			cout << i << ". Qerr = " << qerr << " Alpha = " << this->alpha << " WD = " << winner_differentiation() << endl;
		}
                if (loging) {
                    qerr_file << i << " " << qerr << endl;
                    wd_file << i << " " << winner_differentiation() << endl;
                }
	}

	this->qerr = qerr;

        if (loging) {
            qerr_file.close();
            wd_file.close();
            entropy_file.close();
        }
}

void MNG::test() {
	list<sSequence>*	trn_data = trn_dataset->get_trn_data();
	list<sSequence>::iterator           seq_it;
        list< vector<float> >::iterator     sam_it;

	Neuron *w = NULL;

	ofstream myfile;
	myfile.open ("output.txt");


	for (seq_it=trn_data->begin(); seq_it != trn_data->end(); seq_it++) {
		sSequence sample = *seq_it;
                for (sam_it = sample.seq.begin(); sam_it != sample.seq.end(); sam_it++) {
                    vector<float> input = *sam_it;
                    input_layer = &input[0];
                    w = this->find_winner();
                    myfile << w->get_x() << "," << w->get_y() << " " << w->get_weight(WEIGHT)[0] << "," << w->get_weight(CONTEXT)[0] << endl;
                }
	}
	myfile.close();
}

float MNG::train_one_sample(vector<float> sample, float beta) {
	Neuron*		w = NULL;

	input_layer = &sample[0];

	w = find_winner();

	float qerr = w->recursive_distance(alpha, input_layer, context_weight);

	calc_rnk_matrix(input_layer, context_weight);

	for(int i = 0; i < map_dim_x*map_dim_y; i++) {
		map_layer[i]->update_weights(gama, input_layer, context_weight, (float)rnk_matrix[i], sigma);
	}

	update_context(w, beta);

	//save_to_file("som_t.txt");

	return qerr;
}

void MNG::calc_rnk_matrix(float* xt, float *ct) {
	vector<srank> rnk_vector;

	for(int i = 0; i < map_dim_x*map_dim_y; i++) {
		srank	r;
		r.id = i;
		r.distance = map_layer[i]->recursive_distance(alpha, xt, ct);
		rnk_vector.push_back(r);
	}

	sort(rnk_vector.begin(), rnk_vector.end(), rank_compare);

	for(int i = 0; i < map_dim_x*map_dim_y; i++) {
		rnk_matrix[rnk_vector[i].id] = i;
	}
}

Neuron* MNG::find_winner() {
	int		mini = 0;
	float	mind = -1;

	for (int i = 1; i < map_dim_x*map_dim_y; i++) {
		float i_d = map_layer[i]->recursive_distance(alpha, input_layer, context_weight);
		if (mind > i_d || mind == -1) {
			mini = i;
			mind = i_d;
		}
	}

	entropy_histogram->at(mini) += 1;
	winner_set.insert(mini);

	return map_layer[mini];
}

void MNG::update_context(Neuron* winner, float beta) {
	for(int i = 0; i < input_dim; i++) {
		context_weight[i] = (1 - beta) * winner->get_weight(WEIGHT)[i] + beta * winner->get_weight(CONTEXT)[i]; 
	}
}

void MNG::save_to_file(char* file) {
	ofstream myfile;
	myfile.open (file);

	for (int i = 0; i < this->map_dim_y; i++) {
		char row[1000+1] = "";
		for (int j = 0; j < this->map_dim_x; j++) {
			char tmp[100+1];
			float w = *map_layer[i*map_dim_x+j]->get_weight(WEIGHT);
			sprintf(tmp, "%.2f ", w);
			strcat(row,  tmp);
		}
		myfile << row << endl;
	}
	myfile.close();
}

void MNG::save_to_file2(const char* file_1, const char* file_2) {
	list<sSequence>*                trn_data = trn_dataset->get_trn_data();
	list<sSequence>::iterator	seq_it;
        list< vector<float> >::iterator   sam_it;

	ofstream myfile_1, myfile_2;
	myfile_1.open (file_1);
        myfile_2.open (file_2);


        int *map_magnitude = new int[map_dim_y*map_dim_x*3];
        int *map_magnitude_view = new int[map_dim_y*map_dim_x*4];
        Neuron* w = NULL;

        memset(map_magnitude, 0, sizeof(int)*map_dim_y*map_dim_x*3);
        memset(map_magnitude_view, 0, sizeof(int)*map_dim_y*map_dim_x*4);

	for (seq_it=trn_data->begin(); seq_it != trn_data->end(); seq_it++) {
		sSequence sample = *seq_it;
                for (sam_it = sample.seq.begin(); sam_it != sample.seq.end(); sam_it++) {
                    vector<float> input = *sam_it;
                    input_layer = &input[0];
                    w = this->find_winner();
                    map_magnitude[w->get_y()*map_dim_x*3+w->get_x()*3+sample.seq_class]++;
                    map_magnitude_view[w->get_y()*map_dim_x*4+w->get_x()*4+sample.seq_view]++;
                }
	}

	for (int i = 0; i < this->map_dim_y; i++) {
		char row[1000+1] = "";
		for (int j = 0; j < this->map_dim_x; j++) {
			char tmp[100+1];
			sprintf(tmp, "%i %i %i", map_magnitude[i*map_dim_x*3+j*3+0], map_magnitude[i*map_dim_x*3+j*3+1], map_magnitude[i*map_dim_x*3+j*3+2]);
			//strcat(row,  tmp);
                        myfile_1 << tmp << endl;
                        sprintf(tmp, "%i %i %i %i", map_magnitude_view[i*map_dim_x*3+j*3+0], map_magnitude_view[i*map_dim_x*3+j*3+1], map_magnitude_view[i*map_dim_x*3+j*3+2], map_magnitude_view[i*map_dim_x*3+j*3+3]);
		        myfile_2 << tmp << endl;
                }
		//myfile << row << endl;
	}
	myfile_1.close();
        myfile_2.close();
}

void MNG::sigma_decay(int t) {
	sigma = sigma0 * exp(-(float)t / lambda);
}

void MNG::gama_decay_exp(int t) {
	gama = gama0 * exp(-(float)t / eta);
}

void MNG::gama_decay_lin(int t) {
	gama = gama0 * ((float)(eta-t) / eta);
}

float MNG::entropy() {
	float sum = 0;

	for(int i = 0; i < map_dim_x*map_dim_y; i++) {
		float p = (float)entropy_histogram->at(i)/(float)trn_dataset->get_size();

		if (p > 0) {
			sum += p + log(p);
		}
	}

	return -sum;
}

void MNG::entropy_drive() {
	float h = entropy(); 

	if (h > max_entropy && (alpha - dalpha) > 0) {
		alpha -= dalpha;
	}
	if (h < max_entropy  && (alpha + dalpha) < 1) {
		alpha += dalpha;
	}
	max_entropy = h;
}

float MNG::winner_differentiation() {
	return (float)winner_set.size()/(float)trn_dataset->get_size();
}

float MNG::qerror() {
	return qerr;
}

bool rank_compare(srank r1, srank r2) {
	return r1.distance < r2.distance;
}