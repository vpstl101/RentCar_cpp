#include "trip.h"
#include "ui_trip.h"

trip::trip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::trip)
{
    ui->setupUi(this);
}

trip::~trip()
{
    delete ui;
}

void trip::on_sear_clicked()
{
    //search->hide();
    ui->search_bar->clear();
    ui->search_bar->setHorizontalHeaderItem(0, new QTableWidgetItem("장소"));
    ui->search_bar->setHorizontalHeaderItem(1, new QTableWidgetItem("주소"));
    ui->search_bar->setHorizontalHeaderItem(2, new QTableWidgetItem("장르"));

    query="SELECT * FROM travel";
       sql.exec(QString::fromStdString(query));

       //rec=query.record();
       int i=0;
       while(sql.next())
       {
           ui->search_bar->setItem(i,0,new QTableWidgetItem(sql.value("place").toString()));
           ui->search_bar->setItem(i,1,new QTableWidgetItem(sql.value("addr").toString()));
           ui->search_bar->setItem(i++,2,new QTableWidgetItem(sql.value("type").toString()));
       }
}

void trip::on_back_clicked()
{    this->close();}
