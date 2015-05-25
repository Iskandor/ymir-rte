/* 
 * File:   CControls.cpp
 * Author: Matej Pechac
 * 
 * Created on May 11, 2015, 10:21 PM
 */

#include "CControls.h"

CControls::CControls(CMap* map, CMapRender* map_render, CObjectBuilder* object_builder) {
  this->map = map;
  this->map_render = map_render;
  this->object_builder = object_builder;
}

CControls::CControls(const CControls& orig) {
  this->map = orig.map;
  this->map_render = orig.map_render;
  this->object_builder = orig.object_builder;
}

CControls::~CControls() {
}

void CControls::OnLoop()
{
  
}

