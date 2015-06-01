/* 
 * File:   CMathUtils.cpp
 * Author: Matej Pechac
 * 
 * Created on April 20, 2014, 10:10 PM
 */

#include "CMathUtils.h"
#include <cmath>
#include <random>


CMathUtils::CMathUtils() {
}

CMathUtils::CMathUtils(const CMathUtils& orig) {
}

CMathUtils::~CMathUtils() {
}

double CMathUtils::euclidian_distance(int x1, int y1, int x2, int y2) {
  return euclidian_distance((double)x1, (double)y1, (double)x2, (double)y2);
}

double CMathUtils::euclidian_distance(double x1, double y1, double x2, double y2) {
  double sum;

  sum = pow((x1 - x2), 2) + pow((y1 - y2), 2);

  return sqrt(sum);
}

bool CMathUtils::intersect(int x, int y, int x1, int y1, int x2, int y2) {
  if (x >= x1 && x <= x2 && y >= y1 && y <= y2)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool CMathUtils::intersect(SDL_Rect rect1, SDL_Rect rect2)
{
  //The sides of the rectangles
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;

  //Calculate the sides of rect A
  leftA = rect1.x;
  rightA = rect1.x + rect1.w;
  topA = rect1.y;
  bottomA = rect1.y + rect1.h;

  //Calculate the sides of rect B
  leftB = rect2.x;
  rightB = rect2.x + rect2.w;
  topB = rect2.y;
  bottomB = rect2.y + rect2.h;

   //If any of the sides from A are outside of B
  if( bottomA <= topB )
  {
      return false;
  }

  if( topA >= bottomB )
  {
      return false;
  }

  if( rightA <= leftB )
  {
      return false;
  }

  if( leftA >= rightB )
  {
      return false;
  }
  
  return true;
}

int CMathUtils::find_min(set<int>* find_set, double* array) {
  set<int>::iterator it;
  int min_i = *find_set->begin();
  for(it = find_set->begin(); it != find_set->end(); it++) {
    if (array[*it] < array[min_i]) {
      min_i = *it;
    }
  }
  
  return min_i;
}

int CMathUtils::find_val(int* array, int length, int val) {
  for(int i = 0; i < length; i++) {
    if (array[i] == val) {
      return i;
    }
  }
  
  return -1;  
}

double CMathUtils::gaussian_random(int mean, int sigma)
{
  random_device rd;
  mt19937 e2(rd());
  normal_distribution<> dist(mean, sigma);
  
  return round(dist(e2));
}

