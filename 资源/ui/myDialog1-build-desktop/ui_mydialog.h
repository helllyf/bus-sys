/********************************************************************************
** Form generated from reading UI file 'mydialog.ui'
**
** Created: Sat May 16 20:05:35 2015
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYDIALOG_H
#define UI_MYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MyDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_5;
    QPushButton *pushButton_8;
    QPushButton *pushButton_4;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *MyDialog)
    {
        if (MyDialog->objectName().isEmpty())
            MyDialog->setObjectName(QString::fromUtf8("MyDialog"));
        MyDialog->resize(465, 471);
        gridLayout = new QGridLayout(MyDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(MyDialog);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 1, 0, 1, 2);

        listWidget = new QListWidget(MyDialog);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout->addWidget(listWidget, 2, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton_5 = new QPushButton(MyDialog);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        verticalLayout->addWidget(pushButton_5);

        pushButton_8 = new QPushButton(MyDialog);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));

        verticalLayout->addWidget(pushButton_8);

        pushButton_4 = new QPushButton(MyDialog);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);

        pushButton_6 = new QPushButton(MyDialog);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        verticalLayout->addWidget(pushButton_6);

        pushButton_7 = new QPushButton(MyDialog);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        verticalLayout->addWidget(pushButton_7);

        pushButton = new QPushButton(MyDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(MyDialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);


        gridLayout->addLayout(verticalLayout, 2, 1, 1, 1);


        retranslateUi(MyDialog);
        QObject::connect(pushButton_2, SIGNAL(clicked()), MyDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(MyDialog);
    } // setupUi

    void retranslateUi(QDialog *MyDialog)
    {
        MyDialog->setWindowTitle(QApplication::translate("MyDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MyDialog", "22", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("MyDialog", "\344\270\212\350\241\214", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("MyDialog", "\344\270\213\350\241\214", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("MyDialog", "\345\275\223\345\211\215\347\253\231", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("MyDialog", "\350\256\251\345\272\247", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("MyDialog", "\351\230\262\350\264\274", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MyDialog", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MyDialog", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MyDialog: public Ui_MyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYDIALOG_H
