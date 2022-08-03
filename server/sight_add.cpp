#include "sight_add.h"
#include "ui_sight_add.h"
#include <QMessageBox>

sight_add::sight_add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sight_add)
{
    ui->setupUi(this);
}

sight_add::~sight_add()
{
    delete ui;
}

void sight_add::on_pushButton_clicked()
{
    sql.prepare("INSERT INTO travel (place, addr, type)" "VALUES (?, ?, ?)");
    sql.addBindValue(ui->name_txt->text());
    sql.addBindValue(ui->addr_txt->text());
    sql.addBindValue(ui->type_txt->text());
    sql.exec();
    QMessageBox::information(this, "", "추가완료");
    this->close();
}
