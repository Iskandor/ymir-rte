/********************************************************************************
** Form generated from reading UI file 'NewTileModuleDlg.ui'
**
** Created: Sat May 10 22:55:30 2014
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWTILEMODULEDLG_H
#define UI_NEWTILEMODULEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewTileModuleDlg
{
public:
    QDialogButtonBox *buttonBox;
    QListView *TileListView;
    QLineEdit *TMLe;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *AddTMButton;
    QPushButton *EditTMButton;
    QPushButton *SaveTMButton;
    QPushButton *DeleteTMButton;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QPushButton *ChooseTMButton;
    QLabel *ImageLb;
    QLineEdit *NameLe;
    QLineEdit *FileLe;

    void setupUi(QDialog *NewTileModuleDlg)
    {
        if (NewTileModuleDlg->objectName().isEmpty())
            NewTileModuleDlg->setObjectName(QString::fromUtf8("NewTileModuleDlg"));
        NewTileModuleDlg->resize(628, 457);
        buttonBox = new QDialogButtonBox(NewTileModuleDlg);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(330, 420, 291, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        TileListView = new QListView(NewTileModuleDlg);
        TileListView->setObjectName(QString::fromUtf8("TileListView"));
        TileListView->setGeometry(QRect(10, 70, 171, 341));
        TMLe = new QLineEdit(NewTileModuleDlg);
        TMLe->setObjectName(QString::fromUtf8("TMLe"));
        TMLe->setGeometry(QRect(10, 40, 171, 27));
        TMLe->setReadOnly(true);
        verticalLayoutWidget = new QWidget(NewTileModuleDlg);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(190, 40, 131, 171));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        AddTMButton = new QPushButton(verticalLayoutWidget);
        AddTMButton->setObjectName(QString::fromUtf8("AddTMButton"));

        verticalLayout->addWidget(AddTMButton);

        EditTMButton = new QPushButton(verticalLayoutWidget);
        EditTMButton->setObjectName(QString::fromUtf8("EditTMButton"));

        verticalLayout->addWidget(EditTMButton);

        SaveTMButton = new QPushButton(verticalLayoutWidget);
        SaveTMButton->setObjectName(QString::fromUtf8("SaveTMButton"));

        verticalLayout->addWidget(SaveTMButton);

        DeleteTMButton = new QPushButton(verticalLayoutWidget);
        DeleteTMButton->setObjectName(QString::fromUtf8("DeleteTMButton"));

        verticalLayout->addWidget(DeleteTMButton);

        formLayoutWidget = new QWidget(NewTileModuleDlg);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(330, 40, 291, 371));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        ChooseTMButton = new QPushButton(formLayoutWidget);
        ChooseTMButton->setObjectName(QString::fromUtf8("ChooseTMButton"));

        formLayout->setWidget(2, QFormLayout::FieldRole, ChooseTMButton);

        ImageLb = new QLabel(formLayoutWidget);
        ImageLb->setObjectName(QString::fromUtf8("ImageLb"));

        formLayout->setWidget(3, QFormLayout::FieldRole, ImageLb);

        NameLe = new QLineEdit(formLayoutWidget);
        NameLe->setObjectName(QString::fromUtf8("NameLe"));

        formLayout->setWidget(0, QFormLayout::FieldRole, NameLe);

        FileLe = new QLineEdit(formLayoutWidget);
        FileLe->setObjectName(QString::fromUtf8("FileLe"));

        formLayout->setWidget(1, QFormLayout::FieldRole, FileLe);


        retranslateUi(NewTileModuleDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewTileModuleDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewTileModuleDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewTileModuleDlg);
    } // setupUi

    void retranslateUi(QDialog *NewTileModuleDlg)
    {
        NewTileModuleDlg->setWindowTitle(QApplication::translate("NewTileModuleDlg", "NewTileModuleDlg", 0, QApplication::UnicodeUTF8));
        AddTMButton->setText(QApplication::translate("NewTileModuleDlg", "Add", 0, QApplication::UnicodeUTF8));
        EditTMButton->setText(QApplication::translate("NewTileModuleDlg", "Edit", 0, QApplication::UnicodeUTF8));
        SaveTMButton->setText(QApplication::translate("NewTileModuleDlg", "Save", 0, QApplication::UnicodeUTF8));
        DeleteTMButton->setText(QApplication::translate("NewTileModuleDlg", "Delete", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewTileModuleDlg", "Name", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NewTileModuleDlg", "Filename", 0, QApplication::UnicodeUTF8));
        ChooseTMButton->setText(QApplication::translate("NewTileModuleDlg", "Choose file", 0, QApplication::UnicodeUTF8));
        ImageLb->setText(QApplication::translate("NewTileModuleDlg", "Image", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewTileModuleDlg: public Ui_NewTileModuleDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWTILEMODULEDLG_H
