/* 
 * File:   CUtils.h
 * Author: Matej Pechac
 *
 * Created on February 6, 2013, 8:03 PM
 */

#ifndef CUTILS_H
#define	CUTILS_H

#include <SDL/SDL.h>
#include <utility> 

using namespace std;

class CUtils {
public:
  CUtils();
  CUtils(const CUtils& orig);
  virtual ~CUtils();
  
  static int    rollDice(int k, int n);
  static double Probability(int r);
  static bool   PointIsInArea(pair<int, int> point, SDL_Rect area);
};

#endif	/* CUTILS_H */

