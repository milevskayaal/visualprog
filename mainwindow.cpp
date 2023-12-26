#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Инициализируем 2-е окно
    secondWindow = new Tickets();
    // подключаем к слоту запуска главного окна по кнопке во втором окне
    connect(secondWindow, &Tickets::firstWindow, this, &MainWindow::show);

    // Устанавливаем фиксированный размер окна
   // this->setMaximumSize(this->width(), this->height());
   // this->setMinimumSize(this->width(), this->height());

    // Инициализация объекта базы данных и подключение к ней
    db = new DataBase();
    db->connectToDataBase();

    // Создание модели данных и настройка таблицы
    model = new QSqlTableModel;
    model->setTable(TABLE);
    model->setHeaderData(0, Qt::Horizontal, "id");

    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    // Обновление таблицы и настройка формы редактирования и добавления записей
    updateTable();

    editForm = new EditRecord();
    editForm->setWindowModality(Qt::ApplicationModal);
    addForm = new AddRecord();
    addForm->setWindowModality(Qt::ApplicationModal);

    // Связывание сигналов и слотов для передачи данных между формами
    connect(addForm, SIGNAL(sendToWidget(QByteArray, QString, QString, int, QString, QString, QString, QDate, qint8, QString)),
            this, SLOT(addRecordDataBase(QByteArray, QString, QString, int, QString, QString, QString, QDate, qint8, QString)));
    connect(this, SIGNAL(sendForEdit(int, QByteArray, QString, QString, int, QString, QString, QString, QDate, qint8, QString)),
            editForm, SLOT(catchInfo(int, QByteArray, QString, QString, int, QString, QString, QString, QDate, qint8, QString)));
    connect(editForm, SIGNAL(sendToWidgetUpdate(int, QByteArray, QString, QString, int, QString, QString, QString, QDate, qint8, QString)),
            this, SLOT(editRecordDataBase(int, QByteArray, QString, QString, int, QString, QString, QString, QDate, qint8, QString)));

    // Связывание событий с кнопками и элементами меню
    connect(ui->menu1_add_record, SIGNAL(triggered()), this, SLOT(slotAdd()));
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(slotAdd()));
    connect(ui->menu1_edit_record, SIGNAL(triggered()), this, SLOT(slotEdit()));
    connect(ui->editButton, SIGNAL(clicked()), this, SLOT(slotEdit()));
    connect(ui->menu1_del_record, SIGNAL(triggered()), this, SLOT(slotDel()));
    connect(ui->delButton, SIGNAL(clicked()), this, SLOT(slotDel()));
    connect(ui->menu1_exit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->menu2_help, SIGNAL(triggered()), this, SLOT(slotInfo()));
    connect(ui->menu2_about, SIGNAL(triggered()), this, SLOT(slotAbout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Обновление таблицы
void MainWindow::updateTable()
{
    currRow = -1;
    currID = -1;
    model->select();
    model->setSort(8, Qt::AscendingOrder);

    // Выключение кнопок редактирования и удаления, если нет записей
    if (currRow == -1) {
        ui->menu1_edit_record->setEnabled(false);
        ui->menu1_del_record->setEnabled(false);
        ui->editButton->setEnabled(false);
        ui->delButton->setEnabled(false);
    } else {
        ui->menu1_edit_record->setEnabled(true);
        ui->menu1_del_record->setEnabled(true);
        ui->editButton->setEnabled(true);
        ui->delButton->setEnabled(true);
    }

    // Скрытие таблицы и отображение сообщения, если нет записей
    if (model->rowCount() == 0) {
        ui->label->show();
        ui->tableView->hide();
        return;
    }

    ui->label->hide();
    ui->tableView->show();
    QPixmap pic = QPixmap();

    // Загрузка изображений для каждой строки и установка их в ячейки таблицы
    for (int i = 0; i < model->rowCount(); i++) {
        pic.loadFromData(model->data(model->index(i, 1)).toByteArray());
        QLabel *imageLabel = new QLabel();
        imageLabel->setPixmap(pic.scaled(150, 400, Qt::KeepAspectRatio));
        ui->tableView->setIndexWidget(model->index(i, 1), imageLabel);
    }

    // Настройка размеров колонок
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(6, QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(8, QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(9, QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(10, QHeaderView::Stretch);

    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

// Слот для открытия формы добавления записи
void MainWindow::slotAdd()
{
    addForm->show();
}

// Слот для добавления записи в базу данных
void MainWindow::addRecordDataBase(const QByteArray &pic, const QString &name, const QString &author, const int &releaseYear, const QString &description, const QString &type, const QString &genres, const QDate &viewDate, const qint8 &score, const QString &comment)
{
    db->insertIntoTable(pic, name, author, releaseYear, description, type, genres, viewDate, score, comment);
    updateTable();
    currRow = -1;
    currID = -1;
}

// Слот для открытия формы редактирования записи
void MainWindow::slotEdit()
{
    if (currRow != -1) {
        QString name = model->data(model->index(currRow, 2)).toString();
        QString author = model->data(model->index(currRow, 3)).toString();
        int releaseYear = model->data(model->index(currRow, 4)).toDate().year();
        QString description = model->data(model->index(currRow, 5)).toString();
        QString type = model->data(model->index(currRow, 6)).toString();
        QString genres = model->data(model->index(currRow, 7)).toString();
        QDate viewDate = model->data(model->index(currRow, 8)).toDate();
        qint8 score = static_cast<qint8>(model->data(model->index(currRow, 9)).toInt());
        QString comment = model->data(model->index(currRow, 10)).toString();
        QByteArray inByteArray = model->data(model->index(currRow, 1)).toByteArray();
        emit sendForEdit(currID, inByteArray, name, author, releaseYear, description, type, genres, viewDate, score, comment);
        editForm->show();
    }
}

// Слот для редактирования записи в базе данных
void MainWindow::editRecordDataBase(const int &id, const QByteArray &pic, const QString &name, const QString &author, const int &releaseYear, const QString &description, const QString &type, const QString &genres, const QDate &viewDate, const qint8 &score, const QString &comment)
{
    currRow = -1;
    currID = -1;
    db->editInTable(id, pic, name, author, releaseYear, description, type, genres, viewDate, score, comment);
    updateTable();
}

// Слот для удаления записи из базы данных
void MainWindow::slotDel()
{
    if (currRow != -1) {
        db->deleteFromDatabase(currID);
        updateTable();
        QMessageBox::information(nullptr, "Уведомление", "Запись успешно удалена");
        currRow = -1;
        currID = -1;
    }
}

// Слот для открытия формы справки
void MainWindow::slotInfo()
{
    HelpInformation* form = new HelpInformation();
    form->setWindowModality(Qt::ApplicationModal);
    form->show();
}

// Слот для открытия окна "О программе"
void MainWindow::slotAbout()
{
    QMessageBox::about(this, "О программе", "Автор приложения: Алёна Милевская, ИП-115\n\n                    2023 г, СибГУТИ");
}

// Слот для обработки события клика по строке таблицы
void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    ui->menu1_edit_record->setEnabled(true);
    ui->menu1_del_record->setEnabled(true);
    ui->editButton->setEnabled(true);
    ui->delButton->setEnabled(true);
    currID = model->data(model->index(index.row(), 0)).toInt();
    currRow = index.row();
}

void MainWindow::on_ticketsButton_clicked()
{
    secondWindow->show();  // Показываем окно
    this->close();    // Закрываем основное окно
}
