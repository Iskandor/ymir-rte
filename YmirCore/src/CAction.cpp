/* 
 * File:   CAction.cpp
 * Author: Matej Pechac
 * 
 * Created on August 6, 2014, 7:35 PM
 */

#include "CAction.h"

CAction::CAction() {
    this->type = E_TYPE::IDLE;
    this->cost = 0;
    this->x = 0;
    this->y = 0;
    this->target = 0;
    this->priority = E_PRIORITY::LOWEST;
    this->index = 0;
}

CAction::CAction(E_TYPE type, int cost) {
    this->type = type;
    this->cost = cost;
    this->x = 0;
    this->y = 0;
    this->target = 0;
    this->priority = E_PRIORITY::LOWEST;
    this->index = 0;
}

CAction::CAction(E_TYPE type, int x, int y, int cost) {
    this->type = type;
    this->cost = cost;
    this->x = x;
    this->y = y;
    this->priority = E_PRIORITY::LOWEST;
    this->index = 0;
}

CAction::CAction(E_TYPE type, CUnitEntity* target, int cost) {
    this->type = type;
    this->cost = cost;
    this->target = target;
    this->priority = E_PRIORITY::LOWEST;
    this->index = 0;
}

CAction::CAction(const CAction& orig) {
    this->type = orig.type;
    this->cost = orig.cost;
    this->x = orig.x;
    this->y = orig.y;
    this->target = orig.target;
    this->priority = orig.priority;
    this->index = orig.index;
}

CAction::~CAction() {
}

