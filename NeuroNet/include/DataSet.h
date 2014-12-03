#include <list>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;


#define NONE            0
#define DIMENSION_N     1
#define DIMENSION_2     2
#define DIMENSION_3     3

#define STOCHASTIC_ROW  1
#define ICUB_DATA       2
#define STOCHASTIC_AUT  3
#define ICUB_DATA3D     4

struct sVertex3D {
    float   x;
    float   y;
    float   z;
};

sVertex3D operator + (const sVertex3D &v1, const sVertex3D &v2);

struct sVertex2D {
    float   x;
    float   y;
};

sVertex2D operator + (const sVertex2D &v1, const sVertex2D &v2);
sVertex2D operator - (const sVertex2D &v1, const sVertex2D &v2);

struct sICubArmJoints {
    float       shoulder_pitch;
    float       shoulder_yaw;
    float       shoulder_roll;
    sVertex3D   elbow;
    float       elbow_pitch;
    sVertex3D   wrist;
    float       wrist_prosup;
    float       wrist_pitch;
    float       wrist_yaw;
    float       hand_finger;
    sVertex3D   thumb;
    float       thumb_oppose;
    float       thumb_proximal;
    float       thumb_distal;
    sVertex3D   index;
    float       index_proximal;
    float       index_distal;
    float       middle_proximal;
    float       middle_distal;
    float       pinky;
    float       ang_thumb_index;
    float       ang_thumb_wrist;
};

struct sICubArm {
    float       shoulder_pitch;
    float       shoulder_yaw;
    float       shoulder_roll;
    float       elbow_pitch;
    float       wrist_prosup;
    float       wrist_pitch;
    float       wrist_yaw;
    float       hand_finger;
    float       thumb_oppose;
    float       thumb_proximal;
    float       thumb_distal;
    float       index_proximal;
    float       index_distal;
    float       middle_proximal;
    float       middle_distal;
    float       pinky;
    sVertex3D   shoulder; // Tazisko klbu v pleci
    sVertex3D   upperArm; // Tazisko stredu hornej casti ramena
    sVertex3D   elbow; // Laktovy klb
    sVertex3D   lowerArm; // Tazisko stredu dolnej casti ramena (medzi laktovym klbom a zapastim)
    sVertex3D   palm; // Stred dlane
    sVertex3D   thumb1; // Prsty, vzdy 1 znamena klb daneho prstu na dlani, 2, 3 a 4 su clanky prsta, kde 4. je posledny (tam kde je nechet)
    sVertex3D   thumb2;
    sVertex3D   thumb3;
    sVertex3D   pointer1;
    sVertex3D   pointer2;
    sVertex3D   pointer3;
    sVertex3D   pointer4;
    sVertex3D   middle1;
    sVertex3D   middle2;
    sVertex3D   middle3;
    sVertex3D   middle4;
    sVertex3D   ring1;
    sVertex3D   ring2;
    sVertex3D   ring3;
    sVertex3D   ring4;
    float       ang_thumb_index;
    float       ang_thumb_wrist;
    float       aperture;
};

struct sICubArmProjection {
    sVertex2D   shoulder; // Tazisko klbu v pleci
    sVertex2D   upperArm; // Tazisko stredu hornej casti ramena
    sVertex2D   elbow; // Laktovy klb
    sVertex2D   lowerArm; // Tazisko stredu dolnej casti ramena (medzi laktovym klbom a zapastim)
    sVertex2D   palm; // Stred dlane
    sVertex2D   thumb1; // Prsty, vzdy 1 znamena klb daneho prstu na dlani, 2, 3 a 4 su clanky prsta, kde 4. je posledny (tam kde je nechet)
    sVertex2D   thumb2;
    sVertex2D   thumb3;
    sVertex2D   pointer1;
    sVertex2D   pointer2;
    sVertex2D   pointer3;
    sVertex2D   pointer4;
    sVertex2D   middle1;
    sVertex2D   middle2;
    sVertex2D   middle3;
    sVertex2D   middle4;
    sVertex2D   ring1;
    sVertex2D   ring2;
    sVertex2D   ring3;
    sVertex2D   ring4;
};

struct sICubArmJointProjection {
    sVertex2D   shoulder;
    sVertex2D   elbow;
    sVertex2D   palm;
    sVertex2D   pointer;
    sVertex2D   thumb;
    double      a_elbow;
    double      a_thumb_proximal;
    double      a_thumb_distal;
    double      a_index_proximal;
    double      a_index_middle;
    double      a_index_distal;
    double      a_middle_proximal;
    double      a_middle_middle;
    double      a_middle_distal;
    double      a_ring_proximal;
    double      a_ring_middle;
    double      a_ring_distal;
};


struct sSequence {
    list< vector<float> > seq;
    int           seq_class;
    int           seq_view;
};

#pragma once
class CDataSet
{
private:
	list<sSequence> dataset;
	list<sSequence> trndata;
	int		size;
  int   length;
	int		dim;
 const char* DELIM;

public:
	CDataSet(const char* file, int mode, int data_type, int n_views, int head_cut, int tail_cut, int dim = 0);
	~CDataSet(void);

	list<sSequence>* get_trn_data();
	int		 get_size()   {return size;};
  int		 get_length() {return length;};
  int    get_dim()    {return dim;};

        

private:
        
	void                Fisher_Yates_shuffle();
	void                normalize(int mode);
  void                clear_invalid_data();

  list<sSequence>     postprocess_data(list<sSequence>* raw_sequence, int n_views, bool savetofile = false);
  sICubArm*           rawdata_to_icubarm(vector<float> *raw_data, sICubArm* arm);
  sICubArmJoints*     rawdata_to_icubarm(vector<float> *raw_data, sICubArmJoints* arm);
  vector<float>*      icubarm_to_trndata(vector<float> *trn_data, sICubArm* arm);
  vector<float>*      icubarm_to_trndata(vector<float> *trn_data, sICubArmJoints* arm);
  vector<float>*      icubarm_to_trndata(vector<float> *trn_data, sICubArmProjection* arm_prj);
  vector<float>*      icubarm_to_trndata(vector<float> *trn_data, sICubArmJointProjection* arm_joint);
  sICubArm*           rotation_operator(sICubArm* arm, double* rot_matrix, sVertex3D* view = NULL);
  sICubArm*           y_rotation_operator(double angle, sICubArm* arm, sVertex3D* view = NULL);
  sICubArm*           x_rotation_operator(double angle, sICubArm* arm, sVertex3D* view = NULL);
  sICubArm*           translation(float x, float y, float z, sICubArm* arm);
  sICubArmProjection* translation(float x, float y, sICubArmProjection* arm_prj);
  sICubArmProjection* projection(sICubArm* arm, sICubArmProjection* arm_prj, float dis = 1.0f);

  sICubArmJointProjection*  icubarmprj_to_icubarmjoint(sICubArmProjection* arm_prj, sICubArmJointProjection* arm_joint);
  double                    angle_of_2vectors(sVertex2D* v1, sVertex2D* v2, sVertex2D* v3);

  // normalization support functions
  void                find_max_vector(int dimension, vector<float> *max_vector);
  void                apply_max_vector(int dimension, vector<float> *max_vector);

};

bool            vector_predicate(vector<float> v1, vector<float> v2);
vector<float>   vector_subtract(vector<float> v1, vector<float> v2);
vector<float>   vector_divide(vector<float> v1, vector<float> v2);
sVertex3D*      matrix_multiple(sVertex3D *v, double* mat);
float           vector_magnitude(sVertex2D *v);
float           dot_product(sVertex2D *v1, sVertex2D *v2);

vector<float>    parse_string(char *s, const char* delim);
vector<string>   split_string(char* s, const char* delim);

