#include "reservasion_edit.h"
#include "ui_reservasion_edit.h"

reservasion_edit::reservasion_edit(QString logid, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reservasion_edit)
{
    ui->setupUi(this);
    log_id=logid;

    reserList();
    //carList();
}

reservasion_edit::~reservasion_edit()
{
    delete ui;
}

void reservasion_edit::reserList() //  예약확인2
{
    query="SELECT * FROM reservation where id='" + log_id.toStdString() + "'";

    qDebug() << QString::fromStdString(query); //내용확인

    sql.exec(QString::fromStdString(query));
    sql.first();
    ui-> reser_num-> setText(sql.value(0).toString());
    ui-> reser_ID-> setText(sql.value(1).toString());
    ui-> car_name-> setText(sql.value(2).toString());
    ui-> car_type-> setText(sql.value(3).toString());
    ui-> car_fuel-> setText(sql.value(4).toString());
    ui-> car_pay -> setText(sql.value(5).toString());
    ui-> car_total-> setText(sql.value(6).toString());
    QString rser_date= sql.value(7).toString()+".0";
    QString rturn_date= sql.value(8).toString()+".0";
    QString form = "yyyy-MM-dd HH:mm:ss.z";
    QDateTime dt = QDateTime::fromString(rser_date, form);
    QDateTime dt2 = QDateTime::fromString(rturn_date, form);
    ui ->reser_date ->setDateTime(dt);
    ui ->return_date ->setDateTime(dt2);

    reserv_car = sql.value(2).toString();
    carList();
}

void reservasion_edit::carList() //차량 내역
{
    ui->car_list->clear();
    query="SELECT num, carname, type, fuel, charge FROM rentacar";

    sql.exec(QString::fromStdString(query));
    record = sql.record();

    ui->car_list->setRowCount(sql.size());
    ui->car_list->setHorizontalHeaderItem(0, new QTableWidgetItem("번호"));
    ui->car_list->setHorizontalHeaderItem(1, new QTableWidgetItem("차명"));
    ui->car_list->setHorizontalHeaderItem(2, new QTableWidgetItem("차종"));
    ui->car_list->setHorizontalHeaderItem(3, new QTableWidgetItem("연료"));
    ui->car_list->setHorizontalHeaderItem(4, new QTableWidgetItem("요금"));

       int i=0;
       while(sql.next())
       {
           ui->car_list->setItem(i,0,new QTableWidgetItem(sql.value("num").toString()));
           ui->car_list->setItem(i,1,new QTableWidgetItem(sql.value("carname").toString()));
           ui->car_list->setItem(i,2,new QTableWidgetItem(sql.value("type").toString()));
           ui->car_list->setItem(i,3,new QTableWidgetItem(sql.value("fuel").toString()));
           ui->car_list->setItem(i++,4,new QTableWidgetItem(sql.value("charge").toString()));
       }
}

void reservasion_edit::on_reser_clicked() //예약버튼
{
    sql.prepare("UPDATE reservation SET car_model = ?, car_type = ?, fuel = ?, charge = ?, total = ?, reserv_date = ?, return_date = ? WHERE num = ?");
    sql.addBindValue(ui->car_name->text());
    sql.addBindValue(ui->car_type->text());
    sql.addBindValue(ui->car_fuel->text());
    sql.addBindValue(ui->car_pay->text());
    sql.addBindValue(ui->car_total->text());
    sql.addBindValue(ui->reser_date->dateTime());
    sql.addBindValue(ui->return_date->dateTime());
    sql.addBindValue(ui->reser_num->text());
    sql.exec();

    query = "SELECT num, booking FROM rentacar WHERE carname ='" + ui->car_name->text().toStdString() + "'";
    sql.exec(QString::fromStdString(query));
    record = sql.record();

    int booking = record.indexOf("booking");
    int carnum = record.indexOf("num");
    sql.next();
    int num = sql.value(booking).toInt();
    QString car = sql.value(carnum).toString();
    num++;
    QString number = QString::number(num);
    query = "UPDATE rentacar SET booking = '"
            + number.toStdString() + "' WHERE num = '" + car.toStdString() +"'";
    sql.exec(QString::fromStdString(query));


    query = "SELECT num, booking FROM rentacar WHERE carname = '" + reserv_car.toStdString() +"'";
    sql.exec(QString::fromStdString(query));
    record = sql.record();
    int reserv_book = record.indexOf("booking");
    int reserv_carnum = record.indexOf("num");
    sql.next();
    int reserv_num = sql.value(reserv_book).toInt();
    QString reserv_car = sql.value(reserv_carnum).toString();
    reserv_num--;
    QString reserv_number = QString::number(reserv_num);
    query = "UPDATE rentacar SET booking = '"
            + reserv_number.toStdString() + "' WHERE num = '" + reserv_car.toStdString() +"'";
    sql.exec(QString::fromStdString(query));

    QMessageBox::information(this, "", "수정완료");
    this->close();
}

void reservasion_edit::on_back_clicked() //뒤로
{    this ->close();}

void reservasion_edit::on_car_list_cellDoubleClicked()
{
    int select_row = ui -> car_list->currentRow();
    ui ->car_name->setText(ui->car_list->takeItem(select_row, 1)->text());
    ui ->car_type->setText(ui->car_list->takeItem(select_row, 2)->text());
    ui ->car_fuel->setText(ui->car_list->takeItem(select_row, 3)->text());
    ui ->car_pay->setText(ui->car_list->takeItem(select_row, 4)->text());
    int fee = ui -> car_pay -> text().toInt();
    int days =ui->reser_date->dateTime().daysTo(ui->reser_date->dateTime());
    int charge = fee * (days+1);
    ui ->car_total ->setText(QString::number(charge));
    carList();
}

void reservasion_edit::on_reser_date_dateChanged()
{
    int fee = ui->car_pay->text().toInt();
    int days = ui->reser_date->dateTime().daysTo(ui->return_date->dateTime());
    int charge = fee * (days+1);
    ui->car_total->setText(QString::number(charge));
}

void reservasion_edit::on_return_date_dateChanged()
{
    int fee = ui->car_pay->text().toInt();
    int days = ui->reser_date->dateTime().daysTo(ui->return_date->dateTime());
    int charge = fee * (days+1);
    ui->car_total->setText(QString::number(charge));
}
