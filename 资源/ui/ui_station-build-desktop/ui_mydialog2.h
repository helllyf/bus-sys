/********************************************************************************
** Form generated from reading UI file 'mydialog2.ui'
**
** Created: Sat May 2 22:11:53 2015
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYDIALOG2_H
#define UI_MYDIALOG2_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MyDIalog2
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *Label;
    QLineEdit *LineEdit;
    QLabel *Label_2;
    QLineEdit *LineEdit_2;
    QLabel *Label_3;
    QLineEdit *LineEdit_3;
    QLabel *Label_4;
    QLineEdit *LineEdit_4;

    void setupUi(QDialog *MyDIalog2)
    {
        if (MyDIalog2->objectName().isEmpty())
            MyDIalog2->setObjectName(QString::fromUtf8("MyDIalog2"));
        MyDIalog2->resize(400, 300);
        verticalLayout = new QVBoxLayout(MyDIalog2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        Label = new QLabel(MyDIalog2);
        Label->setObjectName(QString::fromUtf8("Label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, Label);

        LineEdit = new QLineEdit(MyDIalog2);
        LineEdit->setObjectName(QString::fromUtf8("LineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, LineEdit);

        Label_2 = new QLabel(MyDIalog2);
        Label_2->setObjectName(QString::fromUtf8("Label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, Label_2);

        LineEdit_2 = new QLineEdit(MyDIalog2);
        LineEdit_2->setObjectName(QString::fromUtf8("LineEdit_2"));

        formLayout->setWidget(1, QFormLayout::FieldRole, LineEdit_2);

        Label_3 = new QLabel(MyDIalog2);
        Label_3->setObjectName(QString::fromUtf8("Label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, Label_3);

        LineEdit_3 = new QLineEdit(MyDIalog2);
        LineEdit_3->setObjectName(QString::fromUtf8("LineEdit_3"));

        formLayout->setWidget(2, QFormLayout::FieldRole, LineEdit_3);

        Label_4 = new QLabel(MyDIalog2);
        Label_4->setObjectName(QString::fromUtf8("Label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, Label_4);

        LineEdit_4 = new QLineEdit(MyDIalog2);
        LineEdit_4->setObjectName(QString::fromUtf8("LineEdit_4"));

        formLayout->setWidget(3, QFormLayout::FieldRole, LineEdit_4);


        verticalLayout->addLayout(formLayout);


        retranslateUi(MyDIalog2);

        QMetaObject::connectSlotsByName(MyDIalog2);
    } // setupUi

    void retranslateUi(QDialog *MyDIalog2)
    {
        MyDIalog2->setWindowTitle(QApplication::translate("MyDIalog2", "MyDIalog2", 0, QApplication::UnicodeUTF8));
        Label->setText(QApplication::translate("MyDIalog2", "\345\275\223\345\211\215\347\253\231\357\274\232", 0, QApplication::UnicodeUTF8));
        Label_2->setText(QApplication::translate("MyDIalog2", "\345\205\254\344\272\244\357\274\232", 0, QApplication::UnicodeUTF8));
        Label_3->setText(QApplication::translate("MyDIalog2", "\346\211\200\345\234\250\347\253\231\347\202\271\357\274\232", 0, QApplication::UnicodeUTF8));
        Label_4->setText(QApplication::translate("MyDIalog2", "\350\267\235\347\246\273\346\234\254\347\253\231\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MyDIalog2: public Ui_MyDIalog2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYDIALOG2_H
