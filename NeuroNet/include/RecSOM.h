/* 
 * File:   RecSOM.h
 * Author: Matej Pechac
 *
 * Created on April 6, 2013, 3:27 PM
 */
#include <set>

#include "Neuron.h"
#include "DataSet.h"
#include "SOMUtils.h"

#ifndef RECSOM_H
#define	RECSOM_H

class RecSOM {
public:
  /* Utils for measuring qerr, wd etc.*/
  SOMUtils  utils;
  
  RecSOM(int input_dim, int map_dim_x, int map_dim_y);
  RecSOM(const RecSOM& orig);
  virtual ~RecSOM();
  
	void	insert_dataset(CDataSet*	data);
	void	train(int epochs, float alpha, float beta, float gama, int dec_fn, bool loging = false);
  
  void  save_to_file3(const char* file_1, const char* file_2, int n_views, int mode);

private:
	float   train_one_sample(vector<float> sample, int nf);
	void    update_context(float* layer);
  Neuron*	activate_find_winner(float* layer);
	void    sigma_decay(int t);
	void    gama_decay_exp(int t);
	void    gama_decay_lin(int t);
  
private:
  /* params of network */
  CDataSet*	trn_dataset;
  Neuron**	map_layer;
  float*		input_layer;
  float*    context_layer;
  float*    output_layer;
  int       input_dim, map_dim_x, map_dim_y;
  
  /* params of learning */
	float		sigma, sigma0, lambda;
	float		gama, gama0, eta;
  float   beta, alpha;
};

#endif	/* RECSOM_H */

