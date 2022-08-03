#include "chatting.h"
#include "ui_chatting.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>


chatting::chatting(QTcpSocket * socket,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatting)
{
    ui->setupUi(this);
    clntsocket = socket;
    thread = new Thread(clntsocket, this);
    connect(thread, SIGNAL(setValue(QString)), this, SLOT(show(QString)));
    connect(thread, SIGNAL(alarmSetting(QString)), this, SLOT(alarm(QString)));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

chatting::~chatting()
{
    delete ui;
}

void chatting::show(QString msg)
{
    ui->textBrowser->append(msg);
}

void chatting::alarm(QString message)
{
    query = "INSERT INTO chatting (chat) VALUES ('" + ui->textBrowser->toPlainText().toStdString() + "')";
    sql.exec(QString::fromStdString(query));
    ui->textBrowser->append(message);
    QMessageBox::information(this, "", "채팅이 종료되었습니다");
    ui->send_btn->setEnabled(false);
    this->close();
    thread->exit(0);
}


void chatting::on_send_btn_clicked()
{
    if(ui->line->text() != "")
    {
        std::string msg = "[고객센터]" + ui->line->text().toStdString();
        ui->line->clear();
        clntsocket->write(msg.c_str());
        ui->textBrowser->append(QString::fromStdString(msg));
    }

}

void chatting::on_exit_btn_clicked()
{
    query = "INSERT INTO chatting (chat) VALUES ('" + ui->textBrowser->toPlainText().toStdString() + "')";
    sql.exec(QString::fromStdString(query));
    clntsocket->write("채팅종료");
    QMessageBox::information(this, "", "채팅이 종료되었습니다");
    ui->send_btn->setEnabled(false);
    this->close();
    thread->exit(0);
}
