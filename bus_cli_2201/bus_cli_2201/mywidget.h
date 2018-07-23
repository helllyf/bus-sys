#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
namespace Ui {
    class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

private:
    Ui::MyWidget *ui;

public slots:
    void showChildDialog();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // MYWIDGET_H
