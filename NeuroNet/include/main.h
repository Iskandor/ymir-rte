#include <vector>
#include "DataSet.h"

#define N_GRASPS 3
#define N_VIEWS  4
#define N_STEPS_CUT 4
                              //M    //V
#define HEAD_CUT        2     //2    //2
#define TAIL_CUT        0     //63   //0

#define GRASP_1  "power grasp"
#define GRASP_2  "side grasp"
#define GRASP_3  "precision grasp"

struct sResult {
	float	wd;
	float	entropy;
	float	qerr;

	float alpha;
	float beta;
	float gama;
	float dalpha;
};


void test(CDataSet* data, int a, float alpha, float beta, float gama, float dalpha, vector<sResult> *result, bool output);
void STS_test();
void reverse_test();
int  save_results(vector<sResult> *result, const char* file);

