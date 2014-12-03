/* 
 * File:   STS.cpp
 * Author: Matej Pechac
 * 
 * Created on April 14, 2013, 8:25 PM
 */

#include "STS.h"
#include "main.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>
#include <assert.h>

#include <sys/stat.h>

using namespace std;

STS::STS(int stsp_input_dim, int stsp_size, int motor_input_dim, int motor_size, int stsa_size) {
  STSp = new MSOM(stsp_input_dim, stsp_size, stsp_size);
  STSa = new LSOM((stsp_size*stsp_size+motor_size*motor_size), stsa_size, stsa_size);
  PMC = new MSOM(motor_input_dim, motor_size, motor_size);
}

STS::STS(const STS& orig) {
}

STS::~STS() {
  delete STSa;
  delete STSp;
  delete PMC;
}

void STS::insert_dataset(CDataSet* visual, CDataSet* motor) {
  visual_data = visual;
  motor_data = motor;
  
  STSp->insert_dataset(visual_data);
  STSa->insert_dataset(visual_data);
  PMC->insert_dataset(motor_data);
}

void STS::test(int epochs, sMSOMTrnConfig cfgSTSp) {
  list<sSequence>                 *vis_trn_data = motor_data->get_trn_data();
	list<sSequence>::iterator       seq_it_v;
  list< vector<float> >::iterator	sam_it_v;
  float qerr;

  PMC->init_training(epochs, cfgSTSp.alpha, cfgSTSp.beta, cfgSTSp.gama, cfgSTSp.dalpha);
  
  for(int e = 0; e < epochs; e++) {
    qerr = 0.0;
    PMC->param_decay(e, EXP);
    for (seq_it_v=vis_trn_data->begin(); seq_it_v != vis_trn_data->end(); seq_it_v++) {
      sSequence sample = *seq_it_v;

      PMC->reset_context();
      for (sam_it_v = sample.seq.begin(); sam_it_v != sample.seq.end(); sam_it_v++) {
        qerr += PMC->train_one_sample(*sam_it_v, GAUSSIAN, 0);
      }
    }
    cout << e << " " << qerr << endl;
  }
  
  PMC->save_to_file3("grasp.out", "views.out", 0, EXP);
}

void STS::train(int epochs, sLSOMTrnConfig cfgSTSa, sMSOMTrnConfig cfgSTSp, sMSOMTrnConfig cfgPMC, bool loging) {
  list<sSequence>                 *vis_trn_data = visual_data->get_trn_data();
  list<sSequence>                 *mot_trn_data = motor_data->get_trn_data();
	list<sSequence>::iterator       seq_it_v;
  list< vector<float> >::iterator	sam_it_v;
	list<sSequence>::iterator       seq_it_m;
  list< vector<float> >::iterator	sam_it_m;
  int           persp = 0;
  float         qerr_stsa = 0.0;
  float         qerr_stsp = 0.0;
  float         qerr_pmc  = 0.0;
  float *STSp_output;
  float *PMC_output;
  vector<float> input;
  
  int pmc_size[2];
  int stsp_size[2];
  
  PMC->get_size(pmc_size);
  STSp->get_size(stsp_size);
  
  
  //STSa->init_training(epochs, cfgSTSa.gama);
  STSa->init_training(epochs, cfgSTSa.gama, cfgSTSa.gama_l, cfgSTSa.alpha);
  STSp->init_training(epochs, cfgSTSp.alpha, cfgSTSp.beta, cfgSTSp.gama, cfgSTSp.dalpha);
  PMC->init_training(epochs, cfgPMC.alpha, cfgPMC.beta, cfgPMC.gama, cfgPMC.dalpha);
  
  for(int e = 0; e < epochs; e++) {
    qerr_stsa = 0.0;
    qerr_stsp = 0.0;
    qerr_pmc  = 0.0;
    persp = 0;
    seq_it_v = vis_trn_data->begin();
    seq_it_m = mot_trn_data->begin();
    
    STSp->param_decay(e, cfgSTSp.dec_fn);
    STSa->param_decay(e, cfgSTSa.dec_fn);
    PMC->param_decay(e, cfgPMC.dec_fn);
    
    while(seq_it_v != vis_trn_data->end()) {
       
      sSequence pmc_sample = *seq_it_m;
      sSequence sts_sample = *seq_it_v;
      
      sam_it_v = sts_sample.seq.begin();
      sam_it_m = pmc_sample.seq.begin();
      
      while(sam_it_v != sts_sample.seq.end()) {
        // train PMC
        if (persp == 0) {
          qerr_pmc += PMC->train_one_sample(*sam_it_m, GAUSSIAN, EXP);
          sam_it_m++;
        }
        // train STSp
        qerr_stsp += STSp->train_one_sample(*sam_it_v, GAUSSIAN, EXP);
        sam_it_v++;
      }
      // train STSa
      PMC_output = PMC->get_activation();
      STSp_output = STSp->get_activation();
      //utils.filter_kwta(16, PMC_output, pmc_size[0]);
      //utils.filter_kwta(16, STSp_output, stsp_size[0]);
      concat_array(PMC_output, pmc_size[0], STSp_output, stsp_size[0], &input);
      qerr_stsa += STSa->train_one_sample(input, GAUSSIAN, EXP);
        
      STSp->reset_context();
      seq_it_v++;
      persp++;
      
      if (persp == 4) {
        PMC->reset_context();
        seq_it_m++;
        persp = 0;
      }
    }
    
    cout << e << " PMC " << qerr_pmc << " STSp " << qerr_stsp << " STSa " << qerr_stsa << endl;
  }
}

void STS::save2file(sLSOMTrnConfig cfgSTSa, sMSOMTrnConfig cfgSTSp, sMSOMTrnConfig cfgPMC, int mode) {
  list<sSequence>                 *vis_trn_data = visual_data->get_trn_data();
  list<sSequence>                 *mot_trn_data = motor_data->get_trn_data();
	list<sSequence>::iterator       seq_it_v;
  list< vector<float> >::iterator	sam_it_v;
	list<sSequence>::iterator       seq_it_m;
  list< vector<float> >::iterator	sam_it_m;
  
  char file_name_c[1000+1] = "";
  char file_name_v[1000+1] = "";
  
  char tmp[20+1];
  char line[100+1];
  char dir[100+1];
  
  time_t   t = time(0);
  struct tm * now = localtime( & t );

  sprintf(dir, "output/%i-%i-%i_%i:%i:%i", (now->tm_year+1900), (now->tm_mon+1), now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);
  
  mkdir(dir, 0777);
  
  sprintf(file_name_c, "%s/stsp_a%.1f_b%.2f_c%.3f.c", dir, cfgSTSp.alpha, cfgSTSp.beta, cfgSTSp.gama);
  sprintf(file_name_v, "%s/stsp_a%.1f_b%.2f_c%.3f.v", dir, cfgSTSp.alpha, cfgSTSp.beta, cfgSTSp.gama);
  STSp->save_to_file3(std::string(file_name_c).c_str(), std::string(file_name_v).c_str(), N_VIEWS, mode);

  sprintf(file_name_c, "%s/pmc_a%.1f_b%.2f_c%.3f.c", dir, cfgPMC.alpha, cfgPMC.beta, cfgPMC.gama);
  sprintf(file_name_v, "%s/pmc_a%.1f_b%.2f_c%.3f.v", dir, cfgPMC.alpha, cfgPMC.beta, cfgPMC.gama);
  PMC->save_to_file3(std::string(file_name_c).c_str(), std::string(file_name_v).c_str(), 0, mode);  
  
  sprintf(file_name_c, "%s/stsa_a%.1f_b%.2f_c%.3f.c", dir, 0.0f, 0.0f, cfgSTSa.gama);
  sprintf(file_name_v, "%s/stsa_a%.1f_b%.2f_c%.3f.v", dir, 0.0f, 0.0f, cfgSTSa.gama);
  
  ofstream myfile_1, myfile_2;
  myfile_1.open (file_name_c);
  myfile_2.open (file_name_v);

  int stsa_size[2];
  int stsp_size[2];
  int pmc_size[2];
  
  STSa->get_size(stsa_size);
  STSp->get_size(stsp_size);
  PMC->get_size(pmc_size);
  
  double *map_magnitude = new double[stsa_size[1]*stsa_size[0]*N_GRASPS];
  double *map_magnitude_view = new double[stsa_size[1]*stsa_size[0]*N_VIEWS];
  double *map_normal_dist = new double[stsa_size[1]*stsa_size[0]];
  
  memset(map_magnitude, 0, sizeof(double)*stsa_size[1]*stsa_size[0]*N_GRASPS);
  memset(map_magnitude_view, 0, sizeof(double)*stsa_size[1]*stsa_size[0]*N_VIEWS);
  memset(map_normal_dist, 0, sizeof(double)*stsa_size[1]*stsa_size[0]);
  
  int persp = 0;
  
  float *STSp_output;
  vector<float> STSa_output;
  float *PMC_output;
  vector<float> input;
  
  seq_it_v = vis_trn_data->begin();
  seq_it_m = mot_trn_data->begin();

  while(seq_it_v != vis_trn_data->end()) {

    sSequence pmc_sample = *seq_it_m;
    sSequence sts_sample = *seq_it_v;

    sam_it_v = sts_sample.seq.begin();
    sam_it_m = pmc_sample.seq.begin();

    while(sam_it_v != sts_sample.seq.end()) {
      // activate PMC
      if (persp == 0) {
        PMC_output = PMC->activate(*sam_it_m, mode);
        sam_it_m++;
      }
      // activate STSp
      STSp_output = STSp->activate(*sam_it_v, mode);
      sam_it_v++;
    }
    // activate STSa
    //utils.filter_threshold(1.0f, PMC_output, pmc_size[0]);
    //utils.filter_kwta(16, PMC_output, pmc_size[0]);
    //utils.filter_kwta(16, STSp_output, stsp_size[0]);

    concat_array(PMC_output, pmc_size[0], STSp_output, stsp_size[0], &input);
    STSa->activate(input, &STSa_output, mode);

    for(int i = 0; i < stsa_size[1]; i++) {
      for(int j = 0; j < stsa_size[0]; j++) {
        if (STSa_output[i*stsa_size[0]+j] != STSa_output[i*stsa_size[0]+j]) {
          assert(0);
        }
        map_magnitude[i*stsa_size[0]*N_GRASPS+j*N_GRASPS+sts_sample.seq_class] += STSa_output[i*stsa_size[0]+j];
        if (N_VIEWS > 0) {
          map_magnitude_view[i*stsa_size[0]*N_VIEWS+j*N_VIEWS+sts_sample.seq_view] += STSa_output[i*stsa_size[0]+j];
        }
        map_normal_dist[i*stsa_size[0]+j] += STSa_output[i*stsa_size[0]+j];
      }
    }
    
    
    STSp->reset_context();
    seq_it_v++;
    persp++;

    if (persp == 4) {
      PMC->reset_context();
      seq_it_m++;
      persp = 0;
    }
  }
  
  int max_d = 0;
  
  for(int i = 1; i < stsa_size[1]*stsa_size[0]; i++) {
    if (map_normal_dist[i] > map_normal_dist[max_d]) {
      max_d = i;
    }
  }
  
  sprintf(tmp, "#%i %i", stsa_size[0], stsa_size[1]);
  myfile_1 << tmp << endl;
  myfile_2 << tmp << endl;
	for (int i = 0; i < stsa_size[1]; i++) {
		for (int j = 0; j < stsa_size[0]; j++) {
      line[0] = '\0';
			for (int g = 0; g < N_GRASPS; g++) {
        map_magnitude[i*stsa_size[0]*N_GRASPS+j*N_GRASPS+g] /= map_normal_dist[max_d];
        if (mode == LIN) {
          map_magnitude[i*stsa_size[0]*N_GRASPS+j*N_GRASPS+g] = 1 - map_magnitude[i*stsa_size[0]*N_GRASPS+j*N_GRASPS+g];
        }
        sprintf(tmp, "%f ", map_magnitude[i*stsa_size[0]*N_GRASPS+j*N_GRASPS+g]);
        strcat(line, tmp);
      }
      myfile_1 << line << endl;
      line[0] = '\0';
      for(int v = 0; v < N_VIEWS; v++) {
        map_magnitude_view[i*stsa_size[0]*N_VIEWS+j*N_VIEWS+v] /= map_normal_dist[max_d];
        if (mode == LIN) {
          map_magnitude_view[i*stsa_size[0]*N_VIEWS+j*N_VIEWS+v] = 1 - map_magnitude_view[i*stsa_size[0]*N_VIEWS+j*N_VIEWS+v];
        }
        sprintf(tmp, "%f ", map_magnitude_view[i*stsa_size[0]*N_VIEWS+j*N_VIEWS+v]);
        strcat(line, tmp);
      }
      myfile_2 << line << endl;
    }
  }
  myfile_1.close();
  myfile_2.close();
}

void STS::concat_vector(vector<float> *input1, vector<float> *input2, vector<float> *output) {
  output->clear();
  for(unsigned i = 0; i < input1->size(); i++) {
    output->push_back(input1->at(i));
  }
  for(unsigned i = 0; i < input2->size(); i++) {
    output->push_back(input2->at(i));
  }
}

void STS::concat_array(float* input1, int size1, float* input2, int size2, vector<float>* output) {
  output->clear();
  for(unsigned i = 0; i < size1*size1; i++) {
    if (input1[i] != input1[i]) assert(0);
    output->push_back(input1[i]);
  }
  for(unsigned i = 0; i < size2*size2; i++) {
    if (input2[i] != input2[i]) assert(0);
    output->push_back(input2[i]);
  }  
}

