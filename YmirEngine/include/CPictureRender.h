/* 
 * File:   CPictureRender.h
 * Author: matej
 *
 * Created on May 23, 2015, 8:09 AM
 */

#ifndef CPICTURERENDER_H
#define	CPICTURERENDER_H

#include <map>
#include "CPicture.h"

using namespace std;

class CPictureRender {
public:
  CPictureRender();
  CPictureRender(const CPictureRender& orig);
  virtual ~CPictureRender();
  
  void SortObjects(CPicture*);
  multimap<double, CPicture*, less< double > >* GetYSortedTree() { return &ysorted_tree; };
  
  void addPicture(CPicture* picture);
  void remPicture(int id);
  CPicture* GetObjectPicture(int object_id);
  
private:
  multimap<double, CPicture*, less< double > > ysorted_tree;
};

#endif	/* CPICTURERENDER_H */

