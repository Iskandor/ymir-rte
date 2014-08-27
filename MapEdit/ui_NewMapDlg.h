/********************************************************************************
** Form generated from reading UI file 'NewMapDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWMAPDLG_H
#define UI_NEWMAPDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewMapDlg
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_5;
    QLineEdit *leName;
    QLineEdit *leMapX;
    QLineEdit *leMapY;
    QLabel *label_8;
    QComboBox *cbDefaultTile;
    QGroupBox *groupBox_2;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *leEarth;
    QLineEdit *leWater;
    QLineEdit *leAir;
    QLineEdit *leFire;

    void setupUi(QDialog *NewMapDlg)
    {
        if (NewMapDlg->objectName().isEmpty())
            NewMapDlg->setObjectName(QString::fromUtf8("NewMapDlg"));
        NewMapDlg->setWindowModality(Qt::ApplicationModal);
        NewMapDlg->resize(635, 188);
        NewMapDlg->setModal(true);
        buttonBox = new QDialogButtonBox(NewMapDlg);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(550, 10, 81, 61));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);
        groupBox = new QGroupBox(NewMapDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 271, 161));
        groupBox->setAutoFillBackground(true);
        groupBox->setFlat(false);
        formLayoutWidget = new QWidget(groupBox);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(0, 20, 261, 134));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_5);

        leName = new QLineEdit(formLayoutWidget);
        leName->setObjectName(QString::fromUtf8("leName"));

        formLayout->setWidget(1, QFormLayout::FieldRole, leName);

        leMapX = new QLineEdit(formLayoutWidget);
        leMapX->setObjectName(QString::fromUtf8("leMapX"));

        formLayout->setWidget(2, QFormLayout::FieldRole, leMapX);

        leMapY = new QLineEdit(formLayoutWidget);
        leMapY->setObjectName(QString::fromUtf8("leMapY"));

        formLayout->setWidget(3, QFormLayout::FieldRole, leMapY);

        label_8 = new QLabel(formLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_8);

        cbDefaultTile = new QComboBox(formLayoutWidget);
        cbDefaultTile->setObjectName(QString::fromUtf8("cbDefaultTile"));

        formLayout->setWidget(4, QFormLayout::FieldRole, cbDefaultTile);

        groupBox_2 = new QGroupBox(NewMapDlg);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(290, 10, 241, 161));
        groupBox_2->setAutoFillBackground(true);
        groupBox_2->setCheckable(false);
        formLayoutWidget_2 = new QWidget(groupBox_2);
        formLayoutWidget_2->setObjectName(QString::fromUtf8("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(0, 20, 241, 131));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(formLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(formLayoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_4);

        label_6 = new QLabel(formLayoutWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_6);

        label_7 = new QLabel(formLayoutWidget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_7);

        leEarth = new QLineEdit(formLayoutWidget_2);
        leEarth->setObjectName(QString::fromUtf8("leEarth"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, leEarth);

        leWater = new QLineEdit(formLayoutWidget_2);
        leWater->setObjectName(QString::fromUtf8("leWater"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, leWater);

        leAir = new QLineEdit(formLayoutWidget_2);
        leAir->setObjectName(QString::fromUtf8("leAir"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, leAir);

        leFire = new QLineEdit(formLayoutWidget_2);
        leFire->setObjectName(QString::fromUtf8("leFire"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, leFire);


        retranslateUi(NewMapDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewMapDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewMapDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewMapDlg);
    } // setupUi

    void retranslateUi(QDialog *NewMapDlg)
    {
        NewMapDlg->setWindowTitle(QApplication::translate("NewMapDlg", "NewMapDlg", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("NewMapDlg", "Main Attributes", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewMapDlg", "MapName:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NewMapDlg", "Map X:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("NewMapDlg", "Map Y:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("NewMapDlg", "Default tile", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("NewMapDlg", "Elemental centroids", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NewMapDlg", "Earth: ", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("NewMapDlg", "Water:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("NewMapDlg", "Air:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("NewMapDlg", "Fire:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewMapDlg: public Ui_NewMapDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWMAPDLG_H
