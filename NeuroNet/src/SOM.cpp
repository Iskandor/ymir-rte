/* 
 * File:   SOM.cpp
 * Author: Matej Pechac
 * 
 * Created on April 18, 2013, 9:47 PM
 */

#include "SOM.h"
#include <cmath>

SOM::SOM(int input_dim, int map_dim_x, int map_dim_y, Neuron::E_NEIGHBOUR nf) : ISOM(input_dim, map_dim_x, map_dim_y, nf) {
}

SOM::SOM(const SOM& orig) : ISOM(orig) {
}

SOM::~SOM() {
}

Neuron* SOM::find_winner() {
	int		mini = 0;
	float	mind = -1;

	for (int i = 1; i < map_dim_x*map_dim_y; i++) {
		double i_d = map_layer[i]->distance(input_layer);
		if (mind > i_d || mind == -1) {
			mini = i;
			mind = i_d;
		}
	}

	return map_layer[mini];
}

