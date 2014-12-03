#include <set>

#include "Neuron.h"
#include "DataSet.h"

#pragma once

struct sMSOMTrnConfig {
  float alpha; 
  float beta; 
  float gama;
  float dalpha; 
  int   dec_fn;
  
  sMSOMTrnConfig(float _alpha, float _beta, float _gama, float _dalpha, int _dec_fn) {
    alpha = _alpha;
    beta = _beta;
    gama = _gama;
    dalpha = _dalpha,
    dec_fn = _dec_fn;
  }
};

class MSOM
{
private:
	CDataSet*	trn_dataset;
	Neuron**	map_layer;
	float*		input_layer;
	float*		context_weight;
  float*    output;
	float		sigma, sigma0, lambda;
	float		gama, gama0, eta;
  float   beta;
	float		alpha, dalpha;

	int		input_dim, map_dim_x, map_dim_y;

	vector<int>     *entropy_histogram;
	float		max_entropy;
	set<int>	winner_set;
	float		qerr;

public:
	MSOM(int input_dim, int map_dim_x, int map_dim_y);
	~MSOM(void);

	void	insert_dataset(CDataSet*	data);
  void  init_training(int epochs, float alpha, float beta, float gama, float dalpha);
	void	train(int epochs, sMSOMTrnConfig config, bool loging = false);
  float	train_one_sample(vector<float> sample, int nf, int a_mode);
  void  activate(vector<float> sample, vector<float> *output, int mode);
  float*  activate(vector<float> sample, int mode);
  void  reverse_activate(float* output, vector<float> *sample);
  void  reset_context();
  void  param_decay(int epoch, int mode);
  
	void	save_to_file(const char* file);
  void	save_to_file2(const char* file1, const char* file2, int n_views);
  void	save_to_file3(const char* file1, const char* file2, int n_views, int mode);
  void	test(char* filename, float alpha, float beta);
	void	write_output(ofstream& myfile, vector<float> *activation);
  float* get_activation();
  void  get_size(int* size);

	float	winner_differentiation();
	float	entropy();
	float	qerror();

private:
	Neuron*	find_winner(int mode);
	void	update_context(Neuron* winner, float beta);
	void	sigma_decay(int t);
	void	gama_decay(int t, int mode);
	void	entropy_drive();

};

