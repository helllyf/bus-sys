#include <QtGui/QApplication>
#include <QtGui>
#include <QTextCodec>
#include "user_widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    user_widget w;
    w.show();

    return a.exec();
}
