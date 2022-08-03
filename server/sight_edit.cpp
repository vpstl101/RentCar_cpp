#include "sight_edit.h"
#include "ui_sight_edit.h"
#include <QMessageBox>
sight_edit::sight_edit(std::vector<std::string> data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sight_edit)
{
    ui->setupUi(this);
    ui->num_txt->setText(QString::fromStdString(data[0]));
    ui->name_txt->setText(QString::fromStdString(data[1]));
    ui->addr_txt->setText(QString::fromStdString(data[2]));
    ui->type_txt->setText(QString::fromStdString(data[3]));
}

sight_edit::~sight_edit()
{
    delete ui;
}


void sight_edit::on_edit_btn_clicked()
{
    query = "UPDATE travel SET place = '" + ui->name_txt->text().toStdString() + "', addr = '"
            + ui->addr_txt->text().toStdString() + "', type ='" + ui->type_txt->text().toStdString() +"' where num = '" + ui->num_txt->text().toStdString() +"'";
    qDebug()<<QString::fromStdString(query);
    sql.exec(QString::fromStdString(query));
    QMessageBox::information(this, "", "수정완료");
    this->close();

}
