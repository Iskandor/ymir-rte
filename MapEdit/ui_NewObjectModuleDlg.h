/********************************************************************************
** Form generated from reading UI file 'NewObjectModuleDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWOBJECTMODULEDLG_H
#define UI_NEWOBJECTMODULEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "QClickLabel.h"

QT_BEGIN_NAMESPACE

class Ui_NewObjectModuleDlg
{
public:
    QDialogButtonBox *buttonBox;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *label_5;
    QLineEdit *leDesc;
    QLabel *label_6;
    QComboBox *cbClass;
    QWidget *tab;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *leFilename;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpinBox *sbXSize;
    QLabel *label_4;
    QSpinBox *sbYSize;
    QPushButton *bChooseFile;
    QClickLabel *lImage;
    QLineEdit *leModuleName;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *bAdd;
    QPushButton *bEdit;
    QPushButton *bSave;
    QPushButton *bDelete;
    QListView *ObjectList;

    void setupUi(QDialog *NewObjectModuleDlg)
    {
        if (NewObjectModuleDlg->objectName().isEmpty())
            NewObjectModuleDlg->setObjectName(QString::fromUtf8("NewObjectModuleDlg"));
        NewObjectModuleDlg->resize(759, 490);
        buttonBox = new QDialogButtonBox(NewObjectModuleDlg);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(410, 450, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tabWidget = new QTabWidget(NewObjectModuleDlg);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(352, 9, 401, 431));
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        formLayoutWidget_2 = new QWidget(tab_2);
        formLayoutWidget_2->setObjectName(QString::fromUtf8("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(9, 9, 381, 381));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(formLayoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_5);

        leDesc = new QLineEdit(formLayoutWidget_2);
        leDesc->setObjectName(QString::fromUtf8("leDesc"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, leDesc);

        label_6 = new QLabel(formLayoutWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_6);

        cbClass = new QComboBox(formLayoutWidget_2);
        cbClass->setObjectName(QString::fromUtf8("cbClass"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, cbClass);

        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        formLayoutWidget = new QWidget(tab);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(9, 9, 381, 381));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        leFilename = new QLineEdit(formLayoutWidget);
        leFilename->setObjectName(QString::fromUtf8("leFilename"));

        formLayout->setWidget(0, QFormLayout::FieldRole, leFilename);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        sbXSize = new QSpinBox(formLayoutWidget);
        sbXSize->setObjectName(QString::fromUtf8("sbXSize"));

        horizontalLayout->addWidget(sbXSize);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        sbYSize = new QSpinBox(formLayoutWidget);
        sbYSize->setObjectName(QString::fromUtf8("sbYSize"));

        horizontalLayout->addWidget(sbYSize);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout);

        bChooseFile = new QPushButton(formLayoutWidget);
        bChooseFile->setObjectName(QString::fromUtf8("bChooseFile"));

        formLayout->setWidget(2, QFormLayout::FieldRole, bChooseFile);

        lImage = new QClickLabel(formLayoutWidget);
        lImage->setObjectName(QString::fromUtf8("lImage"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lImage);

        tabWidget->addTab(tab, QString());
        leModuleName = new QLineEdit(NewObjectModuleDlg);
        leModuleName->setObjectName(QString::fromUtf8("leModuleName"));
        leModuleName->setGeometry(QRect(10, 10, 161, 27));
        verticalLayoutWidget = new QWidget(NewObjectModuleDlg);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(180, 40, 160, 151));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        bAdd = new QPushButton(verticalLayoutWidget);
        bAdd->setObjectName(QString::fromUtf8("bAdd"));

        verticalLayout->addWidget(bAdd);

        bEdit = new QPushButton(verticalLayoutWidget);
        bEdit->setObjectName(QString::fromUtf8("bEdit"));

        verticalLayout->addWidget(bEdit);

        bSave = new QPushButton(verticalLayoutWidget);
        bSave->setObjectName(QString::fromUtf8("bSave"));

        verticalLayout->addWidget(bSave);

        bDelete = new QPushButton(verticalLayoutWidget);
        bDelete->setObjectName(QString::fromUtf8("bDelete"));

        verticalLayout->addWidget(bDelete);

        ObjectList = new QListView(NewObjectModuleDlg);
        ObjectList->setObjectName(QString::fromUtf8("ObjectList"));
        ObjectList->setGeometry(QRect(10, 40, 161, 401));

        retranslateUi(NewObjectModuleDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewObjectModuleDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewObjectModuleDlg, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(NewObjectModuleDlg);
    } // setupUi

    void retranslateUi(QDialog *NewObjectModuleDlg)
    {
        NewObjectModuleDlg->setWindowTitle(QApplication::translate("NewObjectModuleDlg", "NewObjectModuleDlg", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("NewObjectModuleDlg", "Descriptor", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("NewObjectModuleDlg", "Class", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("NewObjectModuleDlg", "Basic", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewObjectModuleDlg", "Filename", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NewObjectModuleDlg", "Size:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NewObjectModuleDlg", "X", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("NewObjectModuleDlg", "Y", 0, QApplication::UnicodeUTF8));
        bChooseFile->setText(QApplication::translate("NewObjectModuleDlg", "Choose image file", 0, QApplication::UnicodeUTF8));
        lImage->setText(QApplication::translate("NewObjectModuleDlg", "Image", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("NewObjectModuleDlg", "Data", 0, QApplication::UnicodeUTF8));
        bAdd->setText(QApplication::translate("NewObjectModuleDlg", "Add", 0, QApplication::UnicodeUTF8));
        bEdit->setText(QApplication::translate("NewObjectModuleDlg", "Edit", 0, QApplication::UnicodeUTF8));
        bSave->setText(QApplication::translate("NewObjectModuleDlg", "Save", 0, QApplication::UnicodeUTF8));
        bDelete->setText(QApplication::translate("NewObjectModuleDlg", "Delete", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewObjectModuleDlg: public Ui_NewObjectModuleDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWOBJECTMODULEDLG_H
