/********************************************************************************
** Form generated from reading UI file 'mydialog.ui'
**
** Created: Tue May 19 20:50:21 2015
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
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MyDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_5;
    QPushButton *pushButton_8;
    QPushButton *pushButton_4;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton;
    QPushButton *exit_button;

    void setupUi(QDialog *MyDialog)
    {
        if (MyDialog->objectName().isEmpty())
            MyDialog->setObjectName(QString::fromUtf8("MyDialog"));
        MyDialog->resize(458, 540);
        MyDialog->setStyleSheet(QString::fromUtf8("QDialog{\n"
"border-image:url(:/image/back_ground.png);\n"
"}\n"
"QListWidget\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(74, 172, 152, 251), stop:1 rgba(255, 255, 255, 255));\n"
"}\n"
"QPuchButton\n"
"{\n"
"	background-color: rgb(170, 255, 255);\n"
"	border-style:outset;\n"
"	border-width:5px;\n"
"	border-radius:10px;\n"
"	border-color:rgba(255,255,255,30);\n"
"	font:bold 12px;\n"
"	color:rgba(0,0,0,100);\n"
"	padding:6px;\n"
"}\n"
"QPushButton:hover\n"
"{\n"
"	background-color:rgba(100,255,100,100);\n"
"	border-color:rgba(255,255,255,200);\n"
"	color:rgba(0,0,0,200);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: rgb(155, 206, 164);\n"
"	border-style:inset;\n"
"	color:rgba(0,0,0,100);\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(MyDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label = new QLabel(MyDialog);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(1677, 1677));
        QFont font;
        font.setPointSize(19);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_3 = new QLabel(MyDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font1;
        font1.setPointSize(13);
        font1.setBold(false);
        font1.setWeight(50);
        label_3->setFont(font1);

        horizontalLayout_2->addWidget(label_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        label_2 = new QLabel(MyDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font2;
        font2.setPointSize(13);
        font2.setBold(true);
        font2.setItalic(false);
        font2.setUnderline(false);
        font2.setWeight(75);
        font2.setStrikeOut(false);
        label_2->setFont(font2);

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_3 = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        listWidget = new QListWidget(MyDialog);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        horizontalLayout->addWidget(listWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton_5 = new QPushButton(MyDialog);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        QFont font3;
        font3.setPointSize(12);
        pushButton_5->setFont(font3);

        verticalLayout->addWidget(pushButton_5);

        pushButton_8 = new QPushButton(MyDialog);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setFont(font3);

        verticalLayout->addWidget(pushButton_8);

        pushButton_4 = new QPushButton(MyDialog);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setFont(font3);

        verticalLayout->addWidget(pushButton_4);

        pushButton_6 = new QPushButton(MyDialog);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setFont(font3);

        verticalLayout->addWidget(pushButton_6);

        pushButton_7 = new QPushButton(MyDialog);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setFont(font3);

        verticalLayout->addWidget(pushButton_7);

        pushButton = new QPushButton(MyDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setFont(font3);

        verticalLayout->addWidget(pushButton);

        exit_button = new QPushButton(MyDialog);
        exit_button->setObjectName(QString::fromUtf8("exit_button"));
        exit_button->setFont(font3);

        verticalLayout->addWidget(exit_button);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(MyDialog);
        QObject::connect(exit_button, SIGNAL(clicked()), MyDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(MyDialog);
    } // setupUi

    void retranslateUi(QDialog *MyDialog)
    {
        MyDialog->setWindowTitle(QApplication::translate("MyDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MyDialog", "150:15001", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MyDialog", "\345\217\221\351\200\201\346\210\220\345\212\237", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MyDialog", "\344\270\213\350\241\214", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("MyDialog", "\344\270\212\350\241\214", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("MyDialog", "\344\270\213\350\241\214", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("MyDialog", "\346\212\245\347\253\231", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("MyDialog", "\350\256\251\345\272\247", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("MyDialog", "\351\230\262\350\264\274", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MyDialog", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        exit_button->setText(QApplication::translate("MyDialog", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MyDialog: public Ui_MyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYDIALOG_H
