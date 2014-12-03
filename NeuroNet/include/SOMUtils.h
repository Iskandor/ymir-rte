/* 
 * File:   SOMUtils.h
 * Author: Matej Pechac
 *
 * Created on April 7, 2013, 10:13 AM
 */

#include <set>
#include <utility>

using namespace std;

#ifndef SOMUTILS_H
#define	SOMUTILS_H


bool    compare_pair_kwta(pair<int, float> p1, pair<int, float> p2);

class SOMUtils {
public:
  SOMUtils();
  SOMUtils(const SOMUtils& orig);
  virtual ~SOMUtils();
  
  void    update_wd(int n);
  void    calc_wd(int size);
  double  get_wd();
  void    reset_wd();
  void    update_qerr(float error);
  float   get_qerr();
  void    reset_qerr();
  
  void    filter_kwta(int k, float* activation, int size);
  void    filter_threshold(float theta, float* activation, int size);
private:
  
private:
	set<int>	winner_set;
	float     qerr;
  double    wd;
};

#endif	/* SOMUTILS_H */

