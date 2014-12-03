/* 
 * File:   STS.h
 * Author: Matej Pechac
 *
 * Created on April 14, 2013, 8:25 PM
 */

#include "MSOM.h"
#include "LSOM.h"
#include "DataSet.h"
#include "SOMUtils.h"

#ifndef STS_H
#define	STS_H

class STS {
public:
  STS(int stsp_input_dim, int stsp_size, int motor_input_dim, int motor_size, int stsa_size);
  STS(const STS& orig);
  virtual ~STS();
  
  void	insert_dataset(CDataSet* visual, CDataSet* motor);
  void  train(int epochs, sLSOMTrnConfig cfgSTSa, sMSOMTrnConfig cfgSTSp, sMSOMTrnConfig cfgPMC, bool loging = false);
  void  test(int epochs, sMSOMTrnConfig cfgSTSp);
  
  void  save2file(sLSOMTrnConfig cfgSTSa, sMSOMTrnConfig cfgSTSp, sMSOMTrnConfig cfgPMC, int mode);
private:
  void  concat_vector(vector<float> *input1, vector<float> *input2, vector<float> *output);
  void  concat_array(float *input1, int size1, float *input2, int size2, vector<float> *output);
private:
  CDataSet*  visual_data;
  CDataSet*  motor_data;
  SOMUtils   utils;
  
  MSOM* STSp;
  LSOM* STSa;
  MSOM* PMC;
};

#endif	/* STS_H */

