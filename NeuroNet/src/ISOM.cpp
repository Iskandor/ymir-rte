/* 
 * File:   ISOM.cpp
 * Author: Matej Pechac
 * 
 * Created on December 3, 2014, 8:20 PM
 */

#include "ISOM.h"
#include <cmath>
#include <cstring>

ISOM::ISOM(int input_dim, int map_dim_x, int map_dim_y, Neuron::E_NEIGHBOUR nf) {
  	map_layer		= new Neuron*[map_dim_x*map_dim_y];
	input_layer		= new double[input_dim];
  output_layer	= new double[map_dim_x*map_dim_y];

	this->map_dim_x = map_dim_x;
	this->map_dim_y = map_dim_y;
	this->input_dim = input_dim;
  neighbour_func = nf;

	for(int i = 0; i < map_dim_y; i++) {
		for(int j = 0; j < map_dim_x; j++) {
			map_layer[i*map_dim_x+j] = new Neuron(input_dim, 0, j, i);
		}
	}

	sigma0 = sqrt((double)map_dim_x);
}

ISOM::ISOM(const ISOM& orig) {
  map_dim_x = orig.map_dim_x;
  map_dim_y = orig.map_dim_y;
  input_dim = orig.input_dim;
  memcpy(map_layer, orig.map_layer, sizeof(Neuron) * map_dim_x* map_dim_y);
  memcpy(input_layer, orig.input_layer, sizeof(double) * input_dim);
  output_layer	= new double[map_dim_x*map_dim_y];
  
  sigma0 = orig.sigma0;
  gama0 = orig.gama0;
  sigma = orig.sigma;
  gama = orig.gama;
  lambda = orig.lambda;
}

ISOM::~ISOM() {
  delete[] map_layer;
  delete[] input_layer;
  delete[] output_layer;
}

void ISOM::init_training(int epochs, double gama) {
	lambda = (double)epochs / log((double)max(map_dim_x, map_dim_y)/2.0f);
	eta = (double)epochs;
	gama0 = gama;  
}

void ISOM::activate(vector<double> sample, Neuron::DECAY_FN mode) {
	Neuron*		w = NULL;
  double     d;

	input_layer = &sample[0];

	w = find_winner();

	for(int i = 0; i < map_dim_x*map_dim_y; i++) {
		d = map_layer[i]->distance(input_layer);
    if (mode == Neuron::LIN) output_layer[i] = d;
    if (mode == Neuron::EXP) output_layer[i] = exp(-d);
	}  
}

double ISOM::train_one_sample(vector<double> sample) {
	Neuron*		w = NULL;

	input_layer = &sample[0];

	w = find_winner();

	double qerr = w->distance(input_layer);

	for(int i = 0; i < map_dim_x*map_dim_y; i++) {
		map_layer[i]->update_weights(gama, w, input_layer, sigma, neighbour_func);
	}

	return qerr;   
}

double* ISOM::get_activation() {
  return output_layer;  
}

pair<int, int> ISOM::get_size() {
  return pair<int, int>(map_dim_x, map_dim_y);
}

void ISOM::param_decay(int epoch, Neuron::DECAY_FN mode) {
  sigma_decay(epoch);
  gama_decay(epoch, mode);
}

void ISOM::sigma_decay(int t) {
	sigma = sigma0 * exp(-(double)t / lambda);
}

void ISOM::gama_decay(int t, Neuron::DECAY_FN mode) {
  if (mode == Neuron::EXP) {
    gama = gama0 * exp(-(double)t / eta);
  }
  if (mode == Neuron::LIN) {
    gama = gama0 * ((double)(eta-t) / eta);
  }
}



