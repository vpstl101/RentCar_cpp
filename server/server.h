#ifndef SERVER_H
#define SERVER_H
#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class server : public QObject
{
    Q_OBJECT
public:
    explicit server(QObject *parent = 0);

signals:

public slots:
    void newConnection();

private:
    QTcpServer *Server;
};

#endif // SERVER_H
