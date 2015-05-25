/* 
 * File:   CPictureRender.cpp
 * Author: matej
 * 
 * Created on May 23, 2015, 8:09 AM
 */

#include "CPictureRender.h"

CPictureRender::CPictureRender() {
  ysorted_tree.clear();
}

CPictureRender::CPictureRender(const CPictureRender& orig) {
  this->ysorted_tree = orig.ysorted_tree;
}

CPictureRender::~CPictureRender() {
}

void CPictureRender::SortObjects(CPicture* picture) {
  multimap<double, CPicture*, less< double > >::iterator it;
  
  for(it = ysorted_tree.begin(); it != ysorted_tree.end(); it++) {
    if (it->second->GetObjectEntity()->GetID() == picture->GetObjectEntity()->GetID()) {
      break;
    }
  }
  
  if (it != ysorted_tree.end()) {
    ysorted_tree.erase(it);
    ysorted_tree.insert(pair<double, CPicture* >(picture->GetRenderY() + picture->GetZIndex(), picture));
  }
}

void CPictureRender::addPicture(CPicture* picture)
{
  double y_position = picture->GetObjectEntity()->GetY() + picture->GetZIndex() - picture->GetObjectEntity()->GetRootObject()->GetYSize();
  
  ysorted_tree.insert(make_pair(y_position, picture));
}

void CPictureRender::remPicture(int id)
{
  multimap<double, CPicture*, less< double > >::iterator it; 
  
  for(it = ysorted_tree.begin(); it != ysorted_tree.end(); it++) {
    if (it->second->GetObjectEntity()->GetID() == id) {
      break;
    }    
  }
  
  if (it != ysorted_tree.end())
  {
    ysorted_tree.erase(it);
  }
}

CPicture* CPictureRender::GetObjectPicture(int object_id)
{
  multimap<double, CPicture*, less< double > >::iterator it; 
  
  for(it = ysorted_tree.begin(); it != ysorted_tree.end(); it++) {
    if (it->second->GetObjectEntity()->GetID() == object_id) {
      return it->second;
    }    
  }
  
  return NULL;
}

