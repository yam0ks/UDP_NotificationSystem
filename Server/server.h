#ifndef SERVER_H
#define SERVER_H

#include "database.h"

#include <QMainWindow>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
class QUdpSocket;
QT_END_NAMESPACE

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

private slots:
    void broadcastDatagram();
    void on_SendButton_clicked();

private:
    Ui::Server *ui;
    QUdpSocket udpSocket;
    DataBase database;
    int portNumber;
    void showEvent(QShowEvent* event);
};
#endif // SERVER_H
