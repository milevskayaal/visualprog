#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QTranslator>
#include <QLibraryInfo>
#include <QSplashScreen>
#include <QTime>
#include <QPainter>

// Функция для имитации загрузки модулей с отображением сообщений на экране

void LoadModules(QSplashScreen* psplash) {
    QTime time;
    time.start();

    for (int i = 0; i < 100;){
        if (time.elapsed()>2){ //скорость заполнения процентов
            time.start();
            i++;
        }

        psplash->showMessage("Загрузка..." + QString::number(i) + "%",
                             Qt::AlignCenter, Qt::black);
        qApp->processEvents();
    }
}

int main(int argc, char *argv[]) {
    // Инициализация приложения
    QApplication a(argc, argv);

    // Загрузка таблицы стилей из внутреннего ресурса
    QFile f(":/style/style.qss");
    if (!f.exists()) {
        // Вывод сообщения об ошибке, если файл стилей не найден
        printf("Невозможно установить таблицу стилей, файл не найден\n");
    } else {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }

    // Загрузка русского перевода для Qt
    QTranslator qtTranslator;
    qtTranslator.load("qt_ru", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    // Создание основного окна
    MainWindow w;

    // Создание экрана SplashScreen с изображением и отображением
    QSplashScreen splash(QPixmap("C:\\Users\\milev\\Desktop\\VisualProg\\curs\\resources\\images\\main.jpg"));
    splash.show();

    QFile file("C:\\Users\\milev\\Desktop\\VisualProg\\curs\\css\\StyleForKursWork.css");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(file.readAll());

    // Имитация загрузки модулей с отображением на SplashScreen
    LoadModules(&splash);

    // Закрытие SplashScreen и открытие основного окна
    splash.finish(&w);
    w.showMaximized();

    // Запуск цикла обработки событий
    return a.exec();
}
