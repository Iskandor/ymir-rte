/* 
 * File:   CPictureRender.h
 * Author: matej
 *
 * Created on May 23, 2015, 8:09 AM
 */

#ifndef CPICTURERENDER_H
#define	CPICTURERENDER_H

#include "SortedLinkedList.h"

using namespace std;

class CPictureRender : public SortedLinkedList {
public:
  CPictureRender();
  CPictureRender(const CPictureRender& orig);
  virtual ~CPictureRender();
  
  void SortObjects(CPicture* picture);
  
private:
  
};

#endif	/* CPICTURERENDER_H */

