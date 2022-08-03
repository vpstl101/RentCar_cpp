#include "chat.h"
#include "ui_chat.h"

chat::chat(QString log_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat)
{
    ui->setupUi(this);
    logid =log_id;

    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    socket->connectToHost("127.0.0.1", 9100);
    thread();
}

chat::~chat()
{   delete ui;
    delete socket;
}

void chat::readyRead()
{
    QString msg = QString(socket->readAll());
    qDebug() << "clntmsg : " << msg <<endl;
    if( msg == "채팅종료" )
    {
        QMessageBox::information(this, "", "채팅이 종료되었습니다");
        this->close();
    }

    ui->show->append(msg);
}

void chat::connected()
{
    socket->write(QString(" "+ui->line->text()+"\n").toUtf8());
}

void chat::on_send_clicked()
{
    std::string msg= "["+logid.toStdString()+"]" + ui->line->text().toStdString();

    if(ui->line->text() != "")
        socket->write(msg.c_str());

    ui->line->clear();
    ui->line->setFocus();
}
