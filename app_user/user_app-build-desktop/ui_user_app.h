/********************************************************************************
** Form generated from reading UI file 'user_app.ui'
**
** Created: Fri Nov 27 17:29:31 2015
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USER_APP_H
#define UI_USER_APP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_user_app
{
public:
    QGridLayout *gridLayout_4;
    QLabel *label_2;
    QGridLayout *gridLayout_3;
    QLabel *label_6;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QPushButton *search_bustton;
    QLabel *label_4;
    QListWidget *listWidget_2;

    void setupUi(QDialog *user_app)
    {
        if (user_app->objectName().isEmpty())
            user_app->setObjectName(QString::fromUtf8("user_app"));
        user_app->resize(308, 369);
        user_app->setStyleSheet(QString::fromUtf8("QDialog{\n"
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
        gridLayout_4 = new QGridLayout(user_app);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_2 = new QLabel(user_app);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setFamily(QString::fromUtf8("Aharoni"));
        font.setPointSize(28);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_2, 0, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_6 = new QLabel(user_app);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Aharoni"));
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setWeight(75);
        label_6->setFont(font1);

        gridLayout_3->addWidget(label_6, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lineEdit = new QLineEdit(user_app);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout_2->addWidget(lineEdit, 0, 1, 1, 1);

        label = new QLabel(user_app);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setWeight(50);
        label->setFont(font2);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        pushButton = new QPushButton(user_app);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        QFont font3;
        font3.setPointSize(10);
        pushButton->setFont(font3);
        pushButton->setIconSize(QSize(16, 16));

        gridLayout_2->addWidget(pushButton, 0, 2, 1, 1);

        listWidget = new QListWidget(user_app);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout_2->addWidget(listWidget, 1, 0, 1, 3);


        gridLayout_3->addLayout(gridLayout_2, 1, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 1, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_5 = new QLabel(user_app);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);

        verticalLayout->addWidget(label_5);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        lineEdit_3 = new QLineEdit(user_app);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(80);
        sizePolicy1.setVerticalStretch(80);
        sizePolicy1.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEdit_3, 1, 1, 1, 1);

        lineEdit_2 = new QLineEdit(user_app);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        sizePolicy1.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEdit_2, 0, 1, 1, 1);

        label_3 = new QLabel(user_app);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font4;
        font4.setPointSize(12);
        label_3->setFont(font4);

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        search_bustton = new QPushButton(user_app);
        search_bustton->setObjectName(QString::fromUtf8("search_bustton"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(search_bustton->sizePolicy().hasHeightForWidth());
        search_bustton->setSizePolicy(sizePolicy2);
        QFont font5;
        font5.setPointSize(11);
        search_bustton->setFont(font5);

        gridLayout->addWidget(search_bustton, 1, 2, 1, 1);

        label_4 = new QLabel(user_app);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font4);

        gridLayout->addWidget(label_4, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);


        verticalLayout_3->addLayout(verticalLayout);

        listWidget_2 = new QListWidget(user_app);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));

        verticalLayout_3->addWidget(listWidget_2);


        gridLayout_4->addLayout(verticalLayout_3, 2, 0, 1, 1);


        retranslateUi(user_app);

        QMetaObject::connectSlotsByName(user_app);
    } // setupUi

    void retranslateUi(QDialog *user_app)
    {
        user_app->setWindowTitle(QApplication::translate("user_app", "user_app", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("user_app", "\345\234\260\351\223\201\350\267\257\347\272\277\345\212\251\346\211\213", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("user_app", "\345\275\223\345\211\215\347\253\231\347\202\271\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("user_app", "\350\257\267\350\276\223\345\205\245\345\234\260\351\223\201\347\272\277\350\267\257\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("user_app", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("user_app", "\347\272\277\350\267\257\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("user_app", "\350\265\267\345\247\213\347\253\231: ", 0, QApplication::UnicodeUTF8));
        search_bustton->setText(QApplication::translate("user_app", "\346\220\234\347\264\242", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("user_app", "\347\273\210\347\202\271\347\253\231: ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class user_app: public Ui_user_app {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_APP_H
