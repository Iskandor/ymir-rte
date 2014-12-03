#include <random>
#include <time.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iosfwd>

#include "main.h"
#include "MSOM.h"
#include "MNG.h"
#include "RecSOM.h"
#include "DataSet.h"
#include "DataSetUtils.h"
#include "STS.h"

using namespace std;

int main(int argc, char** argv) {
  srand((unsigned)time(0));

  cout << "Loading data..." << endl;
  // nezabudnut HEAD_CUT, TAIL_CUT a N_VIEWS
  //CDataSet        dataset(std::string("dataset/Trajectories.data.3.xy").c_str(), DIMENSION_2, ICUB_DATA, N_VIEWS, 2, 0);
  DataSetUtils    utils;
  vector<sResult> result;

  //utils.integrity_check(&dataset);
  
/*
  for (float alpha = 0.2; alpha < 0.9; alpha += 0.1) {
    for(float beta = 0.4; beta < 0.9; beta += 0.1) {
      test(&dataset, alpha, beta, 0.01, 0.00, &result, true);
    }
  }
  
  save_results(&result, std::string("test28012013.txt").c_str());
*/

  //DataSetUtils utils;

  //utils.analyze_vector_norms(&dataset);

  //test(&dataset, 14, 0.3f, 0.7f, 0.10f, 0.0f, &result, true); // vizualna MSOM
  //test(&dataset, 12, 0.3f, 0.5f, 0.02f, 0.0f, &result, true); // motoricka MSOM
  //test(&dataset, 14, 0.5f, 0.5f, 0.10f, 0.0f, &result, true); // vizualna RecSOM
  
  STS_test();
  //reverse_test();

  //system("pause");

  return 0;
}

void test(CDataSet* data, int a, float alpha, float beta, float gama, float dalpha, vector<sResult> *result, bool output) {

  char file_name_c[1000+1] = "";
  char file_name_v[1000+1] = "";

  sResult r;

  r.entropy = 0;
  r.qerr = 0;
  r.wd = 0;
  
  sMSOMTrnConfig  cfg(alpha, beta, gama, dalpha, EXP);

  for (int i = 0; i < 1; i++) {
    MSOM somnet(data->get_dim(), a, a);
    //RecSOM somnet(data->get_dim(), a, a);

    somnet.insert_dataset(data);
    somnet.train(300, cfg, true);
    //somnet.train(300, alpha, beta, gama, EXP, true);

    if (output) {

      sprintf(file_name_c, "output/g_output_a%.1f_b%.2f_c%.3f_s%i.c", alpha, beta, gama, a);
      sprintf(file_name_v, "output/g_output_a%.1f_b%.2f_c%.3f_s%i.v", alpha, beta, gama, a);
      somnet.save_to_file2(std::string(file_name_c).c_str(), std::string(file_name_v).c_str(), N_VIEWS);
      sprintf(file_name_c, "output/g_output_a%.1f_b%.2f_c%.3f_s%i.ac", alpha, beta, gama, a);
      sprintf(file_name_v, "output/g_output_a%.1f_b%.2f_c%.3f_s%i.av", alpha, beta, gama, a);
      somnet.save_to_file3(std::string(file_name_c).c_str(), std::string(file_name_v).c_str(), N_VIEWS, EXP);

      sprintf(file_name_c, "motor_%i_%i.txt", a, a);
      //somnet.test(file_name_c, alpha, beta);
    }

    //r.entropy += somnet.entropy();
    //r.qerr += somnet.utils.get_qerr();
    //r.wd += somnet.utils.get_wd();

    //somnet.save_to_file("som.txt");
  }

  r.alpha = alpha;
  r.beta = beta;
  r.gama = gama;
  r.dalpha = dalpha;
  r.entropy /= 1;
  r.qerr /= 1;
  r.wd /= 1;

  result->push_back(r);
}

int save_results(vector<sResult> *result, const char* file) {
	ofstream myfile;
	myfile.open (file);
	

	myfile << "TestID | Alpha | Beta | Gama | dAlpha || Qerror | Entropy | WD " << endl;

	for (unsigned int i = 0; i < result->size(); i++) {
		char row[1000+1] = "";
		sResult	r = result->at(i);
		sprintf(row, "%6.2i | %5.2f | %4.2f | %3.3f| %6.2f || %6.2f | %7.2f | %2.3f ", i, r.alpha, r.beta, r.gama, r.dalpha, r.qerr, r.entropy, r.wd);
		myfile << row << endl;
	}
	myfile.close();

	return 0;
}

void STS_test() {
  CDataSet        visual_data(std::string("dataset/Trajectories.data.3.xy").c_str(), DIMENSION_2, ICUB_DATA, N_VIEWS, 2, 0);
  CDataSet        motor_data(std::string("dataset/Trajectories.data.3.xy").c_str(), DIMENSION_3, ICUB_DATA3D, 0, 2, 63);
  
  sMSOMTrnConfig  stsp_cfg(0.3f, 0.7f, 0.10f, 0.0f, EXP);
  sLSOMTrnConfig  stsa_cfg(0.5f, 0.10f, 0.01f, EXP);
  sMSOMTrnConfig  pmc_cfg(0.3f, 0.5f, 0.02f, 0.0f, EXP);
  
  STS   sts_som(visual_data.get_dim(), 16, motor_data.get_dim(), 12, 12);
  
  sts_som.insert_dataset(&visual_data, &motor_data);
  //sts_som.test(300, pmc_cfg);
  sts_som.train(300, stsa_cfg, stsp_cfg, pmc_cfg);
  sts_som.save2file(stsa_cfg, stsp_cfg, pmc_cfg, EXP);
}

void reverse_test() {
  CDataSet        motor_data(std::string("Trajectories.data.3.xy").c_str(), DIMENSION_3, ICUB_DATA3D, 0, 2, 63);
  sMSOMTrnConfig  pmc_cfg(0.3f, 0.5f, 0.02f, 0.0f, EXP);
  
  MSOM pmc(motor_data.get_dim(), 12, 12);
  
  float         *output;
  vector<float> rev_data(motor_data.get_dim());
  
  pmc.insert_dataset(&motor_data);
  pmc.train(300, pmc_cfg);
  
	list<sSequence>                 *trn_data = motor_data.get_trn_data();
	list<sSequence>::iterator       seq_it;
  list< vector<float> >::iterator	sam_it;

  for (seq_it=trn_data->begin(); seq_it != trn_data->end(); seq_it++) {
    sSequence sample = *seq_it;

    pmc.reset_context();
    for (sam_it = sample.seq.begin(); sam_it != sample.seq.end(); sam_it++) {
      vector<float> s = *sam_it;
      output = pmc.activate(*sam_it, EXP);
      pmc.reverse_activate(output, &rev_data);
      for(int i = 0; i < motor_data.get_dim(); i++) {
        cout << s[i] << " ";
      }
      cout << endl;
      for(int i = 0; i < motor_data.get_dim(); i++) {
        cout << rev_data[i] << " ";
      }
      cout << endl;
    }
    cout << endl;
  }
  
  delete[] output;
}