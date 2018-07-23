#ifndef USER_WIDGET_H
#define USER_WIDGET_H

#include <QWidget>

namespace Ui {
    class user_widget;
}

class user_widget : public QWidget
{
    Q_OBJECT

public:
    explicit user_widget(QWidget *parent = 0);
    ~user_widget();

private:
    Ui::user_widget *ui;
public:
    int c_sid;
private slots:
    void on_enter_clicked ();
    void listwidget_init ();
};

#endif // USER_WIDGET_H
