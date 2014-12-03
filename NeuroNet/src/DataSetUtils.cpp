/* 
 * File:   DataSetUtils.cpp
 * Author: matej
 * 
 * Created on July 23, 2012, 9:03 PM
 */

#include <math.h>
#include <fstream>
#include <iostream>
#include <string.h>

#include "DataSetUtils.h"
#include "main.h"

DataSetUtils::DataSetUtils() {
}

DataSetUtils::DataSetUtils(const DataSetUtils& orig) {
}

DataSetUtils::~DataSetUtils() {
}

void DataSetUtils::analyze_vector_norms(CDataSet* dataset) {
	list<sSequence>                 *trn_data = dataset->get_trn_data();
	list<sSequence>::iterator       seq_it;
  list< vector<float> >::iterator	sam_it;

  double result[N_GRASPS][N_VIEWS];
  int number[N_GRASPS][N_VIEWS];

  memset(&number, 0, sizeof(int)*N_GRASPS*N_VIEWS);
  memset(&result, 0, sizeof(double)*N_GRASPS*N_VIEWS);

  for (seq_it=trn_data->begin(); seq_it != trn_data->end(); seq_it++) {
      sSequence sample = *seq_it;
      
      for (sam_it = sample.seq.begin(); sam_it != sample.seq.end(); sam_it++) {
          vector<float> v = *sam_it;

          result[sample.seq_class][sample.seq_view] += vector_magnitude(&v);
          number[sample.seq_class][sample.seq_view]++;
      }
  }

  for(int i = 0; i < N_GRASPS; i++) {
    for(int j = 0; j < N_VIEWS; j++) {
      result[i][j] /= number[i][j];
    }
  }

	ofstream myfile;
  char     val[30+1];
	myfile.open ("analyze_vector_norms.log");

  for(int i = 0; i < N_GRASPS; i++) {
    if (i == 0) myfile << GRASP_1 << " ";
    if (i == 1) myfile << GRASP_2 << " ";
    if (i == 2) myfile << GRASP_3 << " ";
    for(int j = 0; j < N_VIEWS; j++) {
      sprintf(val, "%.5f", result[i][j]);
      myfile << val << " ";
    }
    myfile << endl;
  }

  myfile.close();

}

double DataSetUtils::vector_magnitude(vector<float>* v) {
  double mag = 0.0;

  for(int i =0; i < v->size(); i++) {
    mag += pow(v->at(i), 2);
  }

  return sqrt(mag);
}

void DataSetUtils::integrity_check(CDataSet* dataset) {
  list< sSequence > *data = dataset->get_trn_data();
  
	list<sSequence>::iterator         seq_it;
  list< vector<float> >::iterator   sam_it;
  int seq_classes[N_GRASPS];
  int i = 1;
  int j = 0;
  
  memset(seq_classes, 0, sizeof(int) * N_GRASPS);
  
  cout << "Dataset size: " << data->size() << endl;
  
	for (seq_it=data->begin(); seq_it != data->end(); seq_it++) {
		sSequence sample = *seq_it;
    
    seq_classes[sample.seq_class]++;
    cout << "Sequence " << i <<  " size: " << sample.seq.size() << " class: " << sample.seq_class << endl;
    j++;
    
    if (j == N_GRASPS*N_VIEWS) {
      i++;
      j = 0;
    }
  }
  
  cout << " Sequence class summary: ";
  
  for (int x = 0; x < N_GRASPS; x++) {
    cout << seq_classes[x] << " ";
  }
}

