#include "carsearch.h"
#include "ui_carsearch.h"

carsearch::carsearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::carsearch)
{
    ui->setupUi(this);
}

carsearch::~carsearch()
{
    delete ui;
}

void carsearch::on_sear_clicked() //정보조회
{
    ui->search_bar->clear();
    ui->search_bar->setHorizontalHeaderItem(0, new QTableWidgetItem("차종"));
    ui->search_bar->setHorizontalHeaderItem(1, new QTableWidgetItem("종류"));
    ui->search_bar->setHorizontalHeaderItem(2, new QTableWidgetItem("연료"));
    ui->search_bar->setHorizontalHeaderItem(3, new QTableWidgetItem("댓수"));
    ui->search_bar->setHorizontalHeaderItem(4, new QTableWidgetItem("비용"));

    query="SELECT * FROM rentacar";
       sql.exec(QString::fromStdString(query));

       int i=0;
       while(sql.next())
       {
           ui->search_bar->setItem(i,0,new QTableWidgetItem(sql.value("carname").toString()));
           ui->search_bar->setItem(i,1,new QTableWidgetItem(sql.value("type").toString()));
           ui->search_bar->setItem(i,2,new QTableWidgetItem(sql.value("fuel").toString()));
           ui->search_bar->setItem(i,3,new QTableWidgetItem(sql.value("quantity").toString()));
           ui->search_bar->setItem(i++,4,new QTableWidgetItem(sql.value("charge").toString()));
       }
}

void carsearch::on_back_clicked() //정보조회 뒤로
{    this->close();}
