/* 
 * File:   EntryForm.h
 * Author: matej
 *
 * Created on October 8, 2012, 6:57 PM
 */

#ifndef _ENTRYFORM_H
#define	_ENTRYFORM_H

#include "CMap.h"
#include "ui_EntryForm.h"
#include "GlobalDefine.h"
#include "CMapRender.h"
#include "CModule.h"
#include "CTile.h"
#include "CUnit.h"

class EntryForm : public QMainWindow {
    Q_OBJECT
public:
    EntryForm();
    virtual ~EntryForm();
private:
    Ui::EntryForm widget;

    CMap            *map;
    CMapRender      *map_render;
    CModule<CTile>  tile_module;
    CModule<CUnit>  unit_module;

public slots:
    void    newMap();
    void    openMap();
    void    saveMap();
    void    saveMapAs();
    void    exit();
    void    openUnitModule();
    void    openTileModule();
    void    openObjectModule();

    void    moveCameraX(int);
    void    moveCameraY(int);

private:
    void    repaint();
    void    paintEvent(QPaintEvent*);
};

#endif	/* _ENTRYFORM_H */
