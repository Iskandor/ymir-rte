/* 
 * File:   SOMUtils.cpp
 * Author: matej
 * 
 * Created on April 7, 2013, 10:13 AM
 */

#include "SOMUtils.h"

#include <vector>
#include <algorithm>
#include <cstring>

SOMUtils::SOMUtils() {
  qerr = 0.0;
}

SOMUtils::SOMUtils(const SOMUtils& orig) {
}

SOMUtils::~SOMUtils() {
}

void SOMUtils::reset_qerr() {
  qerr = 0.0;
}

void SOMUtils::reset_wd() {
  winner_set.clear();
}

void SOMUtils::update_qerr(float error) {
  qerr = error;
}

void SOMUtils::update_wd(int n) {
  winner_set.insert(n);
}

void SOMUtils::calc_wd(int size) {
  wd = ((double)winner_set.size() / (double)size) * 100;
}

double SOMUtils::get_wd() {
  return wd;
}

float SOMUtils::get_qerr() {
  return qerr;
}

void SOMUtils::filter_kwta(int k, float* activation, int size) {
  vector< pair<int, float> >  sorted_act;
  
  for(int i = 0; i < size*size; i++) {
    sorted_act.push_back(make_pair(i, activation[i]));
  }
  
  sort(sorted_act.begin(), sorted_act.end(), compare_pair_kwta);
  
  memset(activation, 0.0f, sizeof(float)*size*size);
  
  for(int i = 0; i < k; i++) {
    activation[sorted_act[i].first] = 1.0f;
  }  
}

void SOMUtils::filter_threshold(float theta, float* activation, int size) {
  for(int i = 0; i < size*size; i++) {
    activation[i] -= (theta * activation[i]);
  }
}

bool compare_pair_kwta(pair<int,float> p1, pair<int,float> p2) {
  return (p1.second < p2.second);
}

