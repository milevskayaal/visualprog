#ifndef TICKETS_H
#define TICKETS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QPushButton>

namespace Ui {
class Tickets;
}

class Tickets : public QDialog
{
    Q_OBJECT

public:
    QSqlDatabase mydb;

    void connClose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen()
    {
        mydb=QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C:/Users/milev/Desktop/VisualProg/curs/db/filmoteka.db");
        //проверка на чтение БД
        if(mydb.open()) {
            qDebug("Connected...");
            return true;
        }
        else {
            qDebug("Failed to open the database");
            return false;
        }
    }

public:
    explicit Tickets(QWidget *parent = 0);
    ~Tickets();

signals:
    void firstWindow();  // Сигнал для первого окна на открытие

public slots:
    void showPosts();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::Tickets *ui;
    QPushButton *B1;  QPushButton *B2;  QPushButton *B3;  QPushButton *B4;  QPushButton *B5;  QPushButton *B6;
    QPushButton *B7;  QPushButton *B8;  QPushButton *B9;  QPushButton *B10; QPushButton *B11; QPushButton *B12;
    QPushButton *B13; QPushButton *B14; QPushButton *B15; QPushButton *B16; QPushButton *B17; QPushButton *B18;
    QPushButton *B19; QPushButton *B20; QPushButton *B21; QPushButton *B22; QPushButton *B23; QPushButton *B24;
    QPushButton *B25; QPushButton *B26; QPushButton *B27; QPushButton *B28; QPushButton *B29; QPushButton *B30;
    QPushButton *B31; QPushButton *B32; QPushButton *B33; QPushButton *B34; QPushButton *B35; QPushButton *B36;
    QPushButton *B37; QPushButton *B38; QPushButton *B39; QPushButton *B40;

};

#endif // TICKETS_H
