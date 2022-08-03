#include "ui_menu.h"
#include "menu.h"
#include "chat.h"

using namespace  std;

menu::menu(QString logid, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    log_id = logid;
}

menu::~menu()
{    delete ui;}

void menu::on_my_info_clicked() //내정보 조회 버튼
{
    myinfo myinfo(log_id);
    myinfo.setModal(true);
    myinfo.exec();
}

void menu::on_trip_clicked() //여행정보 조회 버튼
{
    trip trevel;
    trevel.setModal(true);
    trevel.exec();
}

void menu::on_car_search_clicked() //렌터카 정보 조회
{
    carsearch car_search;
    car_search.setModal(true);
    car_search.exec();
    this ->show();
}

void menu::on_reservasion_clicked() //렌터카 예약 / 변경
{
    reservasion reser(log_id);
    reser.setModal(true);
    reser.exec();
    this ->show();
}

void menu::on_chating_clicked() //채팅
{
    chat chatting(log_id);
    chatting.setModal(true);
    chatting.exec();
    this ->show();
}

void menu::on_pay_2_clicked() //종료
{    this ->close();}

