/* 
 * File:   CUtils.cpp
 * Author: matej
 * 
 * Created on February 6, 2013, 8:03 PM
 */

#include "CUtils.h"
#include <cstdlib>

CUtils::CUtils() {
}

CUtils::CUtils(const CUtils& orig) {
}

CUtils::~CUtils() {
}

int CUtils::rollDice(int k, int n) {
  int result = 0;
  
  for(int i = 0; i < n; i++) {
    result += (rand() % k) + 1;
  }
  
  return result;
}
        
bool CUtils::PointIsInArea(pair<int,int> point, SDL_Rect area) {
  if (point.first >= area.x && point.first <= area.x + area.w) {
    if (point.second >= area.y && point.second <= area.y + area.h) {
      return true;
    }
  }
  return false;
}

