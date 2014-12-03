/* 
 * File:   SOM.h
 * Author: Matej Pechac
 *
 * Created on April 18, 2013, 9:47 PM
 */

#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>

#include "ISOM.h"
#include "Neuron.h"

using namespace std;

#ifndef SOM_H
#define	SOM_H

class SOM : public ISOM {
public:
  SOM(int input_dim, int map_dim_x, int map_dim_y, Neuron::E_NEIGHBOUR nf);
  SOM(const SOM& orig);
  virtual ~SOM();
   
private:
	Neuron*	find_winner();

private:

};

#endif	/* SOM_H */

