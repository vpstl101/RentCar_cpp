#include "withdraw.h"
#include "ui_withdraw.h"

withdraw::withdraw(QString logid, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::withdraw)
{
    ui->setupUi(this);
    log_id =logid;
}

withdraw::~withdraw()
{    delete ui;}

void withdraw::on_draw_button_clicked() //탈퇴 버튼
{
    QString id = ui->getID->text();
    QString pw = ui->getPW->text();
    QString name = ui->getName->text();

    query = "SELECT id, pw, name FROM member WHERE id ='"+log_id.toStdString()+"'";
    qDebug() << QString::fromStdString(query); //쿼리문  내용 표시
    sql.exec(QString::fromStdString(query));

    sql.first();
    if(sql.size() != 0)
    {
        if(sql.value(0).toString()==id and sql.value(1).toString() == pw and sql.value(2).toString() == name)
         {
            query = "DELETE FROM member WHERE id='"+id.toStdString()+"' AND pw='"+pw.toStdString()+"' AND name='"+name.toStdString()+"'";
            sql.exec(QString::fromStdString(query));

            QMessageBox::information(this, "", "탈퇴 완료! 이용해 주셔서 감사합니다");
            this->close();
         }
        else
            QMessageBox::warning(this, "error", "입력하신 정보를 다시 확인하세요");
    }
    else
        QMessageBox::warning(this, "error", "입력하신 정보를 다시 확인하세요");
}
