#include "car_edit.h"
#include "ui_car_edit.h"
#include <QMessageBox>
car_edit::car_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::car_edit)
{
    ui->setupUi(this);
    ui->edit_btn->hide();
    ui->num_txt->hide();
    ui->label_6->hide();
}

car_edit::car_edit(std::vector<std::string> data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::car_edit)
{
    ui->setupUi(this);
    ui->add_btn->hide();
    ui->num_txt->setText(QString::fromStdString(data[0]));
    ui->model_txt->setText(QString::fromStdString(data[1]));
    if(data[2] == "소형")
        ui->type_combo->setCurrentIndex(0);
    else if(data[2] == "중형")
        ui->type_combo->setCurrentIndex(1);
    else if(data[2] == "대형")
        ui->type_combo->setCurrentIndex(2);
    else
        ui->type_combo->setCurrentIndex(3);
    if(data[3] == "휘발유")
        ui->fuel_combo->setCurrentIndex(0);
    else if(data[3] == "경유")
        ui->fuel_combo->setCurrentIndex(1);
    else if(data[3] == "LPG")
        ui->fuel_combo->setCurrentIndex(2);
    else
        ui->fuel_combo->setCurrentIndex(3);

    ui->quantity_txt->setText(QString::fromStdString(data[4]));
    ui->charge_txt->setText(QString::fromStdString(data[5]));
}

car_edit::~car_edit()
{
    delete ui;
}

void car_edit::on_add_btn_clicked()
{
    sql.prepare("INSERT INTO rentacar (carname, type, fuel, quantity, charge) " "VALUES (?, ?, ?, ?, ?)");
    sql.addBindValue(ui->model_txt->text());
    sql.addBindValue(ui->type_combo->currentText());
    sql.addBindValue(ui->fuel_combo->currentText());
    sql.addBindValue(ui->quantity_txt->text());
    sql.addBindValue(ui->charge_txt->text());
    sql.exec();
    QMessageBox::information(this, "", "등록완료");
    this->close();
}

void car_edit::on_edit_btn_clicked()
{
    query = "UPDATE rentacar SET carname = '" + ui->model_txt->text().toStdString() + "', type = '"
            + ui->type_combo->currentText().toStdString() + "', fuel ='" + ui->fuel_combo->currentText().toStdString()
            +"', quantity ='" + ui->quantity_txt->text().toStdString() + "', charge = '" + ui->charge_txt->text().toStdString() + "' where num = '" + ui->num_txt->text().toStdString() +"'";
    qDebug()<<QString::fromStdString(query);
    sql.exec(QString::fromStdString(query));
    QMessageBox::information(this, "", "수정완료");
    this->close();

}
