/* 
 * File:   CMathUtils.h
 * Author: matej
 *
 * Created on April 20, 2014, 10:10 PM
 */

#ifndef CMATHUTILS_H
#define	CMATHUTILS_H

#include <set>
#include <SDL/SDL.h>

using namespace std;

class CMathUtils {
public:
  CMathUtils();
  CMathUtils(const CMathUtils& orig);
  virtual ~CMathUtils();
  
  static double euclidian_distance(int x1, int y1, int x2, int y2);
  static double euclidian_distance(double x1, double y1, double x2, double y2);
  static int    find_min(set<int>* find_set, double* array);
  static int    find_val(int* array, int length, int val);
  static bool   intersect(SDL_Rect rect1, SDL_Rect rect2);
  static bool   intersect(int x, int y, int x1, int y1, int x2, int y2);
  static double gaussian_random(int mean, int sigma);
private:

};

#endif	/* CMATHUTILS_H */

