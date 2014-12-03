#pragma once

#include <vector>

using namespace std;

#define WEIGHT  1
#define CONTEXT 2
#define LATERAL 3

class Neuron
{
private:
	double*  weight;
	double*  context;
  double*  lateral;
	int     x, y;
	int     in_dim;
  int     con_dim;
  int     lat_dim;
  int     id;
  
  double   activity;

public:
  enum DECAY_FN{
    EXP = 0,
    LIN = 1
  }; 
  
  enum E_NEIGHBOUR {
    GAUSSIAN = 1,
    MEXICAN = 2
  };
  
  /* Konstruktor pre MSOM */
	Neuron(int dim, int x, int y);
  /* Konstruktor pre MNG */
  Neuron(int dim, int id);
  /* Konstruktor pre RecSOM a SOM */
  Neuron(int in_dim, int con_dim, int x, int y);
  /* Konstruktor pre LSOM */
  Neuron(int in_dim, int con_dim, int lat_dim, int x, int y);
  
	~Neuron(void);

  /* Update pre MSOM a RecSOM */
  void    update_weights(double gama, Neuron* winner, double* xt, double* ct, double sigma, int neigh_fun);
  /* Update pre MNG */
  void    update_weights(double gama, double* xt, double* ct, double rnk, double sigma);
  /* Update pre SOM */
  void    update_weights(double gama, Neuron* winner, double* xt, double sigma, int neigh_fun);
  /* Update pre LSOM */
  void    update_lateral_weights(double gama, Neuron** layer, double* act, double sigma, int neigh_fun, double alpha);
  
  double   recursive_distance(double alpha, double* xt, double* ct);
  double   recursive_distance(double alpha, double beta, double* xt, double* ct);
  double   distance(double* xt);
  
  double   activate(vector<double>* input, double* matrix);
  
	double*	get_weight(int mode);
  int     get_dim(int mode);
	int     get_x();
	int     get_y();
  
private:
	double	euclidian_distance(double* v1, double* v2, int dim);
	double	euclidian_distance(Neuron* w);
	double	gaussian_distance(double sigma, double numerator);
  double gaussian_distance_zero(double sigma, double numerator);
  double mexican_hat_distance(double sigma, double numerator);
	void	init_weights();
  
  void  dump();
};

