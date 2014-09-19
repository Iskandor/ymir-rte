/********************************************************************************
** Form generated from reading UI file 'NewProjModuleDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPROJMODULEDLG_H
#define UI_NEWPROJMODULEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
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

class Ui_NewProjModuleDlg
{
public:
    QDialogButtonBox *buttonBox;
    QListView *ProjListView;
    QLineEdit *leModuleName;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *bAdd;
    QPushButton *bEdit;
    QPushButton *bSave;
    QPushButton *bDelete;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *formLayoutWidget_3;
    QFormLayout *formLayout_3;
    QLabel *label_25;
    QLineEdit *leFilename;
    QLabel *label_26;
    QHBoxLayout *horizontalLayout;
    QLabel *label_27;
    QSpinBox *sbXSize;
    QLabel *label_28;
    QSpinBox *sbYSize;
    QPushButton *bChooseFile;
    QClickLabel *lImage;
    QWidget *tab_2;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *sbSpeed;
    QLabel *label_2;
    QLineEdit *leDesc;

    void setupUi(QDialog *NewProjModuleDlg)
    {
        if (NewProjModuleDlg->objectName().isEmpty())
            NewProjModuleDlg->setObjectName(QString::fromUtf8("NewProjModuleDlg"));
        NewProjModuleDlg->resize(782, 490);
        buttonBox = new QDialogButtonBox(NewProjModuleDlg);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(420, 450, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        ProjListView = new QListView(NewProjModuleDlg);
        ProjListView->setObjectName(QString::fromUtf8("ProjListView"));
        ProjListView->setGeometry(QRect(30, 60, 171, 381));
        leModuleName = new QLineEdit(NewProjModuleDlg);
        leModuleName->setObjectName(QString::fromUtf8("leModuleName"));
        leModuleName->setGeometry(QRect(30, 30, 171, 27));
        leModuleName->setReadOnly(true);
        verticalLayoutWidget_2 = new QWidget(NewProjModuleDlg);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(220, 30, 131, 128));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        bAdd = new QPushButton(verticalLayoutWidget_2);
        bAdd->setObjectName(QString::fromUtf8("bAdd"));

        verticalLayout_2->addWidget(bAdd);

        bEdit = new QPushButton(verticalLayoutWidget_2);
        bEdit->setObjectName(QString::fromUtf8("bEdit"));

        verticalLayout_2->addWidget(bEdit);

        bSave = new QPushButton(verticalLayoutWidget_2);
        bSave->setObjectName(QString::fromUtf8("bSave"));

        verticalLayout_2->addWidget(bSave);

        bDelete = new QPushButton(verticalLayoutWidget_2);
        bDelete->setObjectName(QString::fromUtf8("bDelete"));

        verticalLayout_2->addWidget(bDelete);

        tabWidget = new QTabWidget(NewProjModuleDlg);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(380, 40, 391, 401));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        formLayoutWidget_3 = new QWidget(tab);
        formLayoutWidget_3->setObjectName(QString::fromUtf8("formLayoutWidget_3"));
        formLayoutWidget_3->setGeometry(QRect(10, 10, 371, 351));
        formLayout_3 = new QFormLayout(formLayoutWidget_3);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_3->setContentsMargins(0, 0, 0, 0);
        label_25 = new QLabel(formLayoutWidget_3);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_25);

        leFilename = new QLineEdit(formLayoutWidget_3);
        leFilename->setObjectName(QString::fromUtf8("leFilename"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, leFilename);

        label_26 = new QLabel(formLayoutWidget_3);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_26);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_27 = new QLabel(formLayoutWidget_3);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        horizontalLayout->addWidget(label_27);

        sbXSize = new QSpinBox(formLayoutWidget_3);
        sbXSize->setObjectName(QString::fromUtf8("sbXSize"));

        horizontalLayout->addWidget(sbXSize);

        label_28 = new QLabel(formLayoutWidget_3);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        horizontalLayout->addWidget(label_28);

        sbYSize = new QSpinBox(formLayoutWidget_3);
        sbYSize->setObjectName(QString::fromUtf8("sbYSize"));

        horizontalLayout->addWidget(sbYSize);


        formLayout_3->setLayout(1, QFormLayout::FieldRole, horizontalLayout);

        bChooseFile = new QPushButton(formLayoutWidget_3);
        bChooseFile->setObjectName(QString::fromUtf8("bChooseFile"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, bChooseFile);

        lImage = new QClickLabel(formLayoutWidget_3);
        lImage->setObjectName(QString::fromUtf8("lImage"));

        formLayout_3->setWidget(3, QFormLayout::FieldRole, lImage);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        formLayoutWidget = new QWidget(tab_2);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(9, 9, 371, 351));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        sbSpeed = new QSpinBox(formLayoutWidget);
        sbSpeed->setObjectName(QString::fromUtf8("sbSpeed"));

        formLayout->setWidget(1, QFormLayout::FieldRole, sbSpeed);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        leDesc = new QLineEdit(formLayoutWidget);
        leDesc->setObjectName(QString::fromUtf8("leDesc"));

        formLayout->setWidget(0, QFormLayout::FieldRole, leDesc);

        tabWidget->addTab(tab_2, QString());

        retranslateUi(NewProjModuleDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewProjModuleDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewProjModuleDlg, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(NewProjModuleDlg);
    } // setupUi

    void retranslateUi(QDialog *NewProjModuleDlg)
    {
        NewProjModuleDlg->setWindowTitle(QApplication::translate("NewProjModuleDlg", "NewProjModuleDlg", 0, QApplication::UnicodeUTF8));
        bAdd->setText(QApplication::translate("NewProjModuleDlg", "Add", 0, QApplication::UnicodeUTF8));
        bEdit->setText(QApplication::translate("NewProjModuleDlg", "Edit", 0, QApplication::UnicodeUTF8));
        bSave->setText(QApplication::translate("NewProjModuleDlg", "Save", 0, QApplication::UnicodeUTF8));
        bDelete->setText(QApplication::translate("NewProjModuleDlg", "Delete", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("NewProjModuleDlg", "Filename", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("NewProjModuleDlg", "Size", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("NewProjModuleDlg", "X", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("NewProjModuleDlg", "Y", 0, QApplication::UnicodeUTF8));
        bChooseFile->setText(QApplication::translate("NewProjModuleDlg", "Choose file", 0, QApplication::UnicodeUTF8));
        lImage->setText(QApplication::translate("NewProjModuleDlg", "Image", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("NewProjModuleDlg", "Data", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewProjModuleDlg", "Speed", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NewProjModuleDlg", "Name", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("NewProjModuleDlg", "Basic", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewProjModuleDlg: public Ui_NewProjModuleDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPROJMODULEDLG_H
