/* 
 * File:   CUnit.h
 * Author: Matej Pechac
 *
 * Created on August 20, 2012, 5:42 PM
 */

#ifndef CUNIT_H
#define	CUNIT_H

#include <vector>
#include <map>
#include <string>

#define N_ATTACK  3
#define N_PROP    6
#define N_ELEM    4

#define STR_IND 0
#define END_IND 1
#define AGL_IND 2
#define INT_IND 3
#define DIV_IND 4
#define CHA_IND 5

#define EAR_IND 0
#define WAT_IND 1
#define AIR_IND 2
#define FIR_IND 3

#define BLUNT_IND 0
#define SLASH_IND 1
#define STAB_IND  2

#include "CObject.h"

using namespace std;

class CUnit : public CObject {
public:
    CUnit();
    CUnit(int id);
    CUnit(map<string, string> data);
    CUnit(const CUnit& orig);
    virtual ~CUnit();
    
    map<string, string> exportMap();
    
    void setProp(vector<int> unit_props);
    vector<int> getProp();
    void setClass(string _class);
    string getClass();
    void setRace(string _race);
    string getRace();
    void setElem(vector<int> _elem);
    vector<int> getElem();
    void setAVP(vector<int> _avp);
    vector<int> getAVP();
    int GetAttackType(double probability);
    void setRVP(vector<int> _rvp);
    vector<int> getRVP();
    void setSight(int _sr);
    int getSight();
    void setAttackRange(int _ar);
    int getAttackRange();
    void setDamageArea(int _aa);
    int getDamageArea();
    void setInsigniaPos(pair<int, int> pos);
    pair<int, int> getInsigniaPos();
    void  setWeapon(int value) { weapon = value; };
    int   getWeapon() { return weapon; };
    void  setArmor(int value) {armor = value; };
    int   getArmor() { return armor; };
    void  setProjectilID(int value) { projectil_id = value; };
    int   getProjectilID() { return projectil_id; };
    void  setModifierID(int value) { modifier_id = value; };
    int   getModifierID() { return modifier_id; };    
    
private:
  int sr;
  int ar;
  int aa;
  int weapon;
  int armor;
  int projectil_id;
  int modifier_id;
  vector<int>     elements;
  vector<int>     avp;
  vector<int>     rvp;
  pair<int, int>  insignia_pos;
  
  string unit_class;
  string unit_race;
  
  vector<int> unit_props;
};

#endif	/* CUNIT_H */

