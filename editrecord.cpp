#include "editrecord.h"
#include "ui_editrecord.h"

// Конструктор класса EditRecord
EditRecord::EditRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditRecord)
{
    // Инициализация пользовательского интерфейса
    ui->setupUi(this);

    // Установка минимального и максимального размеров окна
    this->setMaximumSize(this->width(), this->height());
    this->setMinimumSize(this->width(), this->height());
}

// Деструктор класса EditRecord
EditRecord::~EditRecord()
{
    // Освобождение памяти, выделенной для пользовательского интерфейса
    delete ui;
}

// Обработчик события "Нажатие на кнопку загрузки изображения"
void EditRecord::on_uploadPicture_clicked()
{
    // Открытие диалога выбора файла изображения
    pathImage = QFileDialog::getOpenFileName(nullptr, "Выберите изображение", QDir::currentPath(), "*.png *.jpg *.gif *.jpeg *.webp");
    if (pathImage != "") {
        // Загрузка выбранного изображения
        QImage image(pathImage);
        QPixmap pic = QPixmap::fromImage(image);

        qDebug() << pathImage;

        QPixmap inPixmap;
        inPixmap.load(pathImage);
        QByteArray inByteArray;
        QBuffer inBuffer(&inByteArray);
        inBuffer.open(QIODevice::WriteOnly);
        inPixmap.save(&inBuffer, "PNG");

        // Сохранение изображения в байтовый массив
        savePic = inByteArray;

        // Установка изображения в виджет
        ui->picture->setPixmap(pic);
        ui->picture->setPixmap(pic.scaled(ui->picture->width(), ui->picture->height(), Qt::KeepAspectRatio));
    }
}

// Обработчик события "Получение информации для редактирования записи"
void EditRecord::catchInfo(const int &id, const QByteArray &pic, const QString &name, const QString &author, const int &releaseYear, const QString &description, const QString &type, const QString &genres, const QDate &viewDate, const qint8 &score, const QString &comment)
{
    // Установка информации в соответствующие виджеты
    this->id = id;
    ui->nameLineEdit->setText(name);
    ui->authorLineEdit->setText(author);
    ui->releaseDateEdit->setDate(QDate(releaseYear, 1, 1));
    ui->descriptionTextEdit->setText(description);
    ui->typeComboBox->setCurrentText(type);
    ui->genresLineEdit->setText(genres);
    ui->viewDateEdit->setDate(viewDate);
    ui->scoreComboBox->setCurrentIndex(score);
    ui->commentTextEdit->setText(comment);

    QPixmap img = QPixmap();
    savePic = pic;
    img.loadFromData(pic);
    ui->picture->setPixmap(img.scaled(ui->picture->width(), ui->picture->height(), Qt::KeepAspectRatio));
}

// Обработчик события "Нажатие на кнопку отмены"
void EditRecord::on_CancelButton_clicked()
{
    // Закрытие окна
    this->close();
}

// Обработчик события "Нажатие на кнопку сохранения изменений"
void EditRecord::on_SaveButton_clicked()
{
    // Получение данных из виджетов
    QString name = ui->nameLineEdit->text();
    if (name == "") {
        QMessageBox::information(nullptr, "Уведомление", "Заполните поле \"Название\"");
        return;
    }
    QString author = ui->authorLineEdit->text();
    if (author == "") {
        QMessageBox::information(nullptr, "Уведомление", "Заполните поле \"Автор(-ы)\"");
        return;
    }
    int releaseYear = ui->releaseDateEdit->date().year();

    QString description = ui->descriptionTextEdit->toPlainText();
    if (description == "") {
        QMessageBox::information(nullptr, "Уведомление", "Заполните поле \"Описание\"");
        return;
    }
    QString type = ui->typeComboBox->currentText();

    QString genres = ui->genresLineEdit->text();
    if (genres == "") {
        QMessageBox::information(nullptr, "Уведомление", "Заполните поле \"Жанр(-ы)\"");
        return;
    }

    QDate viewDate = ui->viewDateEdit->date();
    qint8 score = (qint8)ui->scoreComboBox->currentIndex();
    QString comment = ui->commentTextEdit->toPlainText();
    if (comment == "") {
        QMessageBox::information(nullptr, "Уведомление", "Заполните поле \"Комментарий\"");
        return;
    }
    QByteArray pic = savePic;

    // Эмитирование сигнала для обновления записи в основном окне
    emit sendToWidgetUpdate(id, pic, name, author, releaseYear, description, type, genres, viewDate, score, comment);

    // Вывод уведомления об успешном изменении записи
    QMessageBox::information(nullptr, "Уведомление", "Запись успешно изменена!");

    // Закрытие окна
    close();
}
