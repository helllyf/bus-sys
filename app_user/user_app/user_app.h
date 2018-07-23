#ifndef USER_APP_H
#define USER_APP_H

#include <QDialog>

namespace Ui {
    class user_app;
}

class user_app : public QDialog
{
    Q_OBJECT

public:
    explicit user_app(QWidget *parent = 0);
    ~user_app();

public:
    int c_sid;

private slots:
    void on_pushButton_clicked();
    void listwidget_init ();
    void listwidget_2_init ();
    void on_search_bustton_clicked();

private:
    Ui::user_app *ui;
};

#endif // USER_APP_H
