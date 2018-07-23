/********************************************************************************
** Form generated from reading UI file 'mywidget.ui'
**
** Created: Thu May 21 06:05:20 2015
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWIDGET_H
#define UI_MYWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *Label;
    QLineEdit *LineEdit;
    QLabel *Label_2;
    QLineEdit *LineEdit_2;
    QLabel *Label_3;
    QLineEdit *LineEdit_3;
    QLabel *Label_4;
    QLineEdit *LineEdit_4;
    QLabel *Label_5;
    QLineEdit *LineEdit_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QWidget *MyWidget)
    {
        if (MyWidget->objectName().isEmpty())
            MyWidget->setObjectName(QString::fromUtf8("MyWidget"));
        MyWidget->resize(542, 271);
        verticalLayout_2 = new QVBoxLayout(MyWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setFormAlignment(Qt::AlignCenter);
        formLayout->setContentsMargins(6, 0, -1, -1);
        Label = new QLabel(MyWidget);
        Label->setObjectName(QString::fromUtf8("Label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, Label);

        LineEdit = new QLineEdit(MyWidget);
        LineEdit->setObjectName(QString::fromUtf8("LineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, LineEdit);

        Label_2 = new QLabel(MyWidget);
        Label_2->setObjectName(QString::fromUtf8("Label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, Label_2);

        LineEdit_2 = new QLineEdit(MyWidget);
        LineEdit_2->setObjectName(QString::fromUtf8("LineEdit_2"));

        formLayout->setWidget(2, QFormLayout::FieldRole, LineEdit_2);

        Label_3 = new QLabel(MyWidget);
        Label_3->setObjectName(QString::fromUtf8("Label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, Label_3);

        LineEdit_3 = new QLineEdit(MyWidget);
        LineEdit_3->setObjectName(QString::fromUtf8("LineEdit_3"));

        formLayout->setWidget(3, QFormLayout::FieldRole, LineEdit_3);

        Label_4 = new QLabel(MyWidget);
        Label_4->setObjectName(QString::fromUtf8("Label_4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, Label_4);

        LineEdit_4 = new QLineEdit(MyWidget);
        LineEdit_4->setObjectName(QString::fromUtf8("LineEdit_4"));

        formLayout->setWidget(4, QFormLayout::FieldRole, LineEdit_4);

        Label_5 = new QLabel(MyWidget);
        Label_5->setObjectName(QString::fromUtf8("Label_5"));

        formLayout->setWidget(5, QFormLayout::LabelRole, Label_5);

        LineEdit_5 = new QLineEdit(MyWidget);
        LineEdit_5->setObjectName(QString::fromUtf8("LineEdit_5"));

        formLayout->setWidget(5, QFormLayout::FieldRole, LineEdit_5);


        verticalLayout_2->addLayout(formLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(MyWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setEnabled(true);
        QFont font;
        font.setFamily(QString::fromUtf8("Algerian"));
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setInputMethodHints(Qt::ImhNone);
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(false);
        label->setOpenExternalLinks(false);

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(MyWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_2 = new QPushButton(MyWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(MyWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(MyWidget);

        QMetaObject::connectSlotsByName(MyWidget);
    } // setupUi

    void retranslateUi(QWidget *MyWidget)
    {
        MyWidget->setWindowTitle(QApplication::translate("MyWidget", "MyWidget", 0, QApplication::UnicodeUTF8));
        Label->setText(QApplication::translate("MyWidget", "\345\275\223\345\211\215\347\253\231\357\274\232", 0, QApplication::UnicodeUTF8));
        Label_2->setText(QApplication::translate("MyWidget", "\344\270\213\344\270\200\347\253\231\357\274\232", 0, QApplication::UnicodeUTF8));
        Label_3->setText(QApplication::translate("MyWidget", "\347\273\210\347\202\271\347\253\231\357\274\232", 0, QApplication::UnicodeUTF8));
        Label_4->setText(QApplication::translate("MyWidget", "\350\256\251\345\272\247\357\274\232", 0, QApplication::UnicodeUTF8));
        Label_5->setText(QApplication::translate("MyWidget", "\351\230\262\350\264\274\357\274\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MyWidget", "\350\257\267\350\276\223\345\205\245xml\346\226\207\344\273\266\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MyWidget", "\345\257\274\345\207\272", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MyWidget", "\350\277\224\345\233\236", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MyWidget: public Ui_MyWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWIDGET_H
