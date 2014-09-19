/********************************************************************************
** Form generated from reading UI file 'EntryForm.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENTRYFORM_H
#define UI_ENTRYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QScrollBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EntryForm
{
public:
    QAction *actionNew_map;
    QAction *actionOpen_map;
    QAction *actionSave_as;
    QAction *actionSave;
    QAction *actionProperties;
    QAction *actionQuit;
    QAction *actionUnit_Module;
    QAction *actionTile_Module;
    QAction *actionObject_Modules;
    QAction *actionProjectile_Modules;
    QWidget *centralwidget;
    QScrollBar *horizontalScrollBar;
    QScrollBar *verticalScrollBar;
    QWidget *drawingWidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QMenu *menuUnits;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *EntryForm)
    {
        if (EntryForm->objectName().isEmpty())
            EntryForm->setObjectName(QString::fromUtf8("EntryForm"));
        EntryForm->resize(1024, 768);
        actionNew_map = new QAction(EntryForm);
        actionNew_map->setObjectName(QString::fromUtf8("actionNew_map"));
        actionNew_map->setIconVisibleInMenu(false);
        actionOpen_map = new QAction(EntryForm);
        actionOpen_map->setObjectName(QString::fromUtf8("actionOpen_map"));
        actionSave_as = new QAction(EntryForm);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        actionSave = new QAction(EntryForm);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionProperties = new QAction(EntryForm);
        actionProperties->setObjectName(QString::fromUtf8("actionProperties"));
        actionQuit = new QAction(EntryForm);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionUnit_Module = new QAction(EntryForm);
        actionUnit_Module->setObjectName(QString::fromUtf8("actionUnit_Module"));
        actionTile_Module = new QAction(EntryForm);
        actionTile_Module->setObjectName(QString::fromUtf8("actionTile_Module"));
        actionObject_Modules = new QAction(EntryForm);
        actionObject_Modules->setObjectName(QString::fromUtf8("actionObject_Modules"));
        actionProjectile_Modules = new QAction(EntryForm);
        actionProjectile_Modules->setObjectName(QString::fromUtf8("actionProjectile_Modules"));
        centralwidget = new QWidget(EntryForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalScrollBar = new QScrollBar(centralwidget);
        horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
        horizontalScrollBar->setGeometry(QRect(0, 710, 1011, 16));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(horizontalScrollBar->sizePolicy().hasHeightForWidth());
        horizontalScrollBar->setSizePolicy(sizePolicy);
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        verticalScrollBar = new QScrollBar(centralwidget);
        verticalScrollBar->setObjectName(QString::fromUtf8("verticalScrollBar"));
        verticalScrollBar->setGeometry(QRect(1010, 0, 20, 711));
        verticalScrollBar->setOrientation(Qt::Vertical);
        drawingWidget = new QWidget(centralwidget);
        drawingWidget->setObjectName(QString::fromUtf8("drawingWidget"));
        drawingWidget->setGeometry(QRect(0, 0, 1011, 711));
        EntryForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(EntryForm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 25));
        menubar->setContextMenuPolicy(Qt::DefaultContextMenu);
        menubar->setAutoFillBackground(false);
        menubar->setDefaultUp(false);
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuUnits = new QMenu(menubar);
        menuUnits->setObjectName(QString::fromUtf8("menuUnits"));
        EntryForm->setMenuBar(menubar);
        statusbar = new QStatusBar(EntryForm);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        EntryForm->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuUnits->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew_map);
        menuFile->addAction(actionOpen_map);
        menuFile->addAction(actionSave_as);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionProperties);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuUnits->addAction(actionUnit_Module);
        menuUnits->addAction(actionTile_Module);
        menuUnits->addAction(actionObject_Modules);
        menuUnits->addAction(actionProjectile_Modules);

        retranslateUi(EntryForm);

        QMetaObject::connectSlotsByName(EntryForm);
    } // setupUi

    void retranslateUi(QMainWindow *EntryForm)
    {
        EntryForm->setWindowTitle(QApplication::translate("EntryForm", "EntryForm", 0, QApplication::UnicodeUTF8));
        actionNew_map->setText(QApplication::translate("EntryForm", "New map", 0, QApplication::UnicodeUTF8));
        actionOpen_map->setText(QApplication::translate("EntryForm", "Open map", 0, QApplication::UnicodeUTF8));
        actionSave_as->setText(QApplication::translate("EntryForm", "Save as..", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("EntryForm", "Save", 0, QApplication::UnicodeUTF8));
        actionProperties->setText(QApplication::translate("EntryForm", "Properties", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("EntryForm", "Quit", 0, QApplication::UnicodeUTF8));
        actionUnit_Module->setText(QApplication::translate("EntryForm", "Unit Modules", 0, QApplication::UnicodeUTF8));
        actionTile_Module->setText(QApplication::translate("EntryForm", "Tile Modules", 0, QApplication::UnicodeUTF8));
        actionObject_Modules->setText(QApplication::translate("EntryForm", "Object Modules", 0, QApplication::UnicodeUTF8));
        actionProjectile_Modules->setText(QApplication::translate("EntryForm", "Projectile Modules", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("EntryForm", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("EntryForm", "Edit", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("EntryForm", "Help", 0, QApplication::UnicodeUTF8));
        menuUnits->setTitle(QApplication::translate("EntryForm", "Modules", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EntryForm: public Ui_EntryForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENTRYFORM_H
