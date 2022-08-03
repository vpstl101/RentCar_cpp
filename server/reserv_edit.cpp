#include "reserv_edit.h"
#include "ui_reserv_edit.h"
#include <QDebug>
#include <QMessageBox>

reserv_edit::reserv_edit(std::vector<std::string> data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reserv_edit)
{
    ui->setupUi(this);
    ui->num_txt->setText(QString::fromStdString(data[0]));
    ui->id_txt->setText(QString::fromStdString(data[1]));
    ui->model_txt->setText(QString::fromStdString(data[2]));
    ui->type_txt->setText(QString::fromStdString(data[3]));
    ui->fuel_txt->setText(QString::fromStdString(data[4]));
    ui->charge_txt->setText(QString::fromStdString(data[5]));
    ui->total_txt->setText(QString::fromStdString(data[6]));
    QString reserv_date = QString::fromStdString(data[7] + ".0");
    QString return_date = QString::fromStdString(data[8] + ".0");
    QString form = "yyyy-MM-dd HH:mm:ss.z";
    QDateTime dt = QDateTime::fromString(reserv_date,form);
    QDateTime dt2 = QDateTime::fromString(return_date, form);
    ui->res_date->setDateTime(dt);
    ui->ret_date->setDateTime(dt2);

    reserv_car = data[2];
    list();
}

reserv_edit::~reserv_edit()
{
    delete ui;
}



void reserv_edit::on_comboBox_currentIndexChanged(int index)
{
    list();
}

void reserv_edit::list()
{
    ui->tableWidget->clear();
    if(ui->comboBox->currentText() != "전체")
        query = "SELECT * FROM rentacar WHERE fuel = '" + ui->comboBox->currentText().toStdString() + "' AND quantity > booking";
    else
        query = "SELECT * FROM rentacar WHERE quantity > booking";
    sql.exec(QString::fromStdString(query));
    record = sql.record();
    int num = record.indexOf("num"); // DB 컬럼명
    int name = record.indexOf("carname");
    int type = record.indexOf("type");
    int fuel = record.indexOf("fuel");
    int charge = record.indexOf("charge");
    ui->tableWidget->setRowCount(sql.size());
    ui->tableWidget->setColumnCount(record.count()-2);
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("번호"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("모델"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("차종"));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("연료"));
    ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("일일요금"));

    int i =0;
    while(sql.next())
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(sql.value(num).toString()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(sql.value(name).toString()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(sql.value(type).toString()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(sql.value(fuel).toString()));
        ui->tableWidget->setItem(i++, 4, new QTableWidgetItem(sql.value(charge).toString()));

    }
}

void reserv_edit::on_tableWidget_cellDoubleClicked(int row, int column)
{
    int select_row = ui->tableWidget->currentRow();
    ui->model_txt->setText(ui->tableWidget->takeItem(select_row, 1)->text());
    ui->type_txt->setText(ui->tableWidget->takeItem(select_row, 2)->text());
    ui->fuel_txt->setText(ui->tableWidget->takeItem(select_row, 3)->text());
    ui->charge_txt->setText(ui->tableWidget->takeItem(select_row, 4)->text());
    int fee = ui->charge_txt->text().toInt();
    int days = ui->res_date->dateTime().daysTo(ui->ret_date->dateTime());
    int charge = fee * (days+1);
    ui->total_txt->setText(QString::number(charge));
    list();

}

void reserv_edit::on_edit_button_clicked()
{
    sql.prepare("UPDATE reservation SET car_model = ?, car_type = ?, fuel = ?, charge = ?, total = ?, reserv_date = ?, return_date = ? WHERE num = ?");
    sql.addBindValue(ui->model_txt->text());
    sql.addBindValue(ui->type_txt->text());
    sql.addBindValue(ui->fuel_txt->text());
    sql.addBindValue(ui->charge_txt->text());
    sql.addBindValue(ui->total_txt->text());
    sql.addBindValue(ui->res_date->dateTime());
    sql.addBindValue(ui->ret_date->dateTime());
    sql.addBindValue(ui->num_txt->text());
    sql.exec();

    query = "SELECT num, booking FROM rentacar WHERE carname ='" + ui->model_txt->text().toStdString() + "'";
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


    query = "SELECT num, booking FROM rentacar WHERE carname = '" + reserv_car +"'";
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

void reserv_edit::on_res_date_dateChanged(const QDate &date)
{
    int fee = ui->charge_txt->text().toInt();
    int days = ui->res_date->dateTime().daysTo(ui->ret_date->dateTime());
    int charge = fee * (days+1);
    ui->total_txt->setText(QString::number(charge));
}

void reserv_edit::on_ret_date_dateChanged(const QDate &date)
{
    int fee = ui->charge_txt->text().toInt();
    int days = ui->res_date->dateTime().daysTo(ui->ret_date->dateTime());
    int charge = fee * (days+1);
    ui->total_txt->setText(QString::number(charge));
}
