/* 
 * File:   CPictureRender.cpp
 * Author: matej
 * 
 * Created on May 23, 2015, 8:09 AM
 */

#include "CPictureRender.h"

CPictureRender::CPictureRender() : SortedLinkedList() {

}

CPictureRender::CPictureRender(const CPictureRender& orig) : SortedLinkedList(orig) {
}

CPictureRender::~CPictureRender() {
}

void CPictureRender::SortObjects(CPicture* picture)
{
  remPicture(picture->GetObjectEntity()->GetID());
  addPicture(picture);
}

