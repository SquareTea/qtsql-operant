#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

Form::Form(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    model = new QSqlTableModel(this);

}

Form::~Form()
{
    delete ui;
    delete model;

}
void Form::showData()
{    QSettings settings("config.ini", QSettings::IniFormat);
     QString tableName = settings.value("Database/TableName").toString();
     model->setTable(tableName);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Name");
    model->setHeaderData(2, Qt::Horizontal, "Age");
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();


}
void Form::on_pushbut_clicked()
{
showData();
}


void Form::on_pushButton_clicked()
{     QSettings settings("config.ini", QSettings::IniFormat);
      QString tableName = settings.value("Database/TableName").toString();
    model->setTable(tableName);
       model->select();
    // Filter the data based on the search input
       if (!ui->lineEdit->text().isEmpty()) {
           QString filter = QString("ID LIKE '%%1%' OR Name LIKE '%%1%' OR Age LIKE '%%1%'").arg(ui->lineEdit->text());
           model->setFilter(filter);
       } else {
           model->setFilter(""); // If the search input is empty, clear the filter
       }

       // Refresh the model to apply the filter
       model->select();
       model->setHeaderData(0, Qt::Horizontal, "ID");
       model->setHeaderData(1, Qt::Horizontal, "Name");
       model->setHeaderData(2, Qt::Horizontal, "Age");
       ui->tableView->setModel(model);
       ui->tableView->resizeColumnsToContents();
}

