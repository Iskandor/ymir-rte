/********************************************************************************
** Form generated from reading UI file 'NewUnitModuleDlg.ui'
**
** Created: Sat May 10 22:55:30 2014
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWUNITMODULEDLG_H
#define UI_NEWUNITMODULEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
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

class Ui_NewUnitModuleDlg
{
public:
    QDialogButtonBox *buttonBox;
    QListView *UnitListView;
    QLineEdit *UMLineEdit;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *AddUMButton;
    QPushButton *EditUMButton;
    QPushButton *SaveBtn;
    QPushButton *DeleteUMButton;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *NameLed;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QSpinBox *StrSbx;
    QComboBox *RaceCbx;
    QSpinBox *IntSbx;
    QSpinBox *DivSbx;
    QSpinBox *ChrSbx;
    QSpinBox *EndSbx;
    QSpinBox *AglSbx;
    QWidget *tab_2;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *label_9;
    QSpinBox *SightSbx;
    QLabel *label_10;
    QSpinBox *AttRngSbx;
    QLabel *label_11;
    QSpinBox *DamSbx;
    QLabel *label_16;
    QLabel *label_21;
    QLabel *label_24;
    QGridLayout *gridLayout;
    QLabel *label_13;
    QSpinBox *EarthSbx;
    QLabel *label_14;
    QSpinBox *WaterSbx;
    QLabel *label_15;
    QSpinBox *AirSbx;
    QSpinBox *FireSbx;
    QLabel *label_12;
    QGridLayout *gridLayout_3;
    QLabel *label_19;
    QSpinBox *BluntASbx;
    QLabel *label_22;
    QSpinBox *StabASbx;
    QSpinBox *SlashASbx;
    QLabel *label_23;
    QGridLayout *gridLayout_2;
    QLabel *label_17;
    QSpinBox *BluntDSbx;
    QLabel *label_18;
    QSpinBox *StabDSbx;
    QSpinBox *SlashDSbx;
    QLabel *label_20;
    QWidget *tab_3;
    QWidget *formLayoutWidget_3;
    QFormLayout *formLayout_3;
    QLabel *label_25;
    QLineEdit *ImageLed;
    QLabel *label_26;
    QPushButton *ChooseBtn;
    QClickLabel *ImageLb;
    QHBoxLayout *horizontalLayout;
    QLabel *label_27;
    QSpinBox *SizeXSb;
    QLabel *label_28;
    QSpinBox *SizeYSb;

    void setupUi(QDialog *NewUnitModuleDlg)
    {
        if (NewUnitModuleDlg->objectName().isEmpty())
            NewUnitModuleDlg->setObjectName(QString::fromUtf8("NewUnitModuleDlg"));
        NewUnitModuleDlg->resize(782, 476);
        buttonBox = new QDialogButtonBox(NewUnitModuleDlg);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(420, 440, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        UnitListView = new QListView(NewUnitModuleDlg);
        UnitListView->setObjectName(QString::fromUtf8("UnitListView"));
        UnitListView->setGeometry(QRect(30, 60, 171, 351));
        UMLineEdit = new QLineEdit(NewUnitModuleDlg);
        UMLineEdit->setObjectName(QString::fromUtf8("UMLineEdit"));
        UMLineEdit->setGeometry(QRect(30, 30, 171, 27));
        UMLineEdit->setReadOnly(true);
        verticalLayoutWidget_2 = new QWidget(NewUnitModuleDlg);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(220, 30, 131, 128));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        AddUMButton = new QPushButton(verticalLayoutWidget_2);
        AddUMButton->setObjectName(QString::fromUtf8("AddUMButton"));

        verticalLayout_2->addWidget(AddUMButton);

        EditUMButton = new QPushButton(verticalLayoutWidget_2);
        EditUMButton->setObjectName(QString::fromUtf8("EditUMButton"));

        verticalLayout_2->addWidget(EditUMButton);

        SaveBtn = new QPushButton(verticalLayoutWidget_2);
        SaveBtn->setObjectName(QString::fromUtf8("SaveBtn"));

        verticalLayout_2->addWidget(SaveBtn);

        DeleteUMButton = new QPushButton(verticalLayoutWidget_2);
        DeleteUMButton->setObjectName(QString::fromUtf8("DeleteUMButton"));

        verticalLayout_2->addWidget(DeleteUMButton);

        tabWidget = new QTabWidget(NewUnitModuleDlg);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(370, 30, 391, 381));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        formLayoutWidget = new QWidget(tab);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(9, 9, 371, 331));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        NameLed = new QLineEdit(formLayoutWidget);
        NameLed->setObjectName(QString::fromUtf8("NameLed"));

        formLayout->setWidget(0, QFormLayout::FieldRole, NameLed);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        label_6 = new QLabel(formLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        label_7 = new QLabel(formLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

        label_8 = new QLabel(formLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_8);

        StrSbx = new QSpinBox(formLayoutWidget);
        StrSbx->setObjectName(QString::fromUtf8("StrSbx"));

        formLayout->setWidget(2, QFormLayout::FieldRole, StrSbx);

        RaceCbx = new QComboBox(formLayoutWidget);
        RaceCbx->setObjectName(QString::fromUtf8("RaceCbx"));
        RaceCbx->setEnabled(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, RaceCbx);

        IntSbx = new QSpinBox(formLayoutWidget);
        IntSbx->setObjectName(QString::fromUtf8("IntSbx"));

        formLayout->setWidget(3, QFormLayout::FieldRole, IntSbx);

        DivSbx = new QSpinBox(formLayoutWidget);
        DivSbx->setObjectName(QString::fromUtf8("DivSbx"));

        formLayout->setWidget(4, QFormLayout::FieldRole, DivSbx);

        ChrSbx = new QSpinBox(formLayoutWidget);
        ChrSbx->setObjectName(QString::fromUtf8("ChrSbx"));

        formLayout->setWidget(5, QFormLayout::FieldRole, ChrSbx);

        EndSbx = new QSpinBox(formLayoutWidget);
        EndSbx->setObjectName(QString::fromUtf8("EndSbx"));

        formLayout->setWidget(6, QFormLayout::FieldRole, EndSbx);

        AglSbx = new QSpinBox(formLayoutWidget);
        AglSbx->setObjectName(QString::fromUtf8("AglSbx"));

        formLayout->setWidget(7, QFormLayout::FieldRole, AglSbx);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        formLayoutWidget_2 = new QWidget(tab_2);
        formLayoutWidget_2->setObjectName(QString::fromUtf8("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(10, 10, 371, 331));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(formLayoutWidget_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_9);

        SightSbx = new QSpinBox(formLayoutWidget_2);
        SightSbx->setObjectName(QString::fromUtf8("SightSbx"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, SightSbx);

        label_10 = new QLabel(formLayoutWidget_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_10);

        AttRngSbx = new QSpinBox(formLayoutWidget_2);
        AttRngSbx->setObjectName(QString::fromUtf8("AttRngSbx"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, AttRngSbx);

        label_11 = new QLabel(formLayoutWidget_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_11);

        DamSbx = new QSpinBox(formLayoutWidget_2);
        DamSbx->setObjectName(QString::fromUtf8("DamSbx"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, DamSbx);

        label_16 = new QLabel(formLayoutWidget_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_16);

        label_21 = new QLabel(formLayoutWidget_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_21);

        label_24 = new QLabel(formLayoutWidget_2);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_24);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_13 = new QLabel(formLayoutWidget_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout->addWidget(label_13, 2, 0, 1, 1);

        EarthSbx = new QSpinBox(formLayoutWidget_2);
        EarthSbx->setObjectName(QString::fromUtf8("EarthSbx"));

        gridLayout->addWidget(EarthSbx, 0, 1, 1, 1);

        label_14 = new QLabel(formLayoutWidget_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout->addWidget(label_14, 0, 2, 1, 1);

        WaterSbx = new QSpinBox(formLayoutWidget_2);
        WaterSbx->setObjectName(QString::fromUtf8("WaterSbx"));

        gridLayout->addWidget(WaterSbx, 2, 1, 1, 1);

        label_15 = new QLabel(formLayoutWidget_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout->addWidget(label_15, 2, 2, 1, 1);

        AirSbx = new QSpinBox(formLayoutWidget_2);
        AirSbx->setObjectName(QString::fromUtf8("AirSbx"));

        gridLayout->addWidget(AirSbx, 0, 3, 1, 1);

        FireSbx = new QSpinBox(formLayoutWidget_2);
        FireSbx->setObjectName(QString::fromUtf8("FireSbx"));

        gridLayout->addWidget(FireSbx, 2, 3, 1, 1);

        label_12 = new QLabel(formLayoutWidget_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 0, 0, 1, 1);


        formLayout_2->setLayout(3, QFormLayout::FieldRole, gridLayout);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_19 = new QLabel(formLayoutWidget_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_3->addWidget(label_19, 2, 0, 1, 1);

        BluntASbx = new QSpinBox(formLayoutWidget_2);
        BluntASbx->setObjectName(QString::fromUtf8("BluntASbx"));

        gridLayout_3->addWidget(BluntASbx, 0, 1, 1, 1);

        label_22 = new QLabel(formLayoutWidget_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_3->addWidget(label_22, 0, 2, 1, 1);

        StabASbx = new QSpinBox(formLayoutWidget_2);
        StabASbx->setObjectName(QString::fromUtf8("StabASbx"));

        gridLayout_3->addWidget(StabASbx, 2, 1, 1, 1);

        SlashASbx = new QSpinBox(formLayoutWidget_2);
        SlashASbx->setObjectName(QString::fromUtf8("SlashASbx"));

        gridLayout_3->addWidget(SlashASbx, 0, 3, 1, 1);

        label_23 = new QLabel(formLayoutWidget_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout_3->addWidget(label_23, 0, 0, 1, 1);


        formLayout_2->setLayout(4, QFormLayout::FieldRole, gridLayout_3);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_17 = new QLabel(formLayoutWidget_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_2->addWidget(label_17, 2, 0, 1, 1);

        BluntDSbx = new QSpinBox(formLayoutWidget_2);
        BluntDSbx->setObjectName(QString::fromUtf8("BluntDSbx"));

        gridLayout_2->addWidget(BluntDSbx, 0, 1, 1, 1);

        label_18 = new QLabel(formLayoutWidget_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_2->addWidget(label_18, 0, 2, 1, 1);

        StabDSbx = new QSpinBox(formLayoutWidget_2);
        StabDSbx->setObjectName(QString::fromUtf8("StabDSbx"));

        gridLayout_2->addWidget(StabDSbx, 2, 1, 1, 1);

        SlashDSbx = new QSpinBox(formLayoutWidget_2);
        SlashDSbx->setObjectName(QString::fromUtf8("SlashDSbx"));

        gridLayout_2->addWidget(SlashDSbx, 0, 3, 1, 1);

        label_20 = new QLabel(formLayoutWidget_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_2->addWidget(label_20, 0, 0, 1, 1);


        formLayout_2->setLayout(5, QFormLayout::FieldRole, gridLayout_2);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        formLayoutWidget_3 = new QWidget(tab_3);
        formLayoutWidget_3->setObjectName(QString::fromUtf8("formLayoutWidget_3"));
        formLayoutWidget_3->setGeometry(QRect(10, 10, 371, 331));
        formLayout_3 = new QFormLayout(formLayoutWidget_3);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_3->setContentsMargins(0, 0, 0, 0);
        label_25 = new QLabel(formLayoutWidget_3);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_25);

        ImageLed = new QLineEdit(formLayoutWidget_3);
        ImageLed->setObjectName(QString::fromUtf8("ImageLed"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, ImageLed);

        label_26 = new QLabel(formLayoutWidget_3);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_26);

        ChooseBtn = new QPushButton(formLayoutWidget_3);
        ChooseBtn->setObjectName(QString::fromUtf8("ChooseBtn"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, ChooseBtn);

        ImageLb = new QClickLabel(formLayoutWidget_3);
        ImageLb->setObjectName(QString::fromUtf8("ImageLb"));

        formLayout_3->setWidget(3, QFormLayout::FieldRole, ImageLb);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_27 = new QLabel(formLayoutWidget_3);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        horizontalLayout->addWidget(label_27);

        SizeXSb = new QSpinBox(formLayoutWidget_3);
        SizeXSb->setObjectName(QString::fromUtf8("SizeXSb"));

        horizontalLayout->addWidget(SizeXSb);

        label_28 = new QLabel(formLayoutWidget_3);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        horizontalLayout->addWidget(label_28);

        SizeYSb = new QSpinBox(formLayoutWidget_3);
        SizeYSb->setObjectName(QString::fromUtf8("SizeYSb"));

        horizontalLayout->addWidget(SizeYSb);


        formLayout_3->setLayout(1, QFormLayout::FieldRole, horizontalLayout);

        tabWidget->addTab(tab_3, QString());

        retranslateUi(NewUnitModuleDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewUnitModuleDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewUnitModuleDlg, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(NewUnitModuleDlg);
    } // setupUi

    void retranslateUi(QDialog *NewUnitModuleDlg)
    {
        NewUnitModuleDlg->setWindowTitle(QApplication::translate("NewUnitModuleDlg", "NewUnitModuleDlg", 0, QApplication::UnicodeUTF8));
        AddUMButton->setText(QApplication::translate("NewUnitModuleDlg", "Add", 0, QApplication::UnicodeUTF8));
        EditUMButton->setText(QApplication::translate("NewUnitModuleDlg", "Edit", 0, QApplication::UnicodeUTF8));
        SaveBtn->setText(QApplication::translate("NewUnitModuleDlg", "Save", 0, QApplication::UnicodeUTF8));
        DeleteUMButton->setText(QApplication::translate("NewUnitModuleDlg", "Delete", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewUnitModuleDlg", "Name", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NewUnitModuleDlg", "Race", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NewUnitModuleDlg", "Strength", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("NewUnitModuleDlg", "Intelligence", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("NewUnitModuleDlg", "Divinity", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("NewUnitModuleDlg", "Charism", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("NewUnitModuleDlg", "Endurance", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("NewUnitModuleDlg", "Agility", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("NewUnitModuleDlg", "Basic", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("NewUnitModuleDlg", "Sight range", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("NewUnitModuleDlg", "Attack range", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("NewUnitModuleDlg", "Damage area", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("NewUnitModuleDlg", "Elements", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("NewUnitModuleDlg", "Attack", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("NewUnitModuleDlg", "Defense", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("NewUnitModuleDlg", "Water", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("NewUnitModuleDlg", "Air", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("NewUnitModuleDlg", "Fire", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("NewUnitModuleDlg", "Earth", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("NewUnitModuleDlg", "Stab", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("NewUnitModuleDlg", "Slash", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("NewUnitModuleDlg", "Blunt", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("NewUnitModuleDlg", "Stab", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("NewUnitModuleDlg", "Slash", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("NewUnitModuleDlg", "Blunt", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("NewUnitModuleDlg", "Advanced", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("NewUnitModuleDlg", "Filename", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("NewUnitModuleDlg", "Size", 0, QApplication::UnicodeUTF8));
        ChooseBtn->setText(QApplication::translate("NewUnitModuleDlg", "Choose file", 0, QApplication::UnicodeUTF8));
        ImageLb->setText(QApplication::translate("NewUnitModuleDlg", "Image", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("NewUnitModuleDlg", "X", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("NewUnitModuleDlg", "Y", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("NewUnitModuleDlg", "Data", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewUnitModuleDlg: public Ui_NewUnitModuleDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWUNITMODULEDLG_H
