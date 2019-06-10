/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QTimeEdit *shutTimEdit;
    QDateEdit *shutDateEdit;
    QCheckBox *setDatebtn;
    QCheckBox *HideToSysTray;
    QPushButton *SettingBtn;
    QPushButton *canBtn;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(313, 159);
        gridLayoutWidget = new QWidget(Dialog);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(9, 9, 297, 141));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        shutTimEdit = new QTimeEdit(gridLayoutWidget);
        shutTimEdit->setObjectName(QString::fromUtf8("shutTimEdit"));

        gridLayout->addWidget(shutTimEdit, 0, 2, 1, 1);

        shutDateEdit = new QDateEdit(gridLayoutWidget);
        shutDateEdit->setObjectName(QString::fromUtf8("shutDateEdit"));
        shutDateEdit->setEnabled(false);

        gridLayout->addWidget(shutDateEdit, 0, 1, 1, 1);

        setDatebtn = new QCheckBox(gridLayoutWidget);
        setDatebtn->setObjectName(QString::fromUtf8("setDatebtn"));

        gridLayout->addWidget(setDatebtn, 0, 0, 1, 1);

        HideToSysTray = new QCheckBox(gridLayoutWidget);
        HideToSysTray->setObjectName(QString::fromUtf8("HideToSysTray"));
        HideToSysTray->setChecked(true);

        gridLayout->addWidget(HideToSysTray, 1, 0, 1, 1);

        SettingBtn = new QPushButton(gridLayoutWidget);
        SettingBtn->setObjectName(QString::fromUtf8("SettingBtn"));

        gridLayout->addWidget(SettingBtn, 1, 1, 1, 1);

        canBtn = new QPushButton(gridLayoutWidget);
        canBtn->setObjectName(QString::fromUtf8("canBtn"));

        gridLayout->addWidget(canBtn, 1, 2, 1, 1);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Coy\345\256\232\346\227\266\345\205\263\346\234\272", nullptr));
        setDatebtn->setText(QApplication::translate("Dialog", "\350\256\276\345\256\232\346\227\245\346\234\237", nullptr));
        HideToSysTray->setText(QApplication::translate("Dialog", "\351\232\220\350\227\217\345\210\260\347\263\273\347\273\237\346\211\230\347\233\230", nullptr));
        SettingBtn->setText(QApplication::translate("Dialog", "\350\256\276\347\275\256", nullptr));
        canBtn->setText(QApplication::translate("Dialog", "\346\222\244\351\224\200\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
