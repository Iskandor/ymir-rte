/* 
 * File:   GlobalDefine.h
 * Author: Matej Pechac
 *
 * Created on August 22, 2012, 7:48 AM
 */

#ifndef GLOBALDEFINE_H
#define	GLOBALDEFINE_H

#define UNIT_LIST  "units"
#define TILE_LIST  "tiles"
#define OBJECT_LIST "objects"
#define PROJECTILES_LIST "projectiles"
#define MODIFIER_LIST "modifiers"
#define IMAGE_PATH_UNITS "data/image/units/"
#define IMAGE_PATH_OBJECTS "data/image/objects/"
#define IMAGE_PATH_PROJECTILES "data/image/objects/"
#define IMAGE_PATH_TILES "data/image/terrain/"
#define IMAGE_PATH_INSIGNIA "data/image/insignia/"

#ifdef	__cplusplus
extern "C" {
#endif

const int MAP_ELEM = 16;
const int TILE_W = 64;
const int TILE_H = 64;
const int TILE_PER_SEGMENT = 16;
const int ELEM_PER_TILE = 4;
const double BOTTOM  = -99;
const double MIDDLE  = 0; 
const double TOP     = 99;
const double SQRT2   = 1.4142;
const int MAX_PLAYER = 2;
const int RESOLUTION_W = 1280;
const int RESOLUTION_H = 720;
const int CAMERA_W = 20;
const int CAMERA_H = 12; //8
const int FONT_HEIGHT = 12;


#ifdef	__cplusplus
}
#endif

#endif	/* GLOBALDEFINE_H */

