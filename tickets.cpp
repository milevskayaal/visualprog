#include "tickets.h"
#include "ui_tickets.h"
#include <QMessageBox>

#define VVOD_FAM "^[А-Я][а-я]+([а-я])"

Tickets::Tickets(QWidget *parent) : QDialog(parent),
    ui(new Ui::Tickets)
{
    ui->setupUi(this);

    //проверка на ввод фамилии
    QRegExp proverka1(VVOD_FAM);
    QRegExpValidator *valiName = new QRegExpValidator(proverka1, this);
    ui->txt_surname->setValidator(valiName);

    //проверка на чтение БД
    if(connOpen()) {
        qDebug("Connected...");
    }
    else {
        qDebug("Failed to open the database");
    }

    // Создаем объекты QPushButton - отрисовка схемы зала
    //первый ряд
    B1 = new QPushButton("1", this);   B1->setCheckable(true);  B1->setGeometry(250, 200, 50, 50);
    B2 = new QPushButton("2", this);   B2->setCheckable(true);  B2->setGeometry(310, 200, 50, 50);
    B3 = new QPushButton("3", this);   B3->setCheckable(true);  B3->setGeometry(370, 200, 50, 50);
    B4 = new QPushButton("4", this);   B4->setCheckable(true);  B4->setGeometry(430, 200, 50, 50);
    B5 = new QPushButton("5", this);   B5->setCheckable(true);  B5->setGeometry(490, 200, 50, 50);
    B6 = new QPushButton("6", this);   B6->setCheckable(true);  B6->setGeometry(550, 200, 50, 50);
    B7 = new QPushButton("7", this);   B7->setCheckable(true);  B7->setGeometry(610, 200, 50, 50);
    B8 = new QPushButton("8", this);   B8->setCheckable(true);  B8->setGeometry(670, 200, 50, 50);
    B9 = new QPushButton("9", this);   B9->setCheckable(true);  B9->setGeometry(730, 200, 50, 50);
    B10 = new QPushButton("10", this); B10->setCheckable(true); B10->setGeometry(790, 200, 50, 50);

    //второй ряд
    B11 = new QPushButton("11", this); B11->setCheckable(true); B11->setGeometry(250, 260, 50, 50);
    B12 = new QPushButton("12", this); B12->setCheckable(true); B12->setGeometry(310, 260, 50, 50);
    B13 = new QPushButton("13", this); B13->setCheckable(true); B13->setGeometry(370, 260, 50, 50);
    B14 = new QPushButton("14", this); B14->setCheckable(true); B14->setGeometry(430, 260, 50, 50);
    B15 = new QPushButton("15", this); B15->setCheckable(true); B15->setGeometry(490, 260, 50, 50);
    B16 = new QPushButton("16", this); B16->setCheckable(true); B16->setGeometry(550, 260, 50, 50);
    B17 = new QPushButton("17", this); B17->setCheckable(true); B17->setGeometry(610, 260, 50, 50);
    B18 = new QPushButton("18", this); B18->setCheckable(true); B18->setGeometry(670, 260, 50, 50);
    B19 = new QPushButton("19", this); B19->setCheckable(true); B19->setGeometry(730, 260, 50, 50);
    B20 = new QPushButton("20", this); B20->setCheckable(true); B20->setGeometry(790, 260, 50, 50);

    //третий ряд
    B21 = new QPushButton("21", this); B21->setCheckable(true); B21->setGeometry(250, 320, 50, 50);
    B22 = new QPushButton("22", this); B22->setCheckable(true); B22->setGeometry(310, 320, 50, 50);
    B23 = new QPushButton("23", this); B23->setCheckable(true); B23->setGeometry(370, 320, 50, 50);
    B24 = new QPushButton("24", this); B24->setCheckable(true); B24->setGeometry(430, 320, 50, 50);
    B25 = new QPushButton("25", this); B25->setCheckable(true); B25->setGeometry(490, 320, 50, 50);
    B26 = new QPushButton("26", this); B26->setCheckable(true); B26->setGeometry(550, 320, 50, 50);
    B27 = new QPushButton("27", this); B27->setCheckable(true); B27->setGeometry(610, 320, 50, 50);
    B28 = new QPushButton("28", this); B28->setCheckable(true); B28->setGeometry(670, 320, 50, 50);
    B29 = new QPushButton("29", this); B29->setCheckable(true); B29->setGeometry(730, 320, 50, 50);
    B30 = new QPushButton("30", this); B30->setCheckable(true); B30->setGeometry(790, 320, 50, 50);
    //четвертый ряд
    B31 = new QPushButton("31", this); B31->setCheckable(true); B31->setGeometry(250, 380, 50, 50);
    B32 = new QPushButton("32", this); B32->setCheckable(true); B32->setGeometry(310, 380, 50, 50);
    B33 = new QPushButton("33", this); B33->setCheckable(true); B33->setGeometry(370, 380, 50, 50);
    B34 = new QPushButton("34", this); B34->setCheckable(true); B34->setGeometry(430, 380, 50, 50);
    B35 = new QPushButton("35", this); B35->setCheckable(true); B35->setGeometry(490, 380, 50, 50);
    B36 = new QPushButton("36", this); B36->setCheckable(true); B36->setGeometry(550, 380, 50, 50);
    B37 = new QPushButton("37", this); B37->setCheckable(true); B37->setGeometry(610, 380, 50, 50);
    B38 = new QPushButton("38", this); B38->setCheckable(true); B38->setGeometry(670, 380, 50, 50);
    B39 = new QPushButton("39", this); B39->setCheckable(true); B39->setGeometry(730, 380, 50, 50);
    B40 = new QPushButton("40", this); B40->setCheckable(true); B40->setGeometry(790, 380, 50, 50);

    connect(B1, &QPushButton::clicked, this, [=](){ui->txt_places->insert("1 "); B1->setEnabled(false);});   connect(B2, &QPushButton::clicked, this, [=](){ui->txt_places->insert("2 "); B2->setEnabled(false);});
    connect(B3, &QPushButton::clicked, this, [=](){ui->txt_places->insert("3 "); B3->setEnabled(false);});   connect(B4, &QPushButton::clicked, this, [=](){ui->txt_places->insert("4 "); B4->setEnabled(false);});
    connect(B5, &QPushButton::clicked, this, [=](){ui->txt_places->insert("5 "); B5->setEnabled(false);});   connect(B6, &QPushButton::clicked, this, [=](){ui->txt_places->insert("6 "); B6->setEnabled(false);});
    connect(B7, &QPushButton::clicked, this, [=](){ui->txt_places->insert("7 "); B7->setEnabled(false);});   connect(B8, &QPushButton::clicked, this, [=](){ui->txt_places->insert("8 "); B8->setEnabled(false);});
    connect(B9, &QPushButton::clicked, this, [=](){ui->txt_places->insert("9 "); B9->setEnabled(false);});   connect(B10, &QPushButton::clicked, this, [=](){ui->txt_places->insert("10 "); B10->setEnabled(false);});
    connect(B11, &QPushButton::clicked, this, [=](){ui->txt_places->insert("11 "); B11->setEnabled(false);}); connect(B12, &QPushButton::clicked, this, [=](){ui->txt_places->insert("12 "); B12->setEnabled(false);});
    connect(B13, &QPushButton::clicked, this, [=](){ui->txt_places->insert("13 "); B13->setEnabled(false);}); connect(B14, &QPushButton::clicked, this, [=](){ui->txt_places->insert("14 "); B14->setEnabled(false);});
    connect(B15, &QPushButton::clicked, this, [=](){ui->txt_places->insert("15 "); B15->setEnabled(false);}); connect(B16, &QPushButton::clicked, this, [=](){ui->txt_places->insert("16 "); B16->setEnabled(false);});
    connect(B17, &QPushButton::clicked, this, [=](){ui->txt_places->insert("17 "); B17->setEnabled(false);}); connect(B18, &QPushButton::clicked, this, [=](){ui->txt_places->insert("18 "); B18->setEnabled(false);});
    connect(B19, &QPushButton::clicked, this, [=](){ui->txt_places->insert("19 "); B19->setEnabled(false);}); connect(B20, &QPushButton::clicked, this, [=](){ui->txt_places->insert("20 "); B20->setEnabled(false);});
    connect(B21, &QPushButton::clicked, this, [=](){ui->txt_places->insert("21 "); B21->setEnabled(false);}); connect(B22, &QPushButton::clicked, this, [=](){ui->txt_places->insert("22 "); B22->setEnabled(false);});
    connect(B23, &QPushButton::clicked, this, [=](){ui->txt_places->insert("23 "); B23->setEnabled(false);}); connect(B24, &QPushButton::clicked, this, [=](){ui->txt_places->insert("24 "); B24->setEnabled(false);});
    connect(B25, &QPushButton::clicked, this, [=](){ui->txt_places->insert("25 "); B25->setEnabled(false);}); connect(B26, &QPushButton::clicked, this, [=](){ui->txt_places->insert("26 "); B26->setEnabled(false);});
    connect(B27, &QPushButton::clicked, this, [=](){ui->txt_places->insert("27 "); B27->setEnabled(false);}); connect(B28, &QPushButton::clicked, this, [=](){ui->txt_places->insert("28 "); B28->setEnabled(false);});
    connect(B29, &QPushButton::clicked, this, [=](){ui->txt_places->insert("29 "); B29->setEnabled(false);}); connect(B30, &QPushButton::clicked, this, [=](){ui->txt_places->insert("30 "); B30->setEnabled(false);});
    connect(B31, &QPushButton::clicked, this, [=](){ui->txt_places->insert("31 "); B31->setEnabled(false);}); connect(B32, &QPushButton::clicked, this, [=](){ui->txt_places->insert("32 "); B32->setEnabled(false);});
    connect(B33, &QPushButton::clicked, this, [=](){ui->txt_places->insert("33 "); B33->setEnabled(false);}); connect(B34, &QPushButton::clicked, this, [=](){ui->txt_places->insert("34 "); B34->setEnabled(false);});
    connect(B35, &QPushButton::clicked, this, [=](){ui->txt_places->insert("35 "); B35->setEnabled(false);}); connect(B36, &QPushButton::clicked, this, [=](){ui->txt_places->insert("36 "); B36->setEnabled(false);});
    connect(B37, &QPushButton::clicked, this, [=](){ui->txt_places->insert("37 "); B37->setEnabled(false);}); connect(B38, &QPushButton::clicked, this, [=](){ui->txt_places->insert("38 "); B38->setEnabled(false);});
    connect(B39, &QPushButton::clicked, this, [=](){ui->txt_places->insert("39 "); B39->setEnabled(false);}); connect(B40, &QPushButton::clicked, this, [=](){ui->txt_places->insert("40 "); B40->setEnabled(false);});

    //список фильмов
    ui->comboBox_Film->clear(); ui->comboBox_Film->insertItem(0, "");
    ui->comboBox_Film->insertItem(1, "Вам и не снилось...");
    ui->comboBox_Film->insertItem(2, "Служебный роман");
    ui->comboBox_Film->insertItem(3, "Девчата");
    ui->comboBox_Film->insertItem(4, "Иван Васильевич меняет профессию");
    ui->comboBox_Film->insertItem(5, "Москва слезам не верит");
    ui->comboBox_Film->insertItem(6, "Морозко");
    //ui->comboBox_Film->insertItem(7, "Карнавальная ночь");
    //ui->comboBox_Film->insertItem(8, "Бриллиантовая рука");
    //ui->comboBox_Film->insertItem(9, "12 стульев");
    //ui->comboBox_Film->insertItem(10, "Джентельмены удачи");

    //список дат
    ui->comboBox_Date->clear(); ui->comboBox_Date->insertItem(0, "");
    ui->comboBox_Date->insertItem(1, "21 декабря");   ui->comboBox_Date->insertItem(2, "22 декабря");   ui->comboBox_Date->insertItem(3, "23 декабря");
    ui->comboBox_Date->insertItem(4, "24 декабря");   ui->comboBox_Date->insertItem(5, "25 декабря");   ui->comboBox_Date->insertItem(6, "26 декабря");
    ui->comboBox_Date->insertItem(7, "27 декабря");   ui->comboBox_Date->insertItem(8, "28 декабря");   ui->comboBox_Date->insertItem(9, "29 декабря");
    ui->comboBox_Date->insertItem(10, "30 декабря");

    connect(ui->comboBox_Date, SIGNAL(currentIndexChanged(QString)), SLOT(showPosts()));
}

void Tickets::showPosts() {
//расписание Вам и не снилось...
    if(ui->comboBox_Film->currentText() == "Вам и не снилось..." and ui->comboBox_Date->currentText() == "21 декабря"){
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(0,"11:30");
        ui->comboBox_Time->insertItem(1,"14:10");
        ui->comboBox_Time->insertItem(2,"18:00");
    }
    else if(ui->comboBox_Film->currentText() == "Вам и не снилось..." and ui->comboBox_Date->currentText() == "22 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(67, "");
    }
    else if(ui->comboBox_Film->currentText() == "Вам и не снилось..." and ui->comboBox_Date->currentText() == "23 декабря"){
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(3,"17:50");
        ui->comboBox_Time->insertItem(4,"22:00");
    }
    else if(ui->comboBox_Film->currentText() == "Вам и не снилось..." and ui->comboBox_Date->currentText() == "24 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(68, "");
    }
    else if(ui->comboBox_Film->currentText() == "Вам и не снилось..." and ui->comboBox_Date->currentText() == "25 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(69, "");
    }
    else if(ui->comboBox_Film->currentText() == "Вам и не снилось..." and ui->comboBox_Date->currentText() == "26 декабря"){
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(5,"21:00");
    }
    else if(ui->comboBox_Film->currentText() == "Вам и не снилось..." and ui->comboBox_Date->currentText() == "27 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(70, "");
    }
    else if(ui->comboBox_Film->currentText() == "Вам и не снилось..." and ui->comboBox_Date->currentText() == "28 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(71, "");
    }
    else if(ui->comboBox_Film->currentText() == "Вам и не снилось..." and ui->comboBox_Date->currentText() == "29 декабря"){
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(6,"15:35");
    }
    else if(ui->comboBox_Film->currentText() == "Вам и не снилось..." and ui->comboBox_Date->currentText() == "30 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(72, "");
    }
//расписание Служебный роман
    else if(ui->comboBox_Film->currentText() == "Служебный роман" and ui->comboBox_Date->currentText() == "21 декабря") {
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(7,"10:00");
        ui->comboBox_Time->insertItem(8,"15:20");
    }
    else if(ui->comboBox_Film->currentText() == "Служебный роман" and ui->comboBox_Date->currentText() == "22 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(73, "");
    }
    else if(ui->comboBox_Film->currentText() == "Служебный роман" and ui->comboBox_Date->currentText() == "23 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(74, "");
    }
    else if(ui->comboBox_Film->currentText() == "Служебный роман" and ui->comboBox_Date->currentText() == "24 декабря"){
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(9,"10:00");
        ui->comboBox_Time->insertItem(10,"16:00");
    }
    else if(ui->comboBox_Film->currentText() == "Служебный роман" and ui->comboBox_Date->currentText() == "25 декабря"){
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(11,"11:00");
        ui->comboBox_Time->insertItem(12,"17:30");
    }
    else if(ui->comboBox_Film->currentText() == "Служебный роман" and ui->comboBox_Date->currentText() == "26 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(75, "");
    }
    else if(ui->comboBox_Film->currentText() == "Служебный роман" and ui->comboBox_Date->currentText() == "27 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(76, "");
    }
    else if(ui->comboBox_Film->currentText() == "Служебный роман" and ui->comboBox_Date->currentText() == "28 декабря"){
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(13,"9:30");
    }
    else if(ui->comboBox_Film->currentText() == "Служебный роман" and ui->comboBox_Date->currentText() == "29 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(77, "");
    }
    else if(ui->comboBox_Film->currentText() == "Служебный роман" and ui->comboBox_Date->currentText() == "30 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(78, "");
    }
//расписание Девчата
    else if(ui->comboBox_Film->currentText() == "Девчата" and ui->comboBox_Date->currentText() == "21 декабря"){
        ui->comboBox_Time->clear();
    }
    else if(ui->comboBox_Film->currentText() == "Девчата" and ui->comboBox_Date->currentText() == "22 декабря") {
         ui->comboBox_Time->clear();
         ui->comboBox_Time->insertItem(14,"10:00");
         ui->comboBox_Time->insertItem(15,"12:00");
         ui->comboBox_Time->insertItem(16,"14:00");
         ui->comboBox_Time->insertItem(17,"16:00");
         ui->comboBox_Time->insertItem(18,"18:00");
         ui->comboBox_Time->insertItem(19,"20:00");
         ui->comboBox_Time->insertItem(20,"22:00");
    }
    else if(ui->comboBox_Film->currentText() == "Девчата" and ui->comboBox_Date->currentText() == "23 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(79, "");
    }
    else if(ui->comboBox_Film->currentText() == "Девчата" and ui->comboBox_Date->currentText() == "24 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(80, "");
    }
    else if(ui->comboBox_Film->currentText() == "Девчата" and ui->comboBox_Date->currentText() == "25 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(81, "");
    }
    else if(ui->comboBox_Film->currentText() == "Девчата" and ui->comboBox_Date->currentText() == "26 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(82, "");
    }
    else if(ui->comboBox_Film->currentText() == "Девчата" and ui->comboBox_Date->currentText() == "27 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(83, "");
    }
    else if(ui->comboBox_Film->currentText() == "Девчата" and ui->comboBox_Date->currentText() == "28 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(84, "");
    }
    else if(ui->comboBox_Film->currentText() == "Девчата" and ui->comboBox_Date->currentText() == "29 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(85, "");
    }
    else if(ui->comboBox_Film->currentText() == "Девчата" and ui->comboBox_Date->currentText() == "30 декабря"){
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(21,"10:00");
        ui->comboBox_Time->insertItem(22,"12:00");
        ui->comboBox_Time->insertItem(23,"14:00");
        ui->comboBox_Time->insertItem(24,"16:00");
        ui->comboBox_Time->insertItem(25,"18:00");
        ui->comboBox_Time->insertItem(26,"20:00");
        ui->comboBox_Time->insertItem(27,"22:00");
    }
//расписание Иван Васильевич меняет профессию
    else if(ui->comboBox_Film->currentText() == "Иван Васильевич меняет профессию" and ui->comboBox_Date->currentText() == "21 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(86, "");
    }
    else if(ui->comboBox_Film->currentText() == "Иван Васильевич меняет профессию" and ui->comboBox_Date->currentText() == "22 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(87, "");
    }
    else if(ui->comboBox_Film->currentText() == "Иван Васильевич меняет профессию" and ui->comboBox_Date->currentText() == "23 декабря") {
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(28,"10:00");
        ui->comboBox_Time->insertItem(29,"14:00");
        ui->comboBox_Time->insertItem(30,"17:30");
    }
    else if(ui->comboBox_Film->currentText() == "Иван Васильевич меняет профессию" and ui->comboBox_Date->currentText() == "24 декабря"){
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(31,"19:00");
    }
    else if(ui->comboBox_Film->currentText() == "Иван Васильевич меняет профессию" and ui->comboBox_Date->currentText() == "25 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(88, "");
    }
    else if(ui->comboBox_Film->currentText() == "Иван Васильевич меняет профессию" and ui->comboBox_Date->currentText() == "26 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(89, "");
    }
    else if(ui->comboBox_Film->currentText() == "Иван Васильевич меняет профессию" and ui->comboBox_Date->currentText() == "27 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(90, "");
    }
    else if(ui->comboBox_Film->currentText() == "Иван Васильевич меняет профессию" and ui->comboBox_Date->currentText() == "28 декабря"){
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(32,"10:00");
        ui->comboBox_Time->insertItem(33,"12:00");
        ui->comboBox_Time->insertItem(34,"14:00");
        ui->comboBox_Time->insertItem(35,"16:00");
        ui->comboBox_Time->insertItem(36,"18:00");
        ui->comboBox_Time->insertItem(37,"20:00");
        ui->comboBox_Time->insertItem(38,"22:00");
    }
    else if(ui->comboBox_Film->currentText() == "Иван Васильевич меняет профессию" and ui->comboBox_Date->currentText() == "29 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(91, "");
    }
    else if(ui->comboBox_Film->currentText() == "Иван Васильевич меняет профессию" and ui->comboBox_Date->currentText() == "30 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(92, "");
    }
//расписание Москва слезам не верит
    else if(ui->comboBox_Film->currentText() == "Москва слезам не верит" and ui->comboBox_Date->currentText() == "21 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(93, "");
    }
    else if(ui->comboBox_Film->currentText() == "Москва слезам не верит" and ui->comboBox_Date->currentText() == "22 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(94, "");
    }
    else if(ui->comboBox_Film->currentText() == "Москва слезам не верит" and ui->comboBox_Date->currentText() == "23 декабря") {
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(39,"21:00");
    }
    else if(ui->comboBox_Film->currentText() == "Москва слезам не верит" and ui->comboBox_Date->currentText() == "24 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(95, "");
    }
    else if(ui->comboBox_Film->currentText() == "Москва слезам не верит" and ui->comboBox_Date->currentText() == "25 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(96, "");
    }
    else if(ui->comboBox_Film->currentText() == "Москва слезам не верит" and ui->comboBox_Date->currentText() == "26 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(97, "");
    }
    else if(ui->comboBox_Film->currentText() == "Москва слезам не верит" and ui->comboBox_Date->currentText() == "27 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(98, "");
    }
    else if(ui->comboBox_Film->currentText() == "Москва слезам не верит" and ui->comboBox_Date->currentText() == "28 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(99, "");
    }
    else if(ui->comboBox_Film->currentText() == "Москва слезам не верит" and ui->comboBox_Date->currentText() == "29 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(100, "");
    }
    else if(ui->comboBox_Film->currentText() == "Москва слезам не верит" and ui->comboBox_Date->currentText() == "30 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(101, "");
    }
//расписание Морозко
    else if(ui->comboBox_Film->currentText() == "Морозко" and ui->comboBox_Date->currentText() == "21 декабря") {
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(40,"21:00");
    }
    else if(ui->comboBox_Film->currentText() == "Морозко" and ui->comboBox_Date->currentText() == "22 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(102, "");
    }
    else if(ui->comboBox_Film->currentText() == "Морозко" and ui->comboBox_Date->currentText() == "23 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(103, "");
    }
    else if(ui->comboBox_Film->currentText() == "Морозко" and ui->comboBox_Date->currentText() == "24 декабря") {
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(41,"10:00");
    }
    else if(ui->comboBox_Film->currentText() == "Морозко" and ui->comboBox_Date->currentText() == "25 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(104, "");
    }
    else if(ui->comboBox_Film->currentText() == "Морозко" and ui->comboBox_Date->currentText() == "26 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(105, "");
    }
    else if(ui->comboBox_Film->currentText() == "Морозко" and ui->comboBox_Date->currentText() == "27 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(106, "");
    }
    else if(ui->comboBox_Film->currentText() == "Морозко" and ui->comboBox_Date->currentText() == "28 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(107, "");
    }
    else if(ui->comboBox_Film->currentText() == "Морозко" and ui->comboBox_Date->currentText() == "29 декабря") {
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(42,"19:00");
    }
    else if(ui->comboBox_Film->currentText() == "Морозко" and ui->comboBox_Date->currentText() == "30 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(108, "");
    }
//расписание Карнавальная ночь
    else if(ui->comboBox_Film->currentText() == "Карнавальная ночь" and ui->comboBox_Date->currentText() == "21 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(109, "");
    }
    else if(ui->comboBox_Film->currentText() == "Карнавальная ночь" and ui->comboBox_Date->currentText() == "22 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(110, "");
    }
    else if(ui->comboBox_Film->currentText() == "Карнавальная ночь" and ui->comboBox_Date->currentText() == "23 декабря") {
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(43,"13:30");
        ui->comboBox_Time->insertItem(44,"21:00");
    }
    else if(ui->comboBox_Film->currentText() == "Карнавальная ночь" and ui->comboBox_Date->currentText() == "24 декабря"){
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(45,"19:00");
    }
    else if(ui->comboBox_Film->currentText() == "Карнавальная ночь" and ui->comboBox_Date->currentText() == "25 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(111, "");
    }
    else if(ui->comboBox_Film->currentText() == "Карнавальная ночь" and ui->comboBox_Date->currentText() == "26 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(112, "");
    }
    else if(ui->comboBox_Film->currentText() == "Карнавальная ночь" and ui->comboBox_Date->currentText() == "27 декабря"){
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(46,"10:00");
        ui->comboBox_Time->insertItem(47,"12:00");
        ui->comboBox_Time->insertItem(48,"14:00");
        ui->comboBox_Time->insertItem(49,"16:00");
        ui->comboBox_Time->insertItem(50,"18:00");
        ui->comboBox_Time->insertItem(51,"20:00");
        ui->comboBox_Time->insertItem(52,"22:00");
    }
    else if(ui->comboBox_Film->currentText() == "Карнавальная ночь" and ui->comboBox_Date->currentText() == "28 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(113, "");
    }
    else if(ui->comboBox_Film->currentText() == "Карнавальная ночь" and ui->comboBox_Date->currentText() == "29 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(114, "");
    }
    else if(ui->comboBox_Film->currentText() == "Карнавальная ночь" and ui->comboBox_Date->currentText() == "30 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(115, "");
    }

//расписание Бриллиантовая рука
    else if(ui->comboBox_Film->currentText() == "Бриллиантовая рука" and ui->comboBox_Date->currentText() == "21 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(116, "");
    }
    else if(ui->comboBox_Film->currentText() == "Бриллиантовая рука" and ui->comboBox_Date->currentText() == "22 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(117, "");
    }
    else if(ui->comboBox_Film->currentText() == "Бриллиантовая рука" and ui->comboBox_Date->currentText() == "23 декабря") {
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(53,"23:00");
    }
    else if(ui->comboBox_Film->currentText() == "Бриллиантовая рука" and ui->comboBox_Date->currentText() == "24 декабря"){
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(54,"22:00");
    }
    else if(ui->comboBox_Film->currentText() == "Бриллиантовая рука" and ui->comboBox_Date->currentText() == "25 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(118, "");
    }
    else if(ui->comboBox_Film->currentText() == "Бриллиантовая рука" and ui->comboBox_Date->currentText() == "26 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(119, "");
    }
    else if(ui->comboBox_Film->currentText() == "Бриллиантовая рука" and ui->comboBox_Date->currentText() == "27 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(120, "");
    }
    else if(ui->comboBox_Film->currentText() == "Интерстеллар" and ui->comboBox_Date->currentText() == "28 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(121, "");
    }
    else if(ui->comboBox_Film->currentText() == "Бриллиантовая рука" and ui->comboBox_Date->currentText() == "29 декабря"){
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(55,"10:00");
        ui->comboBox_Time->insertItem(56,"12:00");
        ui->comboBox_Time->insertItem(57,"14:00");
        ui->comboBox_Time->insertItem(58,"16:00");
        ui->comboBox_Time->insertItem(59,"18:00");
        ui->comboBox_Time->insertItem(60,"20:00");
        ui->comboBox_Time->insertItem(61,"22:00");
    }
    else if(ui->comboBox_Film->currentText() == "Бриллиантовая рука" and ui->comboBox_Date->currentText() == "30 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(122, "");
    }
//расписание 12 стульев
    else if(ui->comboBox_Film->currentText() == "12 стульев" and ui->comboBox_Date->currentText() == "21 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(123, "");
    }
    else if(ui->comboBox_Film->currentText() == "12 стульев" and ui->comboBox_Date->currentText() == "22 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(124, "");
    }
    else if(ui->comboBox_Film->currentText() == "12 стульев" and ui->comboBox_Date->currentText() == "23 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(125, "");
    }
    else if(ui->comboBox_Film->currentText() == "12 стульев" and ui->comboBox_Date->currentText() == "24 декабря"){
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(62,"21:00");
        ui->comboBox_Time->insertItem(63,"23:00");
    }
    else if(ui->comboBox_Film->currentText() == "12 стульев" and ui->comboBox_Date->currentText() == "25 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(126, "");
    }
    else if(ui->comboBox_Film->currentText() == "12 стульев" and ui->comboBox_Date->currentText() == "26 декабря"){
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(64,"21:00");
    }
    else if(ui->comboBox_Film->currentText() == "12 стульев" and ui->comboBox_Date->currentText() == "27 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(127, "");
    }
    else if(ui->comboBox_Film->currentText() == "12 стульев" and ui->comboBox_Date->currentText() == "28 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(128, "");
    }
    else if(ui->comboBox_Film->currentText() == "12 стульев" and ui->comboBox_Date->currentText() == "29 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(129, "");
    }
    else if(ui->comboBox_Film->currentText() == "12 стульев" and ui->comboBox_Date->currentText() == "30 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(130, "");
    }
//расписание Джентельмены удачи
    else if(ui->comboBox_Film->currentText() == "Джентельмены удачи" and ui->comboBox_Date->currentText() == "21 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(131, "");
    }
    else if(ui->comboBox_Film->currentText() == "Джентельмены удачи" and ui->comboBox_Date->currentText() == "22 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(132, "");
    }
    else if(ui->comboBox_Film->currentText() == "Джентельмены удачи" and ui->comboBox_Date->currentText() == "23 декабря") {
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(65,"16:00");
    }
    else if(ui->comboBox_Film->currentText() == "Джентельмены удачи" and ui->comboBox_Date->currentText() == "24 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(133, "");
    }
    else if(ui->comboBox_Film->currentText() == "Джентельмены удачи" and ui->comboBox_Date->currentText() == "25 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(134, "");
    }
    else if(ui->comboBox_Film->currentText() == "Джентельмены удачи" and ui->comboBox_Date->currentText() == "26 декабря"){
        ui->comboBox_Time->clear();
        ui->comboBox_Time->insertItem(66,"16:00");
    }
    else if(ui->comboBox_Film->currentText() == "Джентельмены удачи" and ui->comboBox_Date->currentText() == "27 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(135, "");
    }
    else if(ui->comboBox_Film->currentText() == "Джентельмены удачи" and ui->comboBox_Date->currentText() == "28 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(136, "");
    }
    else if(ui->comboBox_Film->currentText() == "Джентельмены удачи" and ui->comboBox_Date->currentText() == "29 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(137, "");
    }
    else if(ui->comboBox_Film->currentText() == "Джентельмены удачи" and ui->comboBox_Date->currentText() == "30 декабря"){
        ui->comboBox_Time->clear(); ui->comboBox_Time->insertItem(138, "");
    }
}

Tickets::~Tickets()
{
    delete ui;
}

void Tickets::on_pushButton_clicked()
{
    this->close();      // Закрываем окно
    emit firstWindow(); // И вызываем сигнал на открытие главного окна
}

void Tickets::on_pushButton_2_clicked()
{
    Tickets conn;
    QString Surname, Film, Places, Date_of_session, Time_of_session;
    Surname=ui->txt_surname->text();
    Film=ui->comboBox_Film->currentText();
    Date_of_session=ui->comboBox_Date->currentText();
    Time_of_session=ui->comboBox_Time->currentText();
    Places=ui->txt_places->text();
    if(!conn.connOpen()){
        qDebug()<<"Failed to open the database";
        return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into booking (Surname, Film, Places, Date_of_session, Time_of_session) values ('"+Surname+"', '"+Film+"', '"+Places+"', '"+Date_of_session+"', '"+Time_of_session+"')");

    if(qry.exec())
    {
        QMessageBox::information(this,tr("Успешно!"), tr("Места забронированы!"));
        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("Ошибка!"), tr("Фамилия не указана или уже использовалась при бронировании!"));
    }
}


void Tickets::on_pushButton_3_clicked()
{
    ui->txt_surname->clear();
    ui->comboBox_Film->setCurrentIndex(-1);
    ui->comboBox_Date->setCurrentIndex(-1);
    ui->comboBox_Time->setCurrentIndex(-1);
    ui->txt_places->clear();

    //Установка кнопок в состояние невыбранной
    B1->setChecked(false); B2->setChecked(false); B3->setChecked(false); B4->setChecked(false); B5->setChecked(false); B6->setChecked(false); B7->setChecked(false); B8->setChecked(false); B9->setChecked(false); B10->setChecked(false);
    B11->setChecked(false); B12->setChecked(false); B13->setChecked(false); B14->setChecked(false); B15->setChecked(false); B16->setChecked(false); B17->setChecked(false); B18->setChecked(false); B19->setChecked(false); B20->setChecked(false);
    B21->setChecked(false); B22->setChecked(false); B23->setChecked(false); B24->setChecked(false); B25->setChecked(false); B26->setChecked(false); B27->setChecked(false); B28->setChecked(false); B29->setChecked(false); B30->setChecked(false);
    B31->setChecked(false); B32->setChecked(false); B33->setChecked(false); B34->setChecked(false); B35->setChecked(false); B36->setChecked(false); B37->setChecked(false); B38->setChecked(false); B39->setChecked(false); B40->setChecked(false);

    //Установка кнопок опять в состояние доступной
    B1->setEnabled(true); B2->setEnabled(true); B3->setEnabled(true); B4->setEnabled(true); B5->setEnabled(true); B6->setEnabled(true); B7->setEnabled(true); B8->setEnabled(true); B9->setEnabled(true); B10->setEnabled(true);
    B11->setEnabled(true); B12->setEnabled(true); B13->setEnabled(true); B14->setEnabled(true); B15->setEnabled(true); B16->setEnabled(true); B17->setEnabled(true); B18->setEnabled(true); B19->setEnabled(true); B20->setEnabled(true);
    B21->setEnabled(true); B22->setEnabled(true); B23->setEnabled(true); B24->setEnabled(true); B25->setEnabled(true); B26->setEnabled(true); B27->setEnabled(true); B28->setEnabled(true); B29->setEnabled(true); B30->setEnabled(true);
    B31->setEnabled(true); B32->setEnabled(true); B33->setEnabled(true); B34->setEnabled(true); B35->setEnabled(true); B36->setEnabled(true); B37->setEnabled(true); B38->setEnabled(true); B39->setEnabled(true); B40->setEnabled(true);
}
