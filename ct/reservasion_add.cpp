#include "reservasion_add.h"
#include "ui_reservasion_add.h"

reservasion_add::reservasion_add(QString logID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reservasion_add)
{
    ui->setupUi(this);
    log_id = logID;
    list();
}

reservasion_add::~reservasion_add()
{    delete ui;}

void reservasion_add::list()
{
    ui->table->clear();
    if(ui->comboBox->currentText() != "전체")
        query = "SELECT * FROM rentacar WHERE fuel ='" + ui->comboBox->currentText().toStdString() + "' AND quantity > booking";
    else
        query = "SELECT * FROM rentacar WHERE quantity > booking";

    sql.exec(QString::fromStdString(query));
    record = sql.record();
    int num = record.indexOf("num"); // DB 컬럼명
    int name = record.indexOf("carname");
    int type = record.indexOf("type");
    int fuel = record.indexOf("fuel");
    int quantity = record.indexOf("quantity");
    int charge = record.indexOf("charge");
    int booking = record.indexOf("booking");

    ui->table->setRowCount(sql.size());
    ui->table->setColumnCount(record.count());
    ui->table->setHorizontalHeaderItem(0, new QTableWidgetItem("번호"));
    ui->table->setHorizontalHeaderItem(1, new QTableWidgetItem("모델"));
    ui->table->setHorizontalHeaderItem(2, new QTableWidgetItem("차종"));
    ui->table->setHorizontalHeaderItem(3, new QTableWidgetItem("연료"));
    ui->table->setHorizontalHeaderItem(4, new QTableWidgetItem("수량"));
    ui->table->setHorizontalHeaderItem(5, new QTableWidgetItem("일일요금"));
    ui->table->setHorizontalHeaderItem(6, new QTableWidgetItem("예약수량"));

    int i =0;
    while(sql.next())
    {
        ui->table->setItem(i, 0, new QTableWidgetItem(sql.value(num).toString()));
        ui->table->setItem(i, 1, new QTableWidgetItem(sql.value(name).toString()));
        ui->table->setItem(i, 2, new QTableWidgetItem(sql.value(type).toString()));
        ui->table->setItem(i, 3, new QTableWidgetItem(sql.value(fuel).toString()));
        ui->table->setItem(i, 4, new QTableWidgetItem(sql.value(quantity).toString()));
        ui->table->setItem(i, 5, new QTableWidgetItem(sql.value(charge).toString()));
        ui->table->setItem(i++, 6, new QTableWidgetItem(sql.value(booking).toString()));
    }
}


void reservasion_add::on_comboBox_currentIndexChanged()
{    list();}

void reservasion_add::on_booking_clicked()
{

        int row2 = ui->table->currentRow();
        int num = ui->table->takeItem(row2, 6)->text().toInt();
        int fee = ui->table->takeItem(row2, 5)->text().toInt();
        int days = ui->reserv_time->dateTime().daysTo(ui->return_time->dateTime());
        int charge = fee * (days+1);

        sql.prepare("INSERT INTO reservation (id, car_model, car_type, fuel, charge, reserv_date, return_date, total) "
                    "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
        sql.addBindValue(log_id);
        sql.addBindValue(ui->table->takeItem(row2, 1)->text());
        sql.addBindValue(ui->table->takeItem(row2, 2)->text());
        sql.addBindValue(ui->table->takeItem(row2, 3)->text());
        sql.addBindValue(fee);
        sql.addBindValue(ui->reserv_time->dateTime());
        sql.addBindValue(ui->return_time->dateTime());
        sql.addBindValue(charge);

        sql.exec();
        QMessageBox::information(this, "", "예약완료");
        show_time();
        list();
        num++;
        QString number = QString::number(num);
        query = "UPDATE rentacar SET booking = '"
                + number.toStdString() + "' WHERE num = '" + ui->table->takeItem(row2, 0)->text().toStdString() +"'";

        sql.exec(QString::fromStdString(query));

    list();
}
void reservasion_add::show_time()
{
    QDateTime now = QDateTime::currentDateTime();
    ui->reserv_time->setDateTime(now);
    ui->return_time->setDateTime(now);
}


void reservasion_add::on_back_clicked()
{
    this ->close();
}
