#include "car.h"
#include "ui_car.h"
#include "car_edit.h"
#include <QMessageBox>

car::car(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::car)
{
    ui->setupUi(this);
    list();
}

car::~car()
{
    delete ui;
}

void car::list()
{
    ui->carlist->clear();
    if(ui->comboBox->currentText() != "전체")
        query = "SELECT * FROM rentacar WHERE fuel ='" + ui->comboBox->currentText().toStdString() + "'";
    else
        query = "SELECT * FROM rentacar";


    sql.exec(QString::fromStdString(query));
    record = sql.record();
    int num = record.indexOf("num"); // DB 컬럼명
    int name = record.indexOf("carname");
    int type = record.indexOf("type");
    int fuel = record.indexOf("fuel");
    int quantity = record.indexOf("quantity");
    int charge = record.indexOf("charge");
    int booking = record.indexOf("booking");

    ui->carlist->setRowCount(sql.size());
    ui->carlist->setColumnCount(record.count());
    ui->carlist->setHorizontalHeaderItem(0, new QTableWidgetItem("번호"));
    ui->carlist->setHorizontalHeaderItem(1, new QTableWidgetItem("모델"));
    ui->carlist->setHorizontalHeaderItem(2, new QTableWidgetItem("차종"));
    ui->carlist->setHorizontalHeaderItem(3, new QTableWidgetItem("연료"));
    ui->carlist->setHorizontalHeaderItem(4, new QTableWidgetItem("수량"));
    ui->carlist->setHorizontalHeaderItem(5, new QTableWidgetItem("일일요금"));
    ui->carlist->setHorizontalHeaderItem(6, new QTableWidgetItem("에약수량"));
    ui->carlist->horizontalHeader()->setStretchLastSection(true);

    int i =0;
    while(sql.next())
    {
        ui->carlist->setItem(i, 0, new QTableWidgetItem(sql.value(num).toString()));
        ui->carlist->setItem(i, 1, new QTableWidgetItem(sql.value(name).toString()));
        ui->carlist->setItem(i, 2, new QTableWidgetItem(sql.value(type).toString()));
        ui->carlist->setItem(i, 3, new QTableWidgetItem(sql.value(fuel).toString()));
        ui->carlist->setItem(i, 4, new QTableWidgetItem(sql.value(quantity).toString()));
        ui->carlist->setItem(i, 5, new QTableWidgetItem(sql.value(charge).toString()));
        ui->carlist->setItem(i++, 6, new QTableWidgetItem(sql.value(booking).toString()));
    }
}

void car::on_add_btn_clicked()
{
    car_edit add;
    add.setModal(true);
    add.exec();
    list();
}

void car::on_edit_btn_clicked()
{
    if(ui->carlist->currentItem() == NULL)
    {
        QMessageBox::information(this, "", "선택하세요");
    }
    else
    {
        int row;
        std::vector<std::string>data;

        row = ui->carlist->currentRow();
        data.push_back(ui->carlist->takeItem(row, 0)->text().toStdString());
        data.push_back(ui->carlist->takeItem(row, 1)->text().toStdString());
        data.push_back(ui->carlist->takeItem(row, 2)->text().toStdString());
        data.push_back(ui->carlist->takeItem(row, 3)->text().toStdString());
        data.push_back(ui->carlist->takeItem(row, 4)->text().toStdString());
        data.push_back(ui->carlist->takeItem(row, 5)->text().toStdString());
        data.push_back(ui->carlist->takeItem(row, 6)->text().toStdString());
        car_edit edit(data);
        edit.setModal(true);
        edit.exec();
        list();
    }

}

void car::on_delete_btn_clicked()
{
    if(ui->carlist->currentItem() == NULL)
    {
        QMessageBox::information(this, "", "선택하세요");
    }
    else
    {
        int row = ui->carlist->currentRow();
        query = "DELETE FROM rentacar WHERE num = '" + ui->carlist->takeItem(row, 0)->text().toStdString() + "'";
        qDebug() << QString::fromStdString(query);
        sql.exec(QString::fromStdString(query));
        QMessageBox::information(this, "", "삭제완료");
        list();
    }
}

void car::on_comboBox_currentIndexChanged(int index)
{
    list();
}
