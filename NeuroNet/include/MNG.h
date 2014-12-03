#include <set>

#include "Neuron.h"
#include "DataSet.h"

#pragma once


struct srank {
	float	distance;
	int		id;
};

class MNG
{
private:
	CDataSet*	trn_dataset;
	Neuron**	map_layer;
	int*		rnk_matrix;
	float*		input_layer;
	float*		context_weight;
	float		sigma, sigma0, lambda;
	float		gama, gama0, eta;
	float		alpha, dalpha;

	int			input_dim, map_dim_x, map_dim_y;

	vector<int>     *entropy_histogram;
	set<int>	winner_set;
	float		max_entropy;
	float		qerr;

public:
	MNG(int input_dim, int map_dim_x, int map_dim_y);
	~MNG(void);

	void	insert_dataset(CDataSet*	data);
	void	train(int epochs, float alpha, float beta, float gama, float dalpha, int dec_fn, bool loging = false);
	void	save_to_file(char* file);
        void	save_to_file2(const char* file1, const char* file2);
	void	test();

	float	winner_differentiation();
	float	entropy();
	float	qerror();

private:
	float	train_one_sample(vector<float> sample, float beta);
	void	calc_rnk_matrix(float* xt, float *ct);
	Neuron* find_winner();
	void	update_context(Neuron* winner, float beta);
	void	sigma_decay(int t);
	void	gama_decay_exp(int t);
	void	gama_decay_lin(int t);
	void	entropy_drive();

};

bool rank_compare(srank r1, srank r2);

