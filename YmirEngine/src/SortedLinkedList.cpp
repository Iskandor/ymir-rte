/* 
 * File:   SortedLinkedList.cpp
 * Author: Matej Pechac
 * 
 * Created on May 31, 2015, 8:30 AM
 */

#include "SortedLinkedList.h"

SortedLinkedList::SortedLinkedList() {
  begin = NULL;
  size = 0;
}

SortedLinkedList::SortedLinkedList(const SortedLinkedList& orig) {
  begin = orig.begin;
  size = orig.size;
}

SortedLinkedList::~SortedLinkedList() {
  if (begin != NULL)
  {
    ListElem  *elem = begin;
    ListElem  *del = NULL;

    while(elem->next != NULL)
    {
       del = elem;
       elem = elem->next;
       
       delete del;
    }
  }  
}

void SortedLinkedList::addPicture(CPicture* picture)
{
  if (begin == NULL)
  {
    begin = new ListElem;
    
    begin->order = picture->GetObjectEntity()->GetY() + picture->GetZIndex() - picture->GetObjectEntity()->GetRootObject()->GetYSize();
    begin->value = picture;
    begin->next = NULL;
  }
  else
  {
    ListElem  *elem = begin;
    ListElem  *insert = new ListElem;

    insert->order = picture->GetObjectEntity()->GetY() + picture->GetZIndex() - picture->GetObjectEntity()->GetRootObject()->GetYSize();
    insert->value = picture;
    insert->next = NULL;

    while(elem->next != NULL && insert->order > elem->next->order)
    {
      elem = elem->next;
    }

    if (elem->next == NULL)
    {
      if (insert->order < elem->order)
      {
        insert->next = elem;
        
        if (elem == begin)
        {
          begin = insert;
        }
      }
      else
      {
        elem->next = insert;
      }
    }
    else
    {
      if (insert->order < elem->order)
      {
        insert->next = elem;
        
        if (elem == begin)
        {
          begin = insert;
        }
      }
      else
      {
        ListElem* temp = elem->next;

        elem->next = insert;
        insert->next = temp;
      }
    }
  }
  
  size++;
}

void SortedLinkedList::remPicture(int id)
{
  if (begin != NULL)
  {
    ListElem  *elem = begin;
    ListElem  *prev = NULL;
    ListElem  *del  = NULL;

    while(elem != NULL)
    {
      if (elem->value->GetObjectEntity()->GetID() == id)
      {
        del = elem;
        break;
      }
      
      prev = elem;
      elem = elem->next;
    }
    
    if (del != NULL)
    {
      if (del == begin)
      {
        begin = del->next;
      }
      if (prev != NULL)
      {
        prev->next = del->next;
      }
      delete del;
      size--;
    }
  }  
}

CPicture* SortedLinkedList::getObjectPicture(int object_id)
{
  if (begin != NULL)
  {
    ListElem  *elem = begin;

    while(elem->next != NULL)
    {
      if (elem->value->GetObjectEntity()->GetID() == object_id)
      {
        break;
      }
      
      elem = elem->next;
    }
    
    return elem->value;
  }

  return NULL;
}

CPicture* SortedLinkedList::operator [](int index)
{
  int i = 0;
  
  if (begin != NULL)
  {
    ListElem  *elem = begin;

    while(elem->next != NULL && i != index )
    {
      elem = elem->next;
      i++;
    }
    
    return elem->value;
  }

  return NULL;  
}

