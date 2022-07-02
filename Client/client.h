#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
class QUdpSocket;
QT_END_NAMESPACE

class Client : public QDialog
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    void close();
    ~Client();

private slots:
    void processPendingDatagrams();
    void show();
    void showOrhide(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::Client *ui;
    QSystemTrayIcon tray;
    QUdpSocket udpSocket;
    QMenu menu;
    QAction action;
    QString message;
    int portNumber = 45454;

    bool IsByCloseButton = true;

    void closeEvent(QCloseEvent *event);
};
#endif // CLIENT_H
