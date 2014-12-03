/* 
 * File:   LSOM.h
 * Author: Matej Pechac
 *
 * Created on June 11, 2013, 5:57 PM
 */

#ifndef LSOM_H
#define	LSOM_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>

#include "DataSet.h"
#include "Neuron.h"

using namespace std;

struct sLSOMTrnConfig {
  float alpha;
  float gama;
  float gama_l;
  int   dec_fn;
  
  sLSOMTrnConfig(float _alpha, float _gama, float _gama_l, int _dec_fn) {
    alpha = _alpha;
    gama = _gama;
    gama_l = _gama_l;
    dec_fn = _dec_fn;
  }
};

class LSOM {
public:
  LSOM(int input_dim, int map_dim_x, int map_dim_y);
  LSOM(const LSOM& orig);
  virtual ~LSOM();
  
 	void	insert_dataset(CDataSet* data);
  void  init_training(int epochs, float gama, float _gama_l, float _alpha);
	void	train(int epochs, sLSOMTrnConfig config, bool loging = false);
  float	train_one_sample(vector<float> sample, int nf, int a_mode);
  void  activate(vector<float> sample, vector<float> *output, int mode);
  void  param_decay(int epoch, int mode);

	void	write_output(ofstream& myfile, vector<float> *activation);
  void  get_activation(vector<float> *output, int mode);
  void  get_size(int* size);

private:
	Neuron*	find_winner(int mode);
	void    sigma_decay(int t);
	void    gama_decay(int t, int mode);
  
  void    calc_weight_matrix(int i, float* matrix);

private:
	CDataSet*	trn_dataset;
	Neuron**	map_layer;
	float*		input_layer;
  float*    output_layer;
	float		sigma, sigma0, lambda, sigma_l;
	float		gama, gama0, eta, gama_l;
  float   alpha;

	int		input_dim, map_dim_x, map_dim_y;

};


#endif	/* LSOM_H */

