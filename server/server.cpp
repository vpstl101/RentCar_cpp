#include "server.h"
#include <QMessageBox>
#include "chatting.h"

server::server(QObject *parent) :
    QObject(parent)
{
    Server = new QTcpServer(this);
    connect(Server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    if(!Server->listen(QHostAddress::Any, 9100))
    {
        qDebug() << "server does not start";
    }
    else
    {
        qDebug() << "server started";
    }
}


void server::newConnection()
{
    QTcpSocket *socket = Server->nextPendingConnection();
    socket->write("고객센터 연결대기중...\n");
    socket->flush();
    socket->bytesWritten(100);
    QMessageBox box;
    box.setText("채팅요청");
    box.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    box.setDefaultButton(QMessageBox::Yes);
    if(box.exec() == QMessageBox::Yes)
    {
        socket->write("고객센터와 연결되었습니다\n");
        chatting chat(socket);
        chat.exec();

    }
    else
    {
        socket->write("고객센터와 연결불가능\n");
    }

}

