/* 
 * File:   CMathUtils.cpp
 * Author: Matej Pechac
 * 
 * Created on April 20, 2014, 10:10 PM
 */

#include "CMathUtils.h"
#include <cmath>

CMathUtils::CMathUtils() {
}

CMathUtils::CMathUtils(const CMathUtils& orig) {
}

CMathUtils::~CMathUtils() {
}

double CMathUtils::euclidian_distance(int x1, int y1, int x2, int y2) {
  return euclidian_distance((double)x1, (double)y1, (double)x2, (double)y2);
}

double CMathUtils::euclidian_distance(double x1, double y1, double x2, double y2) {
  double sum;

  sum = pow((x1 - x2), 2) + pow((y1 - y2), 2);

  return sqrt(sum);
}

int CMathUtils::find_min(set<int>* find_set, double* array) {
  set<int>::iterator it;
  int min_i = *find_set->begin();
  for(it = find_set->begin(); it != find_set->end(); it++) {
    if (array[*it] < array[min_i]) {
      min_i = *it;
    }
  }
  
  return min_i;
}

int CMathUtils::find_val(int* array, int length, int val) {
  for(int i = 0; i < length; i++) {
    if (array[i] == val) {
      return i;
    }
  }
  
  return -1;  
}

