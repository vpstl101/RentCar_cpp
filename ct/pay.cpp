#include "pay.h"
#include "ui_pay.h"
#include <string>

using namespace std;

pay::pay(QString logID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pay)
{
    ui->setupUi(this);
    choose="money";
    logid=logID;
    point_use=0;
    point_search();
    pay_input();

}

pay::~pay()
{    delete ui;}

void pay::point_search()
{
    query="SELECT point FROM member where id='" + logid.toStdString() + "'";
    sql.exec(QString::fromStdString(query));
    sql.first();
    ui-> user_point-> setText(sql.value(0).toString());
    point_use =sql.value(0).toInt();
}

void pay::pay_input() //결제 란
{
    QString common= "common";
    QString premium= "premium";
    QString vip = "vip";

    query="SELECT total FROM reservation where id='" + logid.toStdString() + "'";
    sql.exec(QString::fromStdString(query));
    sql.first();
    ui-> total-> setText(sql.value(0).toString());

    int grade_total = sql.value(0).toInt();

    query="SELECT grade FROM member where id='" + logid.toStdString() + "'";
    sql.exec(QString::fromStdString(query));
    sql.first();

    if((sql.value(0).toString()) == premium)
    {
        int premium_sale = grade_total *(0.1);
        ui -> grade_total ->setText(QString::number(premium_sale));
        ui -> sale_total ->setText(QString::number(grade_total-(premium_sale+point_use)));
    }
    else if((sql.value(0).toString()) == vip)
    {
        int vip_sale = grade_total *(0.2);
        ui -> grade_total ->setText(QString::number(vip_sale));
        ui -> sale_total ->setText(QString::number(grade_total-(vip_sale+point_use)));
    }
}


void pay::on_back_clicked() //뒤로가기
{    this ->close();}

void pay::on_money_pay_clicked() //현금
{    choose="money";}

void pay::on_card_pay_clicked() //카드
{    choose="card";}
