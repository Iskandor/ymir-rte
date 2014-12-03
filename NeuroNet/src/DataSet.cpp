#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <algorithm>
#include <math.h>
#include <assert.h>


#include "DataSet.h"
#include "main.h"

using namespace std;

CDataSet::CDataSet(const char* file, int mode, int data_type, int n_views, int head_cut, int tail_cut, int dim) {
	ifstream	f;
	char		temp[1000+1];
  int             seq_class = 0;
  sSequence       *s = NULL;
  int             length = 0;
  int   step = 0;
	this->dim = dim;

  DELIM = " ,\t";

	f.open(file);
  switch(data_type) {
    
    case STOCHASTIC_ROW:
      if (f.is_open()) {
        s = new sSequence;
        while(!f.eof()) {
          f.getline(temp, 1000+1);

          vector<float> value;
          float v = atof(temp);
          value.push_back(v);

          s->seq.push_back(value);
          length++;
        }
      }
      dataset.push_back(*s);
      this->length = length;
      this->size = dataset.size();
    break;
    
    case ICUB_DATA:
      if (f.is_open()) {
        //s = new sSequence;
        while (!f.eof()) {
          f.getline(temp, 1000+1);
          if (strcmp(temp, "") != 0) {
            vector<float> v = parse_string(temp, DELIM);

            if (v[1] == 1) {
              if (s != NULL) {
                if (!s->seq.empty()) {
                  s->seq_class = seq_class;
                  dataset.push_back(*s);
                }
                seq_class++;
                step = 0;
                if (seq_class == N_GRASPS) {
                  seq_class = 0;
                }
              }
              s = new sSequence;
            }

            vector<float> v_2(v.size()-head_cut);
            for (unsigned int i = head_cut; i < v.size(); i++) {
              v_2[i-head_cut] = v[i];
            }
            if (step > N_STEPS_CUT) {
              s->seq.push_back(v_2);
            }
            step++;
            length++;
          }
        }
      }
      s->seq_class = seq_class;
      dataset.push_back(*s);
      dataset = postprocess_data(&dataset, n_views, true);
      this->size = dataset.size();
      this->length = length;
    break;
    
    case ICUB_DATA3D:
      if (f.is_open()) {
        while (!f.eof()) {
          f.getline(temp, 1000+1);

          if (strcmp(temp, "") != 0) {
            vector<float> v = parse_string(temp, DELIM);

            if (v[1] == 1) {
              if (s != NULL) {
                if (!s->seq.empty()) {
                  s->seq_class = seq_class;
                  dataset.push_back(*s);
                }
                seq_class++;
                step = 0;
                if (seq_class == N_GRASPS) {
                  seq_class = 0;
                }
                //cout << v[0] << " " << s->seq.size() << " " << s->seq_class << endl;
              }
              s = new sSequence;
            }

            vector<float> v_2(v.size()-(head_cut+tail_cut));
            for (unsigned int i = head_cut; i < v.size()-tail_cut; i++) {
              v_2[i-head_cut] = v[i];
            }
            
            if (this->dim == 0) this->dim = v_2.size();
            if (step > N_STEPS_CUT) {
              s->seq.push_back(v_2);
            }
            step++;
            length++;
          }
        }
      }
      s->seq_class = seq_class;
      dataset.push_back(*s);
      //dataset = postprocess_data(&dataset, true);
      //clear_invalid_data();
      this->size = dataset.size();
      this->length = length;
    break;
    
    case STOCHASTIC_AUT:
      if (f.is_open()) {
        s = new sSequence;
        while(!f.eof()) {
          f.getline(temp, 1000+1);
          vector<float> value;

          if (temp[0] == 'a') {
            value.push_back(0);
          }
          if (temp[0] == 'b') {
            value.push_back(1);
          }
          if (!value.empty()) {
            s->seq.push_back(value);
            length++;
          }
        }
      }
      dataset.push_back(*s);
      this->length = length;
      this->size = dataset.size();
    break;
  }
	f.close();

  if (mode != NONE) normalize(mode);
}

CDataSet::~CDataSet(void)
{
}

void CDataSet::Fisher_Yates_shuffle() {
	sSequence* temp_list = new sSequence;
	sSequence temp_val;

	list<sSequence>::iterator	it;
	int	i = 0;
	int	j = 0;

	for (it=dataset.begin(); it != dataset.end(); it++) {
		temp_list[i] = *it;
		i++;
	}

	for (int i = size-1; i > 0; i--) {
		j = (int)((float)rand()/(float)RAND_MAX) * i + 1;
		temp_val = temp_list[j];
		temp_list[j] = temp_list[i];
		temp_list[i] = temp_val;
	}

	trndata.clear();

	for (int i = 0; i < size; i++) {
		trndata.push_front(temp_list[i]);
	}

	delete[] temp_list;
}

list<sSequence>* CDataSet::get_trn_data() {
	//Fisher_Yates_shuffle();
	return &dataset;
}

vector<float> parse_string(char* s, const char* DELIM) {
	vector<string> temp_vec = split_string(s, DELIM); 
  vector<float> result(temp_vec.size());

	for(unsigned int i = 0; i < temp_vec.size(); i++) {
		result[i] = (float)atof(temp_vec[i].c_str());
	}

	return result;
}

vector<string> split_string(char* s, const char* delim) {
    vector<string>	elems;

    char*   tok;

    tok = strtok(s, delim);

    while (tok != NULL)
    {
        string  s_tok(tok);
        elems.push_back(s_tok);
        tok = strtok (NULL, delim);
    }

    return elems;
}

void CDataSet::normalize(int mode) {
	
  vector<float> max_vector;

  switch (mode) {
    case DIMENSION_N: {
      find_max_vector(0, &max_vector);
      apply_max_vector(0, &max_vector);
    }break;
    case DIMENSION_2: {
      find_max_vector(2, &max_vector);
      apply_max_vector(2, &max_vector);
    }break;
    case DIMENSION_3: {
      find_max_vector(3, &max_vector);
      apply_max_vector(3, &max_vector);
    }break;
    default:
    break;
  }
}

void  CDataSet::find_max_vector(int dimension, vector<float>* max_vector) {
  int max_index = 0;

  list<sSequence>::iterator       seq_it;
  list< vector<float> >::iterator sam_it;

  max_vector->clear();
  if (dimension == 0) dimension = dim;

  for(int i = 0; i < dimension; i++) {
    max_vector->push_back(0.0);
  }

  for(seq_it = dataset.begin(); seq_it != dataset.end(); seq_it++) {
    sSequence sample = *seq_it;
    for(sam_it = sample.seq.begin(); sam_it != sample.seq.end(); sam_it++) {
      vector<float> value = *sam_it;
      max_index = 0;
      for (unsigned int i = 0; i < value.size(); i++) {
        if (max_vector->at(max_index) < fabs(value[i])) {
            max_vector->at(max_index) = fabs(value[i]);
        }
        max_index++;
        if (max_index == dimension) max_index = 0;
      }
    }
  }
}

void CDataSet::apply_max_vector(int dimension, vector<float>* max_vector) {
  int max_index = 0;
  list<sSequence> temp_seq;
  list<sSequence>::iterator       seq_it;
  list< vector<float> >::iterator sam_it;

  if (dimension == 0) dimension = dim;

  for(seq_it = dataset.begin(); seq_it != dataset.end(); seq_it++) {
    sSequence sample = *seq_it;
    sSequence temp_sam;
    for(sam_it = sample.seq.begin(); sam_it != sample.seq.end(); sam_it++) {
      vector<float> value = *sam_it;
      vector<float> new_value;
      for (unsigned int i = 0; i < value.size(); i++) {
        float v = value[i] / max_vector->at(max_index);
        new_value.push_back(v);
        max_index++;
        if (max_index == dimension) max_index = 0;
      }
      temp_sam.seq.push_back(new_value);
      temp_sam.seq_class = sample.seq_class;
      temp_sam.seq_view = sample.seq_view;
    }
    temp_seq.push_back(temp_sam);
  }
  dataset = temp_seq;
}

list<sSequence> CDataSet::postprocess_data(list<sSequence>* raw_sequence, int n_views, bool savetofile) {
    list<sSequence>::iterator       seq_it;
    list< vector<float> >::iterator sam_it;
    list<sSequence>     result;
    ofstream            myfile;
    

    if (savetofile) {
        myfile.open(std::string("seq_prj.dat").c_str());
    }
    

    for (seq_it = raw_sequence->begin(); seq_it != raw_sequence->end(); seq_it++) {
      

      sSequence sample = *seq_it;
      double          fi = 0;
      sVertex3D       target;
      sVertex3D       viewpoint;
      sam_it = sample.seq.end();
      sam_it--;
      vector<float>   end_sam = *sam_it;
      sICubArm        end_arm;
      double          psi = 0;

      memset(&target, 0, sizeof(sVertex3D));
      
      rawdata_to_icubarm(&end_sam, &end_arm);

      target = end_arm.pointer4 + end_arm.thumb3;
      target.x /= 2;
      target.y /= 2;
      target.z /= 2;

      /*target.x = 0;
      target.y = 0.5;
      target.z = 0.5;*/

      viewpoint.x = 0;
      viewpoint.y = 0.95;
      viewpoint.z = 0;
      psi = atan(fabs(target.y -viewpoint.y)/fabs(target.z - viewpoint.z));

      for (int i = 0; i < n_views; i++) {
        sSequence       temp_seq;
        for(sam_it = sample.seq.begin(); sam_it != sample.seq.end(); sam_it++) {
          vector<float>       value = *sam_it;
          vector<float>       trn_data;
          sICubArm            arm;
          sICubArmProjection  arm_prj;
          sICubArmJointProjection arm_joint;

          rawdata_to_icubarm(&value, &arm);

          /*rotacia okolo osi y*/
          //sVertex3D new_view = viewpoint;
          translation(-target.x, -target.y, -target.z, &arm);

          /*
          new_view.x -= target.x;
          new_view.y -= target.y;
          new_view.z -= target.z;
          */

          y_rotation_operator(fi, &arm);
          translation(target.x, target.y, target.z, &arm);

          //rotacia okolo osi x
          //translation(-viewpoint.x, -viewpoint.y, -viewpoint.z, &arm);

          /*
          target.x -= viewpoint.x;
          target.y -= viewpoint.y;
          target.z -= viewpoint.z;
          */
          //x_rotation_operator(-psi, &arm);
          //translation(viewpoint.x, viewpoint.y, viewpoint.z, &arm);
          projection(&arm, &arm_prj, 0.05);

          //icubarmprj_to_icubarmjoint(&arm_prj, &arm_joint);

          //icubarm_to_trndata(&trn_data, &arm_joint);
          icubarm_to_trndata(&trn_data, &arm_prj);
          //icubarm_to_trndata(&trn_data, &arm);
          
          if (savetofile) {
              char    tmp[100+1];
/*
              sprintf(tmp, "%.5f %.5f", arm_prj.elbow.x, arm_prj.elbow.y);
              myfile << tmp << endl;
              tmp[0] = '\0';
              sprintf(tmp, "%.5f %.5f", arm_prj.wrist.x, arm_prj.wrist.y);
              myfile << tmp << endl;
              tmp[0] = '\0';
              sprintf(tmp, "%.5f %.5f", arm_prj.index.x, arm_prj.index.y);
              myfile << tmp << endl;
              tmp[0] = '\0';
              sprintf(tmp, "%.5f %.5f\n", arm_prj.thumb.x, arm_prj.thumb.y);
              myfile << tmp << endl;
* */
          }

          temp_seq.seq.push_back(trn_data);

          if (dim == 0) {
              dim = trn_data.size();
          }
        }
        temp_seq.seq_view = i;
        temp_seq.seq_class = sample.seq_class;
        result.push_back(temp_seq);
        fi += M_PI/2;
      }
    }

    if (savetofile) {
        myfile.close();
    }

    return result;
}

vector<float>* CDataSet::icubarm_to_trndata(vector<float>* trn_data, sICubArm* arm) {
    /* Prepisat na push_back !!!*/
    (*trn_data)[0] = arm->shoulder_pitch;
    (*trn_data)[1] = arm->shoulder_roll;
    (*trn_data)[2] = arm->shoulder_yaw;
    (*trn_data)[3] = arm->elbow_pitch;
    (*trn_data)[4] = arm->wrist_prosup;
    (*trn_data)[5] = arm->wrist_pitch;
    (*trn_data)[6] = arm->wrist_yaw;
    (*trn_data)[7] = arm->hand_finger;
    (*trn_data)[8] = arm->thumb_oppose;
    (*trn_data)[9] = arm->thumb_proximal;
    (*trn_data)[10] = arm->thumb_distal;
    (*trn_data)[11] = arm->index_proximal;
    (*trn_data)[12] = arm->index_distal;
    (*trn_data)[13] = arm->middle_proximal;
    (*trn_data)[14] = arm->middle_distal;
    (*trn_data)[15] = arm->pinky;
//    (*trn_data)[16] = arm->wrist.x;
//    (*trn_data)[17] = arm->wrist.y;
//    (*trn_data)[18] = arm->wrist.z;
    (*trn_data)[19] = arm->elbow.x;
    (*trn_data)[20] = arm->elbow.y;
    (*trn_data)[21] = arm->elbow.z;
//    (*trn_data)[22] = arm->thumb.x;
//    (*trn_data)[23] = arm->thumb.y;
//    (*trn_data)[24] = arm->thumb.z;
//    (*trn_data)[25] = arm->index.x;
//    (*trn_data)[26] = arm->index.y;
//    (*trn_data)[27] = arm->index.z;
    (*trn_data)[28] = arm->ang_thumb_wrist;
    (*trn_data)[29] = arm->ang_thumb_index;

    return trn_data;
}

vector<float>* CDataSet::icubarm_to_trndata(vector<float>* trn_data, sICubArmProjection* arm_prj) {
    trn_data->push_back(arm_prj->shoulder.x);
    trn_data->push_back(arm_prj->shoulder.y);
    trn_data->push_back(arm_prj->upperArm.x);
    trn_data->push_back(arm_prj->upperArm.y);
    trn_data->push_back(arm_prj->elbow.x);
    trn_data->push_back(arm_prj->elbow.y);
    trn_data->push_back(arm_prj->lowerArm.x);
    trn_data->push_back(arm_prj->lowerArm.y);
    trn_data->push_back(arm_prj->palm.x);
    trn_data->push_back(arm_prj->palm.y);
    trn_data->push_back(arm_prj->thumb1.x);
    trn_data->push_back(arm_prj->thumb1.y);
    trn_data->push_back(arm_prj->thumb2.x);
    trn_data->push_back(arm_prj->thumb2.y);
    trn_data->push_back(arm_prj->thumb3.x);
    trn_data->push_back(arm_prj->thumb3.y);
    trn_data->push_back(arm_prj->pointer1.x);
    trn_data->push_back(arm_prj->pointer1.y);
    trn_data->push_back(arm_prj->pointer2.x);
    trn_data->push_back(arm_prj->pointer2.y);
    trn_data->push_back(arm_prj->pointer3.x);
    trn_data->push_back(arm_prj->pointer3.y);
    trn_data->push_back(arm_prj->pointer4.x);
    trn_data->push_back(arm_prj->pointer4.y);
    trn_data->push_back(arm_prj->middle1.x);
    trn_data->push_back(arm_prj->middle1.y);
    trn_data->push_back(arm_prj->middle2.x);
    trn_data->push_back(arm_prj->middle2.y);
    trn_data->push_back(arm_prj->middle3.x);
    trn_data->push_back(arm_prj->middle3.y);
    trn_data->push_back(arm_prj->middle4.x);
    trn_data->push_back(arm_prj->middle4.y);
    trn_data->push_back(arm_prj->ring1.x);
    trn_data->push_back(arm_prj->ring1.y);
    trn_data->push_back(arm_prj->ring2.x);
    trn_data->push_back(arm_prj->ring2.y);
    trn_data->push_back(arm_prj->ring3.x);
    trn_data->push_back(arm_prj->ring3.y);
    trn_data->push_back(arm_prj->ring4.x);
    trn_data->push_back(arm_prj->ring4.y);

    /*
    float   ang = angle_of_2vectors(&arm_prj->thumb, &arm_prj->wrist, &arm_prj->index);
    if (ang != ang ) {
        assert(0);
    }

    trn_data->push_back(ang);

    ang = angle_of_2vectors(&arm_prj->elbow, &arm_prj->wrist, &arm_prj->thumb);
    if (ang != ang ) {
        assert(0);
    }

    trn_data->push_back(ang);
    */


    return trn_data;
}

vector<float>* CDataSet::icubarm_to_trndata(vector<float>* trn_data, sICubArmJointProjection* arm_joint) {
    trn_data->push_back(arm_joint->shoulder.x);
    trn_data->push_back(arm_joint->shoulder.y);
    trn_data->push_back(arm_joint->elbow.x);
    trn_data->push_back(arm_joint->elbow.y);
    trn_data->push_back(arm_joint->palm.x);
    trn_data->push_back(arm_joint->palm.y);
    trn_data->push_back(arm_joint->thumb.x);
    trn_data->push_back(arm_joint->thumb.y);
    trn_data->push_back(arm_joint->pointer.x);
    trn_data->push_back(arm_joint->pointer.y);
    trn_data->push_back(arm_joint->a_elbow);
    trn_data->push_back(arm_joint->a_index_distal);
    trn_data->push_back(arm_joint->a_index_middle);
    trn_data->push_back(arm_joint->a_index_proximal);
    trn_data->push_back(arm_joint->a_middle_distal);
    trn_data->push_back(arm_joint->a_middle_middle);
    trn_data->push_back(arm_joint->a_middle_proximal);
    trn_data->push_back(arm_joint->a_ring_distal);
    trn_data->push_back(arm_joint->a_ring_middle);
    trn_data->push_back(arm_joint->a_ring_proximal);
    trn_data->push_back(arm_joint->a_thumb_distal);
    trn_data->push_back(arm_joint->a_thumb_proximal);

    return trn_data;
}

vector<float>* CDataSet::icubarm_to_trndata(vector<float>* trn_data, sICubArmJoints* arm) {
    trn_data->push_back(arm->shoulder_pitch);
    trn_data->push_back(arm->shoulder_roll);
    trn_data->push_back(arm->shoulder_yaw);
    trn_data->push_back(arm->elbow_pitch);
    trn_data->push_back(arm->wrist_prosup);
    trn_data->push_back(arm->wrist_pitch);
    trn_data->push_back(arm->wrist_yaw);
    trn_data->push_back(arm->hand_finger);
    trn_data->push_back(arm->thumb_oppose);
    trn_data->push_back(arm->thumb_proximal);
    trn_data->push_back(arm->thumb_distal);
    trn_data->push_back(arm->index_proximal);
    trn_data->push_back(arm->index_distal);
    trn_data->push_back(arm->middle_proximal);
    trn_data->push_back(arm->middle_distal);
    trn_data->push_back(arm->pinky);
    trn_data->push_back(arm->wrist.x);
    trn_data->push_back(arm->wrist.y);
    trn_data->push_back(arm->wrist.z);
    trn_data->push_back(arm->elbow.x);
    trn_data->push_back(arm->elbow.y);
    trn_data->push_back(arm->elbow.z);
    trn_data->push_back(arm->thumb.x);
    trn_data->push_back(arm->thumb.y);
    trn_data->push_back(arm->thumb.z);
    trn_data->push_back(arm->index.x);
    trn_data->push_back(arm->index.y);
    trn_data->push_back(arm->index.z);
    trn_data->push_back(arm->ang_thumb_wrist);
    trn_data->push_back(arm->ang_thumb_index);

    return trn_data;
}

sICubArm* CDataSet::rawdata_to_icubarm(vector<float> *raw_data, sICubArm* arm) {
    
    arm->shoulder_pitch = (*raw_data)[0];
    arm->shoulder_roll = (*raw_data)[1];
    arm->shoulder_yaw = (*raw_data)[2];
    arm->elbow_pitch = (*raw_data)[3];
    arm->wrist_prosup = (*raw_data)[4];
    arm->wrist_pitch = (*raw_data)[5];
    arm->wrist_yaw = (*raw_data)[6];
    arm->hand_finger = (*raw_data)[7];
    arm->thumb_oppose = (*raw_data)[8];
    arm->thumb_proximal = (*raw_data)[9];
    arm->thumb_distal = (*raw_data)[10];
    arm->index_proximal = (*raw_data)[11];
    arm->index_distal = (*raw_data)[12];
    arm->middle_proximal = (*raw_data)[13];
    arm->middle_distal = (*raw_data)[14];
    arm->pinky = (*raw_data)[15];
    arm->shoulder.x = (*raw_data)[16];
    arm->shoulder.y = (*raw_data)[17];
    arm->shoulder.z = (*raw_data)[18];
    arm->upperArm.x = (*raw_data)[19];
    arm->upperArm.y = (*raw_data)[20];
    arm->upperArm.z = (*raw_data)[21];
    arm->elbow.x = (*raw_data)[22];
    arm->elbow.y = (*raw_data)[23];
    arm->elbow.z = (*raw_data)[24];
    arm->lowerArm.x = (*raw_data)[25];
    arm->lowerArm.y = (*raw_data)[26];
    arm->lowerArm.z = (*raw_data)[27];
    arm->palm.x = (*raw_data)[28];
    arm->palm.y = (*raw_data)[29];
    arm->palm.z = (*raw_data)[30];
    arm->thumb1.x = (*raw_data)[31];
    arm->thumb1.y = (*raw_data)[32];
    arm->thumb1.z = (*raw_data)[33];
    arm->thumb2.x = (*raw_data)[34];
    arm->thumb2.y = (*raw_data)[35];
    arm->thumb2.z = (*raw_data)[36];
    arm->thumb3.x = (*raw_data)[37];
    arm->thumb3.y = (*raw_data)[38];
    arm->thumb3.z = (*raw_data)[39];
    arm->pointer1.x = (*raw_data)[40];
    arm->pointer1.y = (*raw_data)[41];
    arm->pointer1.z = (*raw_data)[42];
    arm->pointer2.x = (*raw_data)[43];
    arm->pointer2.y = (*raw_data)[44];
    arm->pointer2.z = (*raw_data)[45];
    arm->pointer3.x = (*raw_data)[46];
    arm->pointer3.y = (*raw_data)[47];
    arm->pointer3.z = (*raw_data)[48];
    arm->pointer4.x = (*raw_data)[49];
    arm->pointer4.y = (*raw_data)[50];
    arm->pointer4.z = (*raw_data)[51];
    arm->middle1.x = (*raw_data)[52];
    arm->middle1.y = (*raw_data)[53];
    arm->middle1.z = (*raw_data)[54];
    arm->middle2.x = (*raw_data)[55];
    arm->middle2.y = (*raw_data)[56];
    arm->middle2.z = (*raw_data)[57];
    arm->middle3.x = (*raw_data)[58];
    arm->middle3.y = (*raw_data)[59];
    arm->middle3.z = (*raw_data)[60];
    arm->middle4.x = (*raw_data)[61];
    arm->middle4.y = (*raw_data)[62];
    arm->middle4.z = (*raw_data)[63];
    arm->ring1.x = (*raw_data)[64];
    arm->ring1.y = (*raw_data)[65];
    arm->ring1.z = (*raw_data)[66];
    arm->ring2.x = (*raw_data)[67];
    arm->ring2.y = (*raw_data)[68];
    arm->ring2.z = (*raw_data)[69];
    arm->ring3.x = (*raw_data)[70];
    arm->ring3.y = (*raw_data)[71];
    arm->ring3.z = (*raw_data)[72];
    arm->ring4.x = (*raw_data)[73];
    arm->ring4.y = (*raw_data)[74];
    arm->ring4.z = (*raw_data)[75];
    arm->ang_thumb_wrist = (*raw_data)[76];
    arm->ang_thumb_index = (*raw_data)[77];

    return arm;
}

sICubArmJoints* CDataSet::rawdata_to_icubarm(vector<float>* raw_data, sICubArmJoints* arm) {
  
    arm->shoulder_pitch = (*raw_data)[0];
    arm->shoulder_roll = (*raw_data)[1];
    arm->shoulder_yaw = (*raw_data)[2];
    arm->elbow_pitch = (*raw_data)[3];
    arm->wrist_prosup = (*raw_data)[4];
    arm->wrist_pitch = (*raw_data)[5];
    arm->wrist_yaw = (*raw_data)[6];
    arm->hand_finger = (*raw_data)[7];
    arm->thumb_oppose = (*raw_data)[8];
    arm->thumb_proximal = (*raw_data)[9];
    arm->thumb_distal = (*raw_data)[10];
    arm->index_proximal = (*raw_data)[11];
    arm->index_distal = (*raw_data)[12];
    arm->middle_proximal = (*raw_data)[13];
    arm->middle_distal = (*raw_data)[14];
    arm->pinky = (*raw_data)[15];
    arm->elbow.x = (*raw_data)[16];
    arm->elbow.y = (*raw_data)[17];
    arm->elbow.z = (*raw_data)[18];
    arm->wrist.x = (*raw_data)[19];
    arm->wrist.y = (*raw_data)[20];
    arm->wrist.z = (*raw_data)[21];
    arm->thumb.x = (*raw_data)[25];
    arm->thumb.y = (*raw_data)[26];
    arm->thumb.z = (*raw_data)[27];
    arm->index.x = (*raw_data)[28];
    arm->index.y = (*raw_data)[29];
    arm->index.z = (*raw_data)[30];
    arm->ang_thumb_wrist = (*raw_data)[31];
    arm->ang_thumb_index = (*raw_data)[32];

    return arm;
}

sICubArm* CDataSet::rotation_operator(sICubArm* arm, double* rot_matrix, sVertex3D* view) {

    arm->shoulder = *matrix_multiple(&arm->shoulder, rot_matrix);
    arm->upperArm = *matrix_multiple(&arm->upperArm, rot_matrix);
    arm->elbow = *matrix_multiple(&arm->elbow, rot_matrix);
    arm->lowerArm = *matrix_multiple(&arm->lowerArm, rot_matrix);
    arm->palm = *matrix_multiple(&arm->palm, rot_matrix);
    arm->thumb1 = *matrix_multiple(&arm->thumb1, rot_matrix);
    arm->thumb2 = *matrix_multiple(&arm->thumb2, rot_matrix);
    arm->thumb3 = *matrix_multiple(&arm->thumb3, rot_matrix);
    arm->pointer1 = *matrix_multiple(&arm->pointer1, rot_matrix);
    arm->pointer2 = *matrix_multiple(&arm->pointer2, rot_matrix);
    arm->pointer3 = *matrix_multiple(&arm->pointer3, rot_matrix);
    arm->pointer4 = *matrix_multiple(&arm->pointer4, rot_matrix);
    arm->middle1 = *matrix_multiple(&arm->middle1, rot_matrix);
    arm->middle2 = *matrix_multiple(&arm->middle2, rot_matrix);
    arm->middle3 = *matrix_multiple(&arm->middle3, rot_matrix);
    arm->middle4 = *matrix_multiple(&arm->middle4, rot_matrix);
    arm->ring1 = *matrix_multiple(&arm->ring1, rot_matrix);
    arm->ring2 = *matrix_multiple(&arm->ring2, rot_matrix);
    arm->ring3 = *matrix_multiple(&arm->ring3, rot_matrix);
    arm->ring4 = *matrix_multiple(&arm->ring4, rot_matrix);
            
    if (view != NULL) matrix_multiple(view, rot_matrix);

    return arm;
}

sICubArm* CDataSet::y_rotation_operator(double angle, sICubArm* arm, sVertex3D* view) {
    double rot_matrix[9] = { cos(angle) , 0 , sin(angle),
                             0          , 1 , 0         ,
                            -sin(angle) , 0 , cos(angle)};

    rotation_operator(arm, rot_matrix, view);

    return arm;
}

sICubArm* CDataSet::x_rotation_operator(double angle, sICubArm* arm, sVertex3D* view) {
    double rot_matrix[9] = { 1 , 0          , 0,
                             0 , cos(angle) , -sin(angle),
                             0 , sin(angle) , cos(angle)};

    rotation_operator(arm, rot_matrix, view);

    return arm;
}

sICubArm* CDataSet::translation(float x, float y, float z, sICubArm* arm) {
    sVertex3D   trans_vertex;

    trans_vertex.x = x;
    trans_vertex.y = y;
    trans_vertex.z = z;

    arm->shoulder = arm->shoulder + trans_vertex;
    arm->upperArm = arm->upperArm + trans_vertex;
    arm->elbow = arm->elbow + trans_vertex;
    arm->lowerArm = arm->lowerArm + trans_vertex;
    arm->palm = arm->palm + trans_vertex;
    arm->thumb1 = arm->thumb1 + trans_vertex;
    arm->thumb2 = arm->thumb2 + trans_vertex;
    arm->thumb3 = arm->thumb3 + trans_vertex;
    arm->pointer1 = arm->pointer1 + trans_vertex;
    arm->pointer2 = arm->pointer2 + trans_vertex;
    arm->pointer3 = arm->pointer3 + trans_vertex;
    arm->pointer4 = arm->pointer4 + trans_vertex;
    arm->middle1 = arm->middle1 + trans_vertex;
    arm->middle2 = arm->middle2 + trans_vertex;
    arm->middle3 = arm->middle3 + trans_vertex;
    arm->middle4 = arm->middle4 + trans_vertex;
    arm->ring1 = arm->ring1 + trans_vertex;
    arm->ring2 = arm->ring2 + trans_vertex;
    arm->ring3 = arm->ring3 + trans_vertex;
    arm->ring4 = arm->ring4 + trans_vertex;

    return arm;
}

sICubArmProjection* CDataSet::translation(float x, float y, sICubArmProjection* arm) {
    sVertex2D   trans_vertex;

    trans_vertex.x = x;
    trans_vertex.y = y;

    arm->shoulder = arm->shoulder + trans_vertex;
    arm->upperArm = arm->upperArm + trans_vertex;
    arm->elbow = arm->elbow + trans_vertex;
    arm->lowerArm = arm->lowerArm + trans_vertex;
    arm->palm = arm->palm + trans_vertex;
    arm->thumb1 = arm->thumb1 + trans_vertex;
    arm->thumb2 = arm->thumb2 + trans_vertex;
    arm->thumb3 = arm->thumb3 + trans_vertex;
    arm->pointer1 = arm->pointer1 + trans_vertex;
    arm->pointer2 = arm->pointer2 + trans_vertex;
    arm->pointer3 = arm->pointer3 + trans_vertex;
    arm->pointer4 = arm->pointer4 + trans_vertex;
    arm->middle1 = arm->middle1 + trans_vertex;
    arm->middle2 = arm->middle2 + trans_vertex;
    arm->middle3 = arm->middle3 + trans_vertex;
    arm->middle4 = arm->middle4 + trans_vertex;
    arm->ring1 = arm->ring1 + trans_vertex;
    arm->ring2 = arm->ring2 + trans_vertex;
    arm->ring3 = arm->ring3 + trans_vertex;
    arm->ring4 = arm->ring4 + trans_vertex;

    return arm;
}

sICubArmProjection* CDataSet::projection(sICubArm* arm, sICubArmProjection* arm_prj, float dis) {

  arm_prj->shoulder.x = arm->shoulder.x / arm->shoulder.z * dis;
  arm_prj->shoulder.y = arm->shoulder.y / arm->shoulder.z * dis;
  arm_prj->upperArm.x = arm->upperArm.x / arm->upperArm.z * dis;
  arm_prj->upperArm.y = arm->upperArm.y / arm->upperArm.z * dis;
  arm_prj->elbow.x = arm->elbow.x / arm->elbow.z * dis;
  arm_prj->elbow.y = arm->elbow.y / arm->elbow.z * dis;
  arm_prj->lowerArm.x = arm->lowerArm.x / arm->lowerArm.z * dis;
  arm_prj->lowerArm.y = arm->lowerArm.y / arm->lowerArm.z * dis;
  arm_prj->palm.x = arm->palm.x / arm->palm.z * dis;
  arm_prj->palm.y = arm->palm.y / arm->palm.z * dis;
  arm_prj->thumb1.x = arm->thumb1.x / arm->thumb1.z * dis;
  arm_prj->thumb1.y = arm->thumb1.y / arm->thumb1.z * dis;
  arm_prj->thumb2.x = arm->thumb2.x / arm->thumb2.z * dis;
  arm_prj->thumb2.y = arm->thumb2.y / arm->thumb2.z * dis;
  arm_prj->thumb3.x = arm->thumb3.x / arm->thumb3.z * dis;
  arm_prj->thumb3.y = arm->thumb3.y / arm->thumb3.z * dis;
  arm_prj->pointer1.x = arm->pointer1.x / arm->pointer1.z * dis;
  arm_prj->pointer1.y = arm->pointer1.y / arm->pointer1.z * dis;
  arm_prj->pointer2.x = arm->pointer2.x / arm->pointer2.z * dis;
  arm_prj->pointer2.y = arm->pointer2.y / arm->pointer2.z * dis;
  arm_prj->pointer3.x = arm->pointer3.x / arm->pointer3.z * dis;
  arm_prj->pointer3.y = arm->pointer3.y / arm->pointer3.z * dis;
  arm_prj->pointer4.x = arm->pointer4.x / arm->pointer4.z * dis;
  arm_prj->pointer4.y = arm->pointer4.y / arm->pointer4.z * dis;
  arm_prj->middle1.x = arm->middle1.x / arm->middle1.z * dis;
  arm_prj->middle1.y = arm->middle1.y / arm->middle1.z * dis;
  arm_prj->middle2.x = arm->middle2.x / arm->middle2.z * dis;
  arm_prj->middle2.y = arm->middle2.y / arm->middle2.z * dis;
  arm_prj->middle3.x = arm->middle3.x / arm->middle3.z * dis;
  arm_prj->middle3.y = arm->middle3.y / arm->middle3.z * dis;
  arm_prj->middle4.x = arm->middle4.x / arm->middle4.z * dis;
  arm_prj->middle4.y = arm->middle4.y / arm->middle4.z * dis;
  arm_prj->ring1.x = arm->ring1.x / arm->ring1.z * dis;
  arm_prj->ring1.y = arm->ring1.y / arm->ring1.z * dis;
  arm_prj->ring2.x = arm->ring2.x / arm->ring2.z * dis;
  arm_prj->ring2.y = arm->ring2.y / arm->ring2.z * dis;
  arm_prj->ring3.x = arm->ring3.x / arm->ring3.z * dis;
  arm_prj->ring3.y = arm->ring3.y / arm->ring3.z * dis;
  arm_prj->ring4.x = arm->ring4.x / arm->ring4.z * dis;
  arm_prj->ring4.y = arm->ring4.y / arm->ring4.z * dis;

  return arm_prj;
}

sICubArmJointProjection* CDataSet::icubarmprj_to_icubarmjoint(sICubArmProjection* arm_prj, sICubArmJointProjection* arm_joint) {
  arm_joint->shoulder = arm_prj->shoulder;
  arm_joint->elbow = arm_prj->elbow;
  arm_joint->palm = arm_prj->palm;
  arm_joint->thumb = arm_prj->thumb3;
  arm_joint->pointer = arm_prj->pointer4;
  arm_joint->a_elbow = angle_of_2vectors(&arm_prj->shoulder, &arm_prj->elbow, &arm_prj->palm);
  arm_joint->a_index_distal = angle_of_2vectors(&arm_prj->pointer2, &arm_prj->pointer3, &arm_prj->pointer4);
  arm_joint->a_index_middle = angle_of_2vectors(&arm_prj->pointer1, &arm_prj->pointer2, &arm_prj->pointer3);
  arm_joint->a_index_proximal = angle_of_2vectors(&arm_prj->palm, &arm_prj->pointer1, &arm_prj->pointer2);
  arm_joint->a_middle_distal = angle_of_2vectors(&arm_prj->middle2, &arm_prj->middle3, &arm_prj->middle4);
  arm_joint->a_middle_middle = angle_of_2vectors(&arm_prj->middle1, &arm_prj->middle2, &arm_prj->middle3);
  arm_joint->a_middle_proximal = angle_of_2vectors(&arm_prj->palm, &arm_prj->middle1, &arm_prj->middle2);
  arm_joint->a_ring_distal = angle_of_2vectors(&arm_prj->ring2, &arm_prj->ring3, &arm_prj->ring4);
  arm_joint->a_ring_middle = angle_of_2vectors(&arm_prj->ring1, &arm_prj->ring2, &arm_prj->ring3);
  arm_joint->a_ring_proximal = angle_of_2vectors(&arm_prj->palm, &arm_prj->ring1, &arm_prj->ring2);
  arm_joint->a_thumb_distal = angle_of_2vectors(&arm_prj->thumb1, &arm_prj->thumb2, &arm_prj->thumb3);
  arm_joint->a_thumb_proximal = angle_of_2vectors(&arm_prj->palm, &arm_prj->thumb1, &arm_prj->thumb2);

  return arm_joint;
}

double CDataSet::angle_of_2vectors(sVertex2D* v1, sVertex2D* v2, sVertex2D* v3) {
    sVertex2D vector1 = *v2 - *v1;
    sVertex2D vector2 = *v2 - *v3;

    double r = 0.0;

    r = dot_product(&vector1, &vector2);
    r /= (vector_magnitude(&vector1) * vector_magnitude(&vector2));

    if (r > 1) {
      r = 1;
    }
    if (r < -1) {
      r = -1;
    }

    double psi = acos(r);

    if (psi != psi) {
      assert(0);
    }

    return psi;
}

void CDataSet::clear_invalid_data() {
  list<sSequence>::iterator         seq_it;
  
	for (seq_it=dataset.begin(); seq_it != dataset.end(); seq_it++) {
		sSequence sample = *seq_it;
    
    if (sample.seq.size() == 0) {
      dataset.erase(seq_it);
    }
  }
}

bool vector_predicate(vector<float> v1, vector<float> v2) {
	float	vs1 = 0;
	float	vs2 = 0;

	for (unsigned int i = 0; i < v1.size(); i++) {
		vs1 += pow(v1[i], 2);
		vs2 += pow(v2[i], 2);
	}

	vs1 = sqrt(vs1);
	vs2 = sqrt(vs2);

	return (vs1 < vs2);
}

vector<float> vector_subtract(vector<float> v1, vector<float> v2) {
	vector<float> r(v1.size());

	for (unsigned int i = 0; i < v1.size(); i++) {
		r[i] = v1[i] - v2[i];
	}

	return r;
}

vector<float> vector_divide(vector<float> v1, vector<float> v2) {
	vector<float> r(v1.size());



	for (unsigned int i = 0; i < v1.size(); i++) {
		r[i] = v1[i] / v2[i];
	}

	return r;
}

sVertex3D* matrix_multiple(sVertex3D *v, double* mat) {
    sVertex3D   temp_v = *v;

    for (int i = 0; i < 3; i++) {
        double sum = 0;
        sum += *(mat+i*3+0) * temp_v.x;
        sum += *(mat+i*3+1) * temp_v.y;
        sum += *(mat+i*3+2) * temp_v.z;

        switch(i) {
            case 0:
                v->x = sum;
                break;
            case 1:
                v->y = sum;
                break;
            case 2:
                v->z = sum;
                break;
        }
    }

    return v;
}

sVertex3D operator + (const sVertex3D &v1, const sVertex3D &v2) {
    sVertex3D   r;
    r.x = v1.x + v2.x;
    r.y = v1.y + v2.y;
    r.z = v1.z + v2.z;
    return r;
}

sVertex2D operator + (const sVertex2D &v1, const sVertex2D &v2) {
    sVertex2D   r;
    r.x = v1.x + v2.x;
    r.y = v1.y + v2.y;
    return r;
}

sVertex2D operator - (const sVertex2D &v1, const sVertex2D &v2) {
    sVertex2D   r;
    r.x = v1.x - v2.x;
    r.y = v1.y - v2.y;
    return r;
}

/*
sVertex2D operator = (const sVertex2D &v1) {
    sVertex2D   r;
    r.x = v1.x;
    r.y = v1.y;
    return r;
}*/

float vector_magnitude(sVertex2D* v) {
    float r = 0;

    r+= v->x * v->x;
    r+= v->y * v->y;

    return sqrt(r);
}

float dot_product(sVertex2D *v1, sVertex2D *v2) {
    float r = 0;

    r+= v1->x * v2->x;
    r+= v1->y * v2->y;

    return r;
}
