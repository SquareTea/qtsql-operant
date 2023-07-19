#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QMainWindow>
#include <QMainWindow>
#include <QSqlTableModel>

namespace Ui {
class Form;
}

class Form : public QMainWindow
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    QSqlTableModel *model;


private:
    Ui::Form *ui;



private slots:
    void showData();
    void on_pushbut_clicked();
    void on_pushButton_clicked();
};

#endif // FORM_H
