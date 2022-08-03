#include "sight.h"
#include "ui_sight.h"
#include <QMessageBox>


sight::sight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sight)
{
    ui->setupUi(this);
    list();
}

sight::~sight()
{
    delete ui;
}

void sight:: list()
{
    ui->sight_list->clear();
    query = "SELECT * FROM travel";
    sql.exec(QString::fromStdString(query));
    record = sql.record();
    int num = record.indexOf("num"); // DB 컬럼명
    int place = record.indexOf("place");
    int addr = record.indexOf("addr");
    int type = record.indexOf("type");
    ui->sight_list->setRowCount(sql.size());
    ui->sight_list->setColumnCount(record.count());
    ui->sight_list->setHorizontalHeaderItem(0, new QTableWidgetItem("번호"));
    ui->sight_list->setHorizontalHeaderItem(1, new QTableWidgetItem("이름"));
    ui->sight_list->setHorizontalHeaderItem(3, new QTableWidgetItem("주소"));
    ui->sight_list->setHorizontalHeaderItem(2, new QTableWidgetItem("업종"));
    ui->sight_list->horizontalHeader()->setStretchLastSection(true);

    int i =0;
    while(sql.next())
    {
        ui->sight_list->setItem(i, 0, new QTableWidgetItem(sql.value(num).toString()));
        ui->sight_list->setItem(i, 1, new QTableWidgetItem(sql.value(place).toString()));
        ui->sight_list->setItem(i, 3, new QTableWidgetItem(sql.value(addr).toString()));
        ui->sight_list->setItem(i++, 2, new QTableWidgetItem(sql.value(type).toString()));
    }
}

void sight::on_edit_btn_clicked()
{
    if(ui->sight_list->currentItem() == NULL)
    {
        QMessageBox::information(this, "", "선택하세요");
    }
    else
    {
        int row;
        std::vector<std::string>data;

        row = ui->sight_list->currentRow();
        data.push_back(ui->sight_list->takeItem(row, 0)->text().toStdString());
        data.push_back(ui->sight_list->takeItem(row, 1)->text().toStdString());
        data.push_back(ui->sight_list->takeItem(row, 2)->text().toStdString());
        data.push_back(ui->sight_list->takeItem(row, 3)->text().toStdString());

        sight_edit edit(data);
        edit.setModal(true);
        edit.exec();
        list();
    }
}

void sight::on_delete_btn_clicked()
{
    if(ui->sight_list->currentItem() == NULL)
    {
        QMessageBox::information(this, "", "선택하세요");
    }
    else
    {
        int row = ui->sight_list->currentRow();
        query = "DELETE FROM travel WHERE num = '" + ui->sight_list->takeItem(row, 0)->text().toStdString() + "'";
        qDebug() << QString::fromStdString(query);
        sql.exec(QString::fromStdString(query));
        QMessageBox::information(this, "", "삭제완료");
        list();
    }

}

void sight::on_add_btn_clicked()
{
    sight_add add;
    add.setModal(true);
    add.exec();
    list();
}
