/* 
 * File:   CObjectRender.h
 * Author: Matej Pechac
 *
 * Created on May 30, 2014, 7:46 PM
 */

#ifndef COBJECTRENDER_H
#define	COBJECTRENDER_H


#include <SDL/SDL_image.h>

#include "CModule.h"
#include "CObject.h"
#include "IRender.h"
#include "CObjectPicture.h"


class CObjectRender : public IRender<CObjectPicture> {
public:
  CObjectRender(CModule<CObject> *object_module);
  CObjectRender(const CObjectRender& orig);
  virtual ~CObjectRender();

public:  
  virtual bool LoadSurfaces();
  virtual CObjectPicture* addPicture(CObjectEntity* object_entity, double z_index); 
  
private:
  CModule<CObject> *object_module;
};

#endif	/* COBJECTRENDER_H */

