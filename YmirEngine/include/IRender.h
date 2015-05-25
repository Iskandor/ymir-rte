/* 
 * File:   CRender.h
 * Author: Matej Pechac
 *
 * Created on May 21, 2015, 9:05 PM
 */

#ifndef CRENDER_H
#define	CRENDER_H

#include <memory>
#include <vector>

#include "CSprite.h"
#include "CObjectEntity.h"


using namespace std;

template<class P>
class IRender {
public:
  IRender()
  {
    
  }
  
  IRender(const IRender& orig)
  {
    sprite_map = orig.sprite_map;
    //picture_buffer = orig.picture_buffer;
  }
  
  virtual ~IRender() {}
  
  virtual bool LoadSurfaces()  {}
  
  virtual P* addPicture(CObjectEntity* object_entity, double z_index)  {}
  
  void remPicture(int id)
  {
    typename vector<unique_ptr<P> >::iterator it;
    
    for(it = picture_buffer.begin(); it != picture_buffer.end(); it++)
    {
      P* picture_ptr = NULL;

      if (((P)(**it)).GetObjectEntity()->GetID() == id) {
        picture_ptr = (*it).release();
        picture_buffer.erase(it);
        delete picture_ptr;

        break;
      }
    }
  }
  
protected:
  map<int, CSprite*>             sprite_map;
  vector< unique_ptr<P> >   picture_buffer;
};

#endif	/* CRENDER_H */

