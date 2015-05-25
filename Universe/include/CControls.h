/* 
 * File:   CControls.h
 * Author: matej
 *
 * Created on May 11, 2015, 10:21 PM
 */

#ifndef CCONTROLS_H
#define	CCONTROLS_H

#include "CMap.h"
#include "CMapRender.h"
#include "CObjectBuilder.h"

class CControls {
public:
  CControls(CMap* map, CMapRender* map_render, CObjectBuilder* object_builder);
  CControls(const CControls& orig);
  virtual ~CControls();
  
  virtual void OnLoop();
  
protected:
  CMap*           map;
  CMapRender*     map_render;
  CObjectBuilder* object_builder;  

};

#endif	/* CCONTROLS_H */

