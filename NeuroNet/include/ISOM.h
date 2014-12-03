/* 
 * File:   ISOM.h
 * Author: Matej Pechac
 *
 * Created on December 3, 2014, 8:20 PM
 */

#ifndef ISOM_H
#define	ISOM_H

#include <vector>

#include "Neuron.h"

using namespace std;

class ISOM {
public: 
  ISOM(int input_dim, int map_dim_x, int map_dim_y, Neuron::E_NEIGHBOUR nf);
  ISOM(const ISOM& orig);
  virtual ~ISOM();
  
  void    init_training(int epochs, double gama);
  double  train_one_sample(vector<double> sample);
  void    activate(vector<double> sample, Neuron::DECAY_FN mode);
  void    param_decay(int epoch, Neuron::DECAY_FN mode);

  double* get_activation();
  pair<int, int> get_size();
  
protected:
  virtual Neuron*	find_winner() = 0;
	void    sigma_decay(int t);
	void    gama_decay(int t, Neuron::DECAY_FN mode);
  
protected:
	Neuron**	map_layer;
	double*		input_layer;
  double*   output_layer;
	double    sigma, sigma0, lambda;
	double    gama, gama0, eta;

	int	input_dim;
  int map_dim_x;
  int map_dim_y;
  Neuron::E_NEIGHBOUR neighbour_func;
};

#endif	/* ISOM_H */

