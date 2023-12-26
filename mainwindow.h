#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>
#include "addrecord.h"
#include "editrecord.h"
#include "helpinformation.h"
#include "database.h"
#include "tickets.h"


// Пространство имен Ui содержит класс, созданный в Qt Designer для главного окна
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Конструктор класса MainWindow
    explicit MainWindow(QWidget *parent = nullptr);

    // Деструктор класса MainWindow
    ~MainWindow();

public slots:
    // Слоты для обработки действий пользователя
    void slotAdd();
    void slotEdit();
    void slotDel();
    void slotInfo();
    void slotAbout();
    void updateTable();
    void addRecordDataBase(const QByteArray &pic, const QString &name, const QString &author, const int &releaseYear, const QString &description, const QString &type, const QString &genres, const QDate &viewDate, const qint8 &score, const QString &comment);
    void editRecordDataBase(const int &id, const QByteArray &pic, const QString &name, const QString &author, const int &releaseYear, const QString &description, const QString &type, const QString &genres, const QDate &viewDate, const qint8 &score, const QString &comment);

signals:
    // Сигнал для передачи данных форме редактирования
    void sendForEdit(const int &ip, const QByteArray &pic, const QString &name, const QString &author, const int &releaseYear, const QString &description, const QString &type, const QString &genres, const QDate &viewDate, const qint8 &score, const QString &comment);

private slots:
    // Слот для обработки нажатия на запись в таблице
    void on_tableView_clicked(const QModelIndex &index);

    void on_ticketsButton_clicked();

private:
    // Указатель на объект интерфейса Ui::MainWindow
    Ui::MainWindow *ui;

     Tickets *secondWindow;

    // Указатели на объекты форм добавления, редактирования и базы данных
    AddRecord *addForm;
    EditRecord *editForm;
    DataBase *db;

    // Модель данных для работы с таблицей в базе данных
    QSqlTableModel *model;

    // Текущая выбранная строка и ID записи
    int currRow = -1;
    int currID = -1;
};

#endif // MAINWINDOW_H
