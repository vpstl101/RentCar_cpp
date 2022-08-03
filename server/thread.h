#ifndef THREAD_H
#define THREAD_H
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include "database.h"

class Thread : public QThread
{
    Q_OBJECT

public:
    explicit Thread(QTcpSocket * clntsocket, QObject * parent=0);
private:
    void run();
    QTcpSocket * socket;
    QSqlQuery sql;
    std::string query;

signals:
    void setValue(QString msg);
    void alarmSetting(QString message);
public slots:
    void disconnected();
    void readyRead();

};

#endif // THREAD_H
