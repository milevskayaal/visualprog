#include "helpinformation.h"
#include "ui_helpinformation.h"

// Конструктор класса HelpInformation
HelpInformation::HelpInformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpInformation)
{
    // Инициализация пользовательского интерфейса
    ui->setupUi(this);

    // Установка минимального и максимального размеров окна
    this->setMaximumSize(this->width(), this->height());
    this->setMinimumSize(this->width(), this->height());

    // Установка соединений (сигналов и слотов) для кнопок и текстового браузера
    connect(ui->textBrowser, SIGNAL(anchorClicked(QUrl)), this, SLOT(on_textBrowser_anchorClicked(QUrl)));
    connect(ui->backButton, SIGNAL(clicked()), ui->textBrowser, SLOT(backward()));
    connect(ui->textBrowser, SIGNAL(backwardAvailable(bool)), ui->backButton, SLOT(setEnabled(bool)));

    // Установка источника для текстового браузера (открывается HTML-страница из ресурсов)
    ui->textBrowser->setSource(QUrl::fromLocalFile(":/helpInformation/index.html"));
}

// Деструктор класса HelpInformation
HelpInformation::~HelpInformation()
{
    // Освобождение памяти, выделенной для пользовательского интерфейса
    delete ui;
}

