/* 
 * File:   SortedLinkedList.h
 * Author: Matej Pechac
 *
 * Created on May 31, 2015, 8:30 AM
 */

#ifndef SORTEDLINKEDLIST_H
#define	SORTEDLINKEDLIST_H

#include "CPicture.h"

class SortedLinkedList {
  struct ListElem
  {
    double    order;
    CPicture* value;
    ListElem* next;
  };
  
public:
  SortedLinkedList();
  SortedLinkedList(const SortedLinkedList& orig);
  virtual ~SortedLinkedList();
  
  void addPicture(CPicture* picture);
  void remPicture(int id);
  CPicture* getObjectPicture(int object_id);
  CPicture* operator [](int index);
  
  int Size() { return size; }
  
protected:
  ListElem  *begin;
  int       size;
};

#endif	/* SORTEDLINKEDLIST_H */

