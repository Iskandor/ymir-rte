/* 
 * File:   newClass.h
 * Author: Matej Pechac
 *
 * Created on April 5, 2014, 4:42 PM
 */

#ifndef CSTRUTILS_H
#define	CSTRUTILS_H

#include <string>

using namespace std;

class CStrUtils {
public:
  CStrUtils();
  CStrUtils(const CStrUtils& orig);
  virtual ~CStrUtils();

  static void EraseBuffer(char* buffer, int size);
  static string ImplodeToString(int* array, int length);
  static void ExplodeFromString(string source, int* array);
};

#endif	/* NEWCLASS_H */

