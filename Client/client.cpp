#include "client.h"
#include "ui_client.h"

#include <QAction>
#include <QCloseEvent>
#include <QMenu>
#include <QMessageBox>
#include <QSettings>
#include <QUdpSocket>

Client::Client(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Client), action("Close")
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);

    QIcon TrayIcon(":/new/images/test.png");
    tray.setToolTip("Waiting for messages");
    tray.show();
    tray.setIcon(TrayIcon);


    menu.addAction(&action);
    tray.setContextMenu(&menu);
    
    if(!udpSocket.bind(portNumber, QUdpSocket::ShareAddress | QUdpSocket :: ReuseAddressHint))
        QMessageBox::warning(nullptr, "Warning!","Can not connect to server!");

    connect(&udpSocket, &QUdpSocket::readyRead,
            this, &Client::processPendingDatagrams);

    connect(&action, &QAction::triggered, this, &Client::close);

    connect(&tray, &QSystemTrayIcon::messageClicked, this, &Client::show);

    connect(&tray,&QSystemTrayIcon::activated, this, &Client::showOrhide);
}

void Client::close()
{
    IsByCloseButton = false;
    window()->close();
}

void Client::processPendingDatagrams()
{
    QByteArray datagram;

    QIcon NotificationIcon(":/new/images/test.png");

    while (udpSocket.hasPendingDatagrams()) {
        datagram.resize(int(udpSocket.pendingDatagramSize()));

        udpSocket.readDatagram(datagram.data(), datagram.size());

        message = datagram;

        tray.showMessage("New message!", message, NotificationIcon);

        QTextCursor cursor = ui->MessageBox->textCursor();
        cursor.movePosition(QTextCursor::End);

        cursor.insertText("Received: " + message + "\n");
    }
}

void Client::show()
{

    window()->show();
}

void Client::showOrhide(QSystemTrayIcon::ActivationReason reason)
{
    if(reason != QSystemTrayIcon::Context){
        if(window()->isHidden())
            window()->show();
        else
            window()->hide();
    }
}

void Client::closeEvent(QCloseEvent *event)
{
    if(IsByCloseButton){

        window()->hide();
        event->ignore();
    }
    else{
        event->accept();
        IsByCloseButton = true;
    }
}

Client::~Client()
{
    delete ui;
}

