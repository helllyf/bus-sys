#include <QtGui/QApplication>
#include <QTextCodec>
#include "mywidget.h"
#include "mydialog.h"
#include "LedUtils.h"
#include "packet.h"
#include "system.h"
#include "uart.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    MyWidget w;
    MyDialog dialog;    //新建MyDialog类对象
    if (dialog.exec() == QDialog::Accepted){
        w.show();           //如果按下“进入主界面”，则显示主界面
        return a.exec();
    }
    else return 0;
}
