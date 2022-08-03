#include "payment.h"
#include "ui_payment.h"
#include <QMessageBox>

payment::payment(std::vector <std::string> data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::payment)
{
    use_point = 0;
    insurance = 0;
    ui->setupUi(this);
    text_setting(data);

}

payment::~payment()
{
    delete ui;
}

void payment::text_setting(std::vector <std::string> data)
{
    reserv_num = data[0];
    ID = data[1];
    total = data[2];
    query = "SELECT point, grade FROM member WHERE id = '" + ID +"'";
    sql.exec(QString::fromStdString(query));
    record = sql.record();
    sql.next();
    int pointnum = record.indexOf("point");
    int grade_rec = record.indexOf("grade");
    QString point = sql.value(pointnum).toString();
    QString grade = sql.value(grade_rec).toString();
    if(grade == "premium")
        sale = 10;
    else if(grade == "vip")
        sale = 20;
    else
        sale = 0;
    ui->point_txt->setText(point);
    totalcharge = QString::fromStdString(total).toInt() * (100-sale) / 100;
    int discount = QString::fromStdString(total).toInt() - totalcharge;
    ui->sale_txt->setText(QString::number(discount));
    ui->total_txt->setText(QString::number(totalcharge));
    ui->insurance_txt->setText(QString::number(insurance));
}

void payment::on_point_btn_clicked()
{
    use_point = ui->point_txt->text().toInt();
    ui->point_txt->setText("0");
    plus_ins = totalcharge + insurance - use_point;
    ui->total_txt->setText(QString::number(plus_ins));
}


void payment::on_pay_btn_clicked()
{
    if(ui->card_txt->text() == NULL)
        QMessageBox::warning(this, "", "카드회사를 입력하세요");
    else if( ui->cardnum_txt->text() == NULL)
        QMessageBox::warning(this, "", "카드번호를 입력하세요");
    else
    {
        query = "UPDATE member SET point = '" + ui->point_txt->text().toStdString() + "', coupon ='주유쿠폰' WHERE id = '" + ID + "'";
        sql.exec(QString::fromStdString(query));
        query = "UPDATE reservation SET pay = 'O' WHERE num = '" + reserv_num + "'";
        sql.exec(QString::fromStdString(query));
        QMessageBox::information(this, "결제완료", "쿠폰이 지급되었습니다");
        this->close();
    }

}

void payment::on_comboBox_currentTextChanged(const QString &arg1)
{
    query = "SELECT reserv_date, return_date FROM reservation WHERE num = '" + reserv_num + "'";
    sql.exec(QString::fromStdString(query));
    record = sql.record();
    sql.next();
    int reserv_date = record.indexOf("reserv_date");
    int return_date = record.indexOf("return_date");
    QDateTime reservDate = sql.value(reserv_date).toDateTime();
    QDateTime returnDate = sql.value(return_date).toDateTime();
    int days = reservDate.daysTo(returnDate);

    if(ui->comboBox->currentText() == "일반자차")
    {
        insurance = 50000 * (days+1);
    }
    else if(ui->comboBox->currentText() == "완전자차")
    {
        insurance = 55000 * (days+1);
    }
    else
    {
        insurance = 0;
    }
    ui->insurance_txt->setText(QString::number(insurance));
    plus_ins = totalcharge + insurance - use_point;
    ui->total_txt->setText(QString::number(plus_ins));

}
