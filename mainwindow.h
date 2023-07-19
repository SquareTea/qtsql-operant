#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <random>
#include <QSettings>
#include "form.h"
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool establishDatabaseConnection(const QString& host, int port, const QString& databaseName, const QString& username, const QString& password){

           db = QSqlDatabase::addDatabase("QMYSQL");
           db.setPort(port);
           db.setHostName(host);
           db.setDatabaseName(databaseName);
           db.setUserName(username);
           db.setPassword(password);


           if (!db.open()) {
               qWarning() << "Error connecting to the database:" << db.lastError().text();
           } else {
               qDebug() << "Connected to the database!";
           }

   }
    void readDatabaseConfig() {
        QSettings settings("config.ini", QSettings::IniFormat);

        QString host = settings.value("Database/Host").toString();
        int port = settings.value("Database/Port", 3306).toInt();
        QString databaseName = settings.value("Database/DatabaseName").toString();

        QString username = settings.value("Database/Username").toString();
        QString password = settings.value("Database/Password").toString();

        // Use the retrieved values to establish the database connection
        establishDatabaseConnection(host, port, databaseName, username, password);
    }

private slots:
    void on_pushButton_clicked();

    void on_actionView_triggered();

    int getRandomNumber(int min, int max) {
        // Create a random device to seed the random number generator
        std::random_device rd;

        // Use the random device to seed the random number engine
        std::mt19937 gen(rd());

        // Create a distribution to generate integers in the specified range [min, max]
        std::uniform_int_distribution<int> dist(min, max);

        // Generate and return a random number
        return dist(gen);
    }

    void on_actionConfig_Edit_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
};
#endif // MAINWINDOW_H
