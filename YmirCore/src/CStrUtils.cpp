/* 
 * File:   newClass.cpp
 * Author: matej
 * 
 * Created on April 5, 2014, 4:42 PM
 */

#include "CStrUtils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

CStrUtils::CStrUtils() {
}

CStrUtils::CStrUtils(const CStrUtils& orig) {
}

CStrUtils::~CStrUtils() {
}

void CStrUtils::EraseBuffer(char* buffer, int size) {
  memset(buffer, 0, sizeof(char) * size);
}

string CStrUtils::ImplodeToString(int* array, int length) {
  char  tmp[3+1];
  string result;
  
  for(int i = 0; i < length; i++) {
    sprintf(tmp, "%i", array[i]);
    result.append(tmp);
    result.append("|");
  }
  
  return result;
}

void CStrUtils::ExplodeFromString(string source, int* array) {
  int i = 0;
  string next = "";

  for (string::const_iterator it = source.begin(); it != source.end(); it++) {
    if (*it == '|') {
      if (next.length() > 0) {
        array[i] = atoi(next.c_str());
        next = "";
        i++;
      }
    } else {
      next += *it;
    }
  }
}

