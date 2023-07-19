#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <form.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Initialize the MySQL database connection
    readDatabaseConfig();

}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}


void MainWindow::on_pushButton_clicked()
{
        int min = 100000;
       int max = 199999;
        QSettings settings("config.ini", QSettings::IniFormat);
        QString tableName = settings.value("Database/TableName").toString();
       int randomNumber = getRandomNumber(min, max);
        QString name = ui->lineEdit->text();
       // int id = ui->lineEdit_3->text().toInt();
        int age = ui->lineEdit_2->text().toInt();
        QString newValue = ui->label_4->text() + " " + QString::number(randomNumber);
        ui->label_4->setText(newValue);
        QSqlQuery query;
        QString tbn = tableName; // Replace this with the actual table name
        QString queryStr = "INSERT INTO " + tbn + " (ID, Name, Age) VALUES (:ID, :Name, :Age)";
        query.prepare(queryStr);
        query.bindValue(":ID", randomNumber);
        query.bindValue(":Name", name);
        query.bindValue(":Age", age);

        if (query.exec()) {
            qDebug() << "Data inserted successfully!";
        } else {
            qWarning() << "Error inserting data:" << query.lastError().text();
        }
}


void MainWindow::on_actionView_triggered()
{
 Form *form1 = new Form(this);
form1->showNormal();
}


void MainWindow::on_actionConfig_Edit_triggered()
{
    QString fileName = "config.ini";
       if (fileName.isEmpty()) return;

       QProcess::startDetached("xdg-open", QStringList() << fileName);
}

