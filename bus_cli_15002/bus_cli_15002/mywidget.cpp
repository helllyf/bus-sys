#include "mywidget.h"
#include "ui_mywidget.h"
#include "led_public.h"
#include "mydialog.h"
#include <stdio.h>
#include <QDialog>
#include <string>
#include <QFile>
#include <QtXml>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    /* 产生单机信号时，与槽进行关联 */
    //connect(ui->showChildButton, SIGNAL(clicked()), this, SLOT(showChildDialog()));
    ui->LineEdit->clear();
    ui->LineEdit_2->clear();
    ui->LineEdit_3->clear();
    ui->LineEdit_4->clear();
    ui->LineEdit_5->clear();
    QFile file("bus_150.xml");
    if (!file.open(QIODevice::ReadOnly)) return ;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return ;
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    int flag=0;
    QDomNode n = docElem.firstChild();
    while(!n.isNull())
    {
        if (n.isElement())
        {
            QDomElement e = n.toElement();
            QDomNodeList list = e.childNodes();
            if (flag == 0)
            {
                for(int i=0; i<list.count(); i++)
                {
                    QDomNode node = list.at(i);
                    if(node.isElement())
                    {
                        const QString str = node.toElement().text();
                        switch(i)
                        {
                        //case 0:number=node.toElement().text().toInt();break;
                        case 1: ui->LineEdit->setText(str);
                                config_1_text(str.toStdString().c_str());
                                break;
                        case 2: ui->LineEdit_2->setText(str);
                                config_2_text(str.toStdString().c_str());
                                break;
                        case 3: ui->LineEdit_3->setText(str);
                                config_3_text(str.toStdString().c_str());
                                break;
                        case 4: ui->LineEdit_4->setText(str);
                                config_4_text(str.toStdString().c_str());
                                break;
                        case 5: ui->LineEdit_5->setText(str);
                                config_5_text(str.toStdString().c_str());
                                break;
                        default:break;
                        }
                    }
                }
            }
            flag++;
        }
        n = n.nextSibling();
    }
}

MyWidget::~MyWidget()
{
    delete ui;
}

/* 创建子窗口时 */
void MyWidget::showChildDialog()
{
    QDialog *dialog = new QDialog(this);
    dialog->show();
}

/* 重新登入产生的槽 */
void MyWidget::on_pushButton_clicked()
{
    close();
    MyDialog dlg;
    if (dlg.exec() == QDialog::Accepted)
        show();
}

/* 保存 */
void MyWidget::on_pushButton_2_clicked()
{
    QString xml_name = ui->lineEdit->text();
    qDebug()<<xml_name;

    if (xml_name != "bus_150.xml")
    {
        char xmlname[256] = {0};
        strcpy (xmlname, xml_name.toStdString().c_str());
        fopen (xmlname, "w");
    }
    QFile file1(xml_name);
    QFile file("bus_150.xml");

    if (!file.open(QIODevice::ReadOnly)) return ;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return ;
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    int flag=0;
    QDomNode n = docElem.firstChild();
    while(!n.isNull())
    {
        if (n.isElement())
        {
            QDomElement e = n.toElement();
            QDomNodeList list = e.childNodes();
            QDomNode oldnode;
            QDomNode newnode;
            if (flag == 0)
            {
                for(int i=0; i<list.count(); i++)
                {
                    QDomNode node = list.at(i);
                    if(node.isElement())
                    {
                        switch(i)
                        {
                        case 1: oldnode = node.firstChild();     //标签之间的内容作为节点的子节点出现，得到原来的子节点
                                node.firstChild().setNodeValue(ui->LineEdit->text());   //用提供的value值来设置子节点的内容
                                newnode = node.firstChild();     //值修改过后
                                node.replaceChild(newnode,oldnode);      //调用节点的replaceChild方法实现修改功能
                                break;
                        case 2: oldnode = node.firstChild();
                                node.firstChild().setNodeValue(ui->LineEdit_2->text());
                                newnode = node.firstChild();
                                node.replaceChild(newnode,oldnode);
                                break;
                        case 3: oldnode = node.firstChild();
                                node.firstChild().setNodeValue(ui->LineEdit_3->text());
                                newnode = node.firstChild();
                                node.replaceChild(newnode,oldnode);
                                break;
                        case 4: oldnode = node.firstChild();
                                node.firstChild().setNodeValue(ui->LineEdit_4->text());
                                newnode = node.firstChild();
                                node.replaceChild(newnode,oldnode);
                                break;
                        case 5: oldnode = node.firstChild();
                                node.firstChild().setNodeValue(ui->LineEdit_5->text());
                                newnode = node.firstChild();
                                node.replaceChild(newnode,oldnode);
                                break;
                        default:    break;
                        }
                    }
                }
            }
            flag++;
        }
        n = n.nextSibling();
    }

    if (!file1.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return ;
    QTextStream out(&file1);
    doc.save(out, 4);
    file1.close();
}
