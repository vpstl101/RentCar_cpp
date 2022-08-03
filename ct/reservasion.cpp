#include "reservasion.h"
#include "ui_reservasion.h"

reservasion::reservasion(QString logid, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reservasion)
{
    ui->setupUi(this);
    log_id = logid;
    reserlist();
}

reservasion::~reservasion()
{    delete ui;}

void reservasion::reserlist() //예약 화면
{
    ui->rent_info->clear();

    query="SELECT * FROM reservation where id='" + log_id.toStdString() + "'";

    qDebug() << QString::fromStdString(query);
    sql.exec(QString::fromStdString(query));
    record = sql.record();

    int num = record.indexOf("num");
    int id = record.indexOf("id");
    int car_model = record.indexOf("car_model");
    int car_type = record.indexOf("car_type");
    int fuel = record.indexOf("fuel");
    int charge = record.indexOf("charge");
    int total = record.indexOf("total");
    int reserv_date = record.indexOf("reserv_date");
    int return_date = record.indexOf("return_date");
    int pay = record.indexOf("pay");

    ui->rent_info->setRowCount(sql.size());
    ui->rent_info->setColumnCount(record.count()-1);
    ui->rent_info->setHorizontalHeaderItem(0, new QTableWidgetItem("예약번호"));
    ui->rent_info->setHorizontalHeaderItem(1, new QTableWidgetItem("ID"));
    ui->rent_info->setHorizontalHeaderItem(2, new QTableWidgetItem("차명"));
    ui->rent_info->setHorizontalHeaderItem(3, new QTableWidgetItem("차종"));
    ui->rent_info->setHorizontalHeaderItem(4, new QTableWidgetItem("연료"));
    ui->rent_info->setHorizontalHeaderItem(5, new QTableWidgetItem("일요금"));
    ui->rent_info->setHorizontalHeaderItem(6, new QTableWidgetItem("합산"));
    ui->rent_info->setHorizontalHeaderItem(7, new QTableWidgetItem("예약날짜"));
    ui->rent_info->setHorizontalHeaderItem(8, new QTableWidgetItem("반납날짜"));
    ui->rent_info->setHorizontalHeaderItem(9, new QTableWidgetItem("결제"));

    int i=0;
    while(sql.next())
    {
        ui->rent_info->setItem(i,0,new QTableWidgetItem(sql.value(num).toString()));
        ui->rent_info->setItem(i,1,new QTableWidgetItem(sql.value(id).toString()));
        ui->rent_info->setItem(i,2,new QTableWidgetItem(sql.value(car_model).toString()));
        ui->rent_info->setItem(i,3,new QTableWidgetItem(sql.value(car_type).toString()));
        ui->rent_info->setItem(i,4,new QTableWidgetItem(sql.value(fuel).toString()));
        ui->rent_info->setItem(i,5,new QTableWidgetItem(sql.value(charge).toString()));
        ui->rent_info->setItem(i,6,new QTableWidgetItem(sql.value(total).toString()));
        ui->rent_info->setItem(i,7,new QTableWidgetItem(sql.value(reserv_date).toString()));
        ui->rent_info->setItem(i,8,new QTableWidgetItem(sql.value(return_date).toString()));
        ui->rent_info->setItem(i++,9,new QTableWidgetItem(sql.value(pay).toString()));

    }
}

void reservasion::on_reser_clicked() //예약 버튼
{
    reservasion_edit rser_edit(log_id);
    rser_edit.setModal(true);
    rser_edit.exec();
    reserlist();
}


void reservasion::on_del_clicked() //예약 삭제
{
    if(ui->rent_info->currentItem() == NULL)
          QMessageBox::information(this, "", "선택하세요");
    else
    {
        int row = ui->rent_info->currentRow();
        query = "DELETE FROM reservation WHERE num = '" + ui->rent_info->takeItem(row, 0)->text().toStdString() + "'";
        sql.exec(QString::fromStdString(query));

        query = "SELECT num, booking FROM rentacar WHERE carname = '" + ui->rent_info->takeItem(row, 2)->text().toStdString() +"'";
        sql.exec(QString::fromStdString(query));
        record = sql.record();

        int booking = record.indexOf("booking");
        int carnum = record.indexOf("num");
        sql.next();
        int num = sql.value(booking).toInt();

        QString car = sql.value(carnum).toString();
        num--;
        QString number = QString::number(num);

        query = "UPDATE rentacar SET booking = '"
                + number.toStdString() + "' WHERE num = '" + car.toStdString() +"'";

        sql.exec(QString::fromStdString(query));

        QMessageBox::information(this, "", "삭제완료");

    }
    reserlist();

}

void reservasion::on_pay_clicked() //결제 ->결제 창
{
    pay payment(log_id);
    payment.setModal(true);
    payment.exec();
}

void reservasion::on_back_clicked() //뒤로가기
{    this ->close();}

void reservasion::on_real_reser_clicked() //예약 추가
{
    reservasion_add add(log_id);
    add.setModal(true);
    add.exec();
    reserlist();
}
