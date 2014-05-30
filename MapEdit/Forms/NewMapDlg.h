/* 
 * File:   NewMapDlg.h
 * Author: matej
 *
 * Created on October 8, 2012, 7:05 PM
 */

#ifndef _NEWMAPDLG_H
#define	_NEWMAPDLG_H

#include <string>

#include "ui_NewMapDlg.h"
#include "CModule.h"
#include "CTile.h"

using namespace std;

struct  sMapDlg {
    std::string name;
    int x;
    int y;
    int centroids[4];
    int default_tile;
};

class NewMapDlg : public QDialog {
    Q_OBJECT
public:
    NewMapDlg(CModule<CTile> *tile_module);
    virtual ~NewMapDlg();

    sMapDlg     map_dlg;
private:
    Ui::NewMapDlg widget;
    
    CModule<CTile>* tile_module;
    
    void RefreshComboBox();
    
public slots:
    void accept();
};

#endif	/* _NEWMAPDLG_H */
