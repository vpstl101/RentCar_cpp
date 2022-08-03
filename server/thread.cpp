#include "thread.h"

Thread::Thread(QTcpSocket * clntsocket, QObject *parent) :
    QThread(parent)
{
    socket = clntsocket;
}

void Thread::run()
{
    qDebug() <<"start thread";


    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    exec();

}

void Thread::readyRead()
{
    QString msg = QString(socket->readAll());
    qDebug() << "clntmsg : " << msg <<endl;
    emit setValue(msg);
    socket->write(msg.toStdString().c_str());
}

void Thread::disconnected()
{
    emit alarmSetting("채팅 종료");
    qDebug() << "disconnected";
    socket->deleteLater();
}
