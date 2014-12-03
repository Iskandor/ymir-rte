#include <stdlib.h>
#include <math.h>
#include <random>
#include <assert.h>
#include <iostream>

#include "Neuron.h"


using namespace std;

Neuron::Neuron(int dim, int x, int y)
{
	weight = new double[dim];
	context = new double[dim];

	this->x = x;
	this->y = y;
	this->in_dim = dim;
  this->con_dim = dim;
  this->lat_dim = 0;

	init_weights();
}

Neuron::Neuron(int dim, int id)
{
	weight = new double[dim];
	context = new double[dim];

	this->id = id;
	this->in_dim = dim;
  this->con_dim = dim;
  this->lat_dim = 0;
  
	init_weights();
}

Neuron::Neuron(int in_dim, int con_dim, int x, int y)
{
	weight = new double[in_dim];
	context = new double[con_dim];

	this->x = x;
	this->y = y;
	this->in_dim = in_dim;
  this->con_dim = con_dim;
  this->lat_dim = 0;
  
	init_weights();  
}

Neuron::Neuron(int in_dim, int con_dim, int lat_dim, int x, int y) {
	weight = new double[in_dim];
	context = new double[con_dim];
  lateral = new double[lat_dim];

	this->x = x;
	this->y = y;
	this->in_dim = in_dim;
  this->con_dim = con_dim;
  this->lat_dim = lat_dim;
  
	init_weights();    
}

Neuron::~Neuron(void)
{
	delete[] weight;
	delete[] context;
}

void Neuron::init_weights() {
	for(int i = 0; i < in_dim; i++) {
		weight[i] = ((double)rand()/(double)RAND_MAX)*2-1;
	}

	for(int i = 0; i < con_dim; i++) {
		context[i] = 0;
	}
  
  for(int i = 0; i < lat_dim; i++) {
    lateral[i] = 0;
  }
}

void Neuron::update_weights(double gama, Neuron* winner, double* xt, double* ct, double sigma, int neigh_fun) {
  double gd = 0;

  switch(neigh_fun) {
    case GAUSSIAN:
      gd = gaussian_distance(sigma, euclidian_distance(winner));
      break;
    case MEXICAN:
      gd = mexican_hat_distance(sigma, euclidian_distance(winner));
      break;
  }

	for(int i = 0; i < in_dim; i++) {
		double	dw = gama * gd * (xt[i] - weight[i]);
		weight[i]  += dw;
    if (weight[i] != weight[i]) assert(0);
	}
  for(int i = 0; i < con_dim; i++) {
    double	dc = gama * gd * (ct[i] - context[i]);
    context[i] += dc;
    if (context[i] != context[i]) assert(0);
  }
}

void Neuron::update_weights(double gama, Neuron* winner, double* xt, double sigma, int neigh_fun) {
  double gd = 0;

  switch(neigh_fun) {
    case GAUSSIAN:
      gd = gaussian_distance(sigma, euclidian_distance(winner));
      break;
    case MEXICAN:
      gd = mexican_hat_distance(sigma, euclidian_distance(winner));
      break;
  }

	for(int i = 0; i < in_dim; i++) {
		double	dw = gama * gd * (xt[i] - weight[i]);
		weight[i]  += dw;
    if (weight[i] != weight[i]) assert(0);
	}  
}

void Neuron::update_weights(double gama, double* xt, double* ct, double rnk, double sigma) {

	for(int i = 0; i < in_dim; i++) {
		double	dw = gama * exp(-rnk/sigma) * (xt[i] - weight[i]);
		weight[i]  += dw;
    if (weight[i] != weight[i]) assert(0);
	}
  for(int i = 0; i < con_dim; i++) {
    double	dc = gama * exp(-rnk/sigma) * (ct[i] - context[i]);
    context[i] += dc;
    if (context[i] != context[i]) assert(0);
  }
}

void Neuron::update_lateral_weights(double gama, Neuron** layer, double* act, double sigma, int neigh_fun, double alpha) {
  double gd = 0;

  for(int i = 0; i < lat_dim; i++) {
    double pos1[2] = {(double)layer[i]->x, (double)layer[i]->y};
    double pos2[2] = {(double)x, (double)y};
    
    switch(neigh_fun) {
      case GAUSSIAN:
        gd = gaussian_distance_zero(sigma, euclidian_distance(pos1, pos2, 2));
        break;
      case MEXICAN:
        gd = mexican_hat_distance(sigma, euclidian_distance(pos1, pos2, 2));
        break;
    }

    if (gd > 0) {
      lateral[i] += gama * (alpha*gd + (1-alpha) * act[i]) * activity;
    }
  }
}

double Neuron::gaussian_distance(double sigma, double numerator) {
	double g = 0;

	g = exp(-(numerator/(2*pow(sigma, 2))));

	return g;
}

double Neuron::gaussian_distance_zero(double sigma, double numerator) {
	double g = 0;

	g = numerator != 0 ? exp(-(numerator/(2*pow(sigma, 2)))) : 0;

	return g;
}

double Neuron::mexican_hat_distance(double sigma, double numerator) {
  double m = 0;

  m = (2 * M_PI) / sqrt(sigma) * (1 - 2 * M_PI * numerator / pow(sigma, 2)) * exp(-(numerator/(pow(sigma, 2))));
  return m;
}

double Neuron::recursive_distance(double alpha, double* xt, double* ct) {
	double dt = 0;

	dt = (1 - alpha) * euclidian_distance(xt, weight, in_dim) + alpha * euclidian_distance(ct, context, con_dim);

  if (dt != dt) {
    dump();
    for(int i = 0; i < in_dim; i++) {
      cout << xt[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < con_dim; i++) {
      cout << ct[i] << " ";
    }
    cout << endl;
    assert(0);
  }
  
  activity = exp(-dt);
  
	return dt;
}

double Neuron::recursive_distance(double alpha, double beta, double* xt, double* ct) {
	double dt = 0;

	dt = alpha * euclidian_distance(xt, weight, in_dim) + beta * euclidian_distance(ct, context, con_dim);

  if (dt != dt) {
    dump();
    for(int i = 0; i < in_dim; i++) {
      cout << xt[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < con_dim; i++) {
      cout << ct[i] << " ";
    }
    cout << endl;
    assert(0);
  }
  
  activity = exp(-dt);
  
	return dt;  
}

double Neuron::distance(double* xt) {
  double dt = 0;
  
  dt = euclidian_distance(xt, weight, in_dim);
  
  if (dt != dt) {
    dump();
    cout << "Input:" << endl;
    for(int i = 0; i < in_dim; i++) {
      cout << xt[i] << " ";
    }
    cout << endl;
    assert(0);
  }
  
  activity = exp(-dt);
  
  return dt;
}

double Neuron::euclidian_distance(double* v1, double* v2, int dim) {
	if (v1 == NULL || v2 == NULL) {
		return -1;
	}

	double sum = 0;

	for(int i = 0; i < dim; i++) {
            double x = *(v1+i);
            double y = *(v2+i);
            sum += pow((x - y), 2);
	}
	return sum;
}

double Neuron::euclidian_distance(Neuron* w) {
	if (w == NULL) {
    assert(0);
	}

	double sum = 0;

	sum += pow((double)(w->x - x), 2);
	sum += pow((double)(w->y - y), 2);

	return sum;
}

double Neuron::activate(vector<double>* input, double* matrix) {
  double act = 0.0;
  
  for(int i = 0; i < lat_dim; i++) {
    act += (*input)[i] * matrix[i];
  }
  
  return act;
}

double* Neuron::get_weight(int mode) {
  if (mode == WEIGHT) return weight;
	if (mode == CONTEXT) return context;
  if (mode == LATERAL) return lateral;
}

int Neuron::get_dim(int mode) {
  if (mode == WEIGHT)   return in_dim;
  if (mode == CONTEXT)  return con_dim;
  if (mode == LATERAL)  return lat_dim;
}

int Neuron::get_x() {
	return x;
}

int Neuron::get_y() {
	return y;
}

void Neuron::dump() {
  cout << in_dim << endl;
  cout << con_dim << endl;
  cout << "Weights:" << endl;
  for(int i = 0; i < in_dim; i++) {
    cout << weight[i] << " ";
  }
  cout << endl;
  cout << "Context weights:" << endl;
  for(int i = 0; i < con_dim; i++) {
    cout << context[i] << " ";
  }
  cout << endl;
}