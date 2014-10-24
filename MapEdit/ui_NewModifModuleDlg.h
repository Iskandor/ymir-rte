/********************************************************************************
** Form generated from reading UI file 'NewModifModuleDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWMODIFMODULEDLG_H
#define UI_NEWMODIFMODULEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewModifModuleDlg
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
    QLabel *label;
    QSpinBox *sbDuration;
    QWidget *tab;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_7;
    QSpinBox *sbDeltaHP;
    QSpinBox *spinBox_4;
    QSpinBox *sbDeltaHPper;
    QSpinBox *sbDeltaStper;
    QSpinBox *sbDeltaSt;
    QSpinBox *spinBox_7;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox_8;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QListView *ObjectList;
    QLineEdit *leModuleName;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *bAdd;
    QPushButton *bEdit;
    QPushButton *bSave;
    QPushButton *bDelete;

    void setupUi(QDialog *NewModifModuleDlg)
    {
        if (NewModifModuleDlg->objectName().isEmpty())
            NewModifModuleDlg->setObjectName(QString::fromUtf8("NewModifModuleDlg"));
        NewModifModuleDlg->resize(761, 487);
        buttonBox = new QDialogButtonBox(NewModifModuleDlg);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(410, 450, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tabWidget = new QTabWidget(NewModifModuleDlg);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(352, 9, 401, 431));
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        formLayoutWidget_2 = new QWidget(tab_2);
        formLayoutWidget_2->setObjectName(QString::fromUtf8("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(9, 9, 381, 381));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
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

        label = new QLabel(formLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label);

        sbDuration = new QSpinBox(formLayoutWidget_2);
        sbDuration->setObjectName(QString::fromUtf8("sbDuration"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, sbDuration);

        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayoutWidget = new QWidget(tab);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(9, 9, 381, 381));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 3, 0, 1, 1);

        sbDeltaHP = new QSpinBox(gridLayoutWidget);
        sbDeltaHP->setObjectName(QString::fromUtf8("sbDeltaHP"));

        gridLayout->addWidget(sbDeltaHP, 0, 1, 1, 1);

        spinBox_4 = new QSpinBox(gridLayoutWidget);
        spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));

        gridLayout->addWidget(spinBox_4, 3, 1, 1, 1);

        sbDeltaHPper = new QSpinBox(gridLayoutWidget);
        sbDeltaHPper->setObjectName(QString::fromUtf8("sbDeltaHPper"));
        sbDeltaHPper->setMaximum(100);

        gridLayout->addWidget(sbDeltaHPper, 0, 2, 1, 1);

        sbDeltaStper = new QSpinBox(gridLayoutWidget);
        sbDeltaStper->setObjectName(QString::fromUtf8("sbDeltaStper"));
        sbDeltaStper->setMaximum(100);

        gridLayout->addWidget(sbDeltaStper, 1, 2, 1, 1);

        sbDeltaSt = new QSpinBox(gridLayoutWidget);
        sbDeltaSt->setObjectName(QString::fromUtf8("sbDeltaSt"));

        gridLayout->addWidget(sbDeltaSt, 1, 1, 1, 1);

        spinBox_7 = new QSpinBox(gridLayoutWidget);
        spinBox_7->setObjectName(QString::fromUtf8("spinBox_7"));
        spinBox_7->setMaximum(100);

        gridLayout->addWidget(spinBox_7, 2, 2, 1, 1);

        spinBox_3 = new QSpinBox(gridLayoutWidget);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));

        gridLayout->addWidget(spinBox_3, 2, 1, 1, 1);

        spinBox_8 = new QSpinBox(gridLayoutWidget);
        spinBox_8->setObjectName(QString::fromUtf8("spinBox_8"));
        spinBox_8->setMaximum(100);

        gridLayout->addWidget(spinBox_8, 3, 2, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 0, 3, 1, 1);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 1, 3, 1, 1);

        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 2, 3, 1, 1);

        label_11 = new QLabel(gridLayoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 3, 3, 1, 1);

        tabWidget->addTab(tab, QString());
        ObjectList = new QListView(NewModifModuleDlg);
        ObjectList->setObjectName(QString::fromUtf8("ObjectList"));
        ObjectList->setGeometry(QRect(10, 40, 161, 401));
        leModuleName = new QLineEdit(NewModifModuleDlg);
        leModuleName->setObjectName(QString::fromUtf8("leModuleName"));
        leModuleName->setGeometry(QRect(10, 10, 161, 27));
        verticalLayoutWidget = new QWidget(NewModifModuleDlg);
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


        retranslateUi(NewModifModuleDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewModifModuleDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewModifModuleDlg, SLOT(reject()));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(NewModifModuleDlg);
    } // setupUi

    void retranslateUi(QDialog *NewModifModuleDlg)
    {
        NewModifModuleDlg->setWindowTitle(QApplication::translate("NewModifModuleDlg", "NewModifModuleDlg", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("NewModifModuleDlg", "Descriptor", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("NewModifModuleDlg", "Class", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewModifModuleDlg", "Duration", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("NewModifModuleDlg", "Basic", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NewModifModuleDlg", "HP", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NewModifModuleDlg", "Stamina", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("NewModifModuleDlg", "Sight", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("NewModifModuleDlg", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("NewModifModuleDlg", "%", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("NewModifModuleDlg", "%", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("NewModifModuleDlg", "%", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("NewModifModuleDlg", "%", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("NewModifModuleDlg", "Values", 0, QApplication::UnicodeUTF8));
        bAdd->setText(QApplication::translate("NewModifModuleDlg", "Add", 0, QApplication::UnicodeUTF8));
        bEdit->setText(QApplication::translate("NewModifModuleDlg", "Edit", 0, QApplication::UnicodeUTF8));
        bSave->setText(QApplication::translate("NewModifModuleDlg", "Save", 0, QApplication::UnicodeUTF8));
        bDelete->setText(QApplication::translate("NewModifModuleDlg", "Delete", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewModifModuleDlg: public Ui_NewModifModuleDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWMODIFMODULEDLG_H
