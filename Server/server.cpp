#include "server.h"
#include "ui_server.h"

#include <QMessageBox>
#include <QSettings>
#include <QUdpSocket>

Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);

    setWindowTitle("Server");

    QList<QString> args = QCoreApplication::arguments();
    if(args.count() == 1)
        QMessageBox::warning(nullptr, "Warning!","Bad arguments");
    QSettings sett(QCoreApplication::arguments()[1], QSettings::IniFormat);
    portNumber = sett.value("PORT/PortNumber", "0").toInt();
}

void Server::broadcastDatagram()
{
    if(ui->MessageEdit->text().isEmpty())
        return;

    QString message = ui->MessageEdit->text();

    QByteArray datagram = message.toUtf8();

    if(!database.WriteLine(message))
        close();

    udpSocket.writeDatagram(datagram, QHostAddress::Broadcast, portNumber);

    QTextCursor cursor = ui->MessageBox->textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText("Sent: " + message + "\n");
}


void Server::on_SendButton_clicked()
{

    broadcastDatagram();

    ui->MessageEdit->clear();

    ui->MessageEdit->setFocus();
}

void Server::showEvent(QShowEvent* event)
{
    if(!database.MakeConnection())
        close();

    QMainWindow::showEvent(event);
}

Server::~Server()
{
    delete ui;
}
