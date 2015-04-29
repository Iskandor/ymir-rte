/* 
 * File:   IManager.h
 * Author: Matej Pechac
 *
 * Created on April 26, 2015, 9:12 AM
 */

#ifndef IMANAGER_H
#define	IMANAGER_H

#include <vector>

using namespace std;

template<class Entity>
class IManager {
  public:
  
  IManager() {
  };

  IManager(const IManager& orig) {
    this->entity_list = orig.entity_list;
  };

  virtual ~IManager() { };

  virtual Entity* Add() {};

  Entity* Get(int index) {
    return entity_list[index];
  };
 
  void Rem(int index) {
    int i = 0;
    typename vector<Entity*>::iterator it = entity_list.end();    

    for(it = entity_list.begin(); it != entity_list.end(); it++) {
      if (i == index) {
        entity_list.erase(it);
        break;
      }
      i++;
    }
  };

  void Rem(Entity* entity) {
    typename vector<Entity*>::iterator i = entity_list.end();

    for(i = entity_list.begin(); i != entity_list.end(); i++) {
      if (*i == entity) {
        break;
      }
    }

    if (i != entity_list.end()) {
      entity_list.erase(i);
    }
  };

  int GetListSize() {
    return entity_list.size();
  };
  
protected:
  vector<Entity*>       entity_list;
};

#endif	/* IMANAGER_H */

