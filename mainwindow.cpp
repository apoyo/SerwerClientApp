
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;


}



void MainWindow::on_pushButton_clicked()
{


     tcpServer = new QTcpServer(this);

    if(!tcpServer->listen()){

         QMessageBox::information(this,"Blad","Nie udalo sie otworzyc serwera");




     }

         QList<QString> fortunes;
     QString ip_adress;

      const QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();


      for (const QHostAddress &entry : ipAddressesList) {
         if (entry != QHostAddress::LocalHost && entry.toIPv4Address()) {
             ip_adress = entry.toString();
             break;
         }

         if (ip_adress.isEmpty())
             ip_adress = QHostAddress(QHostAddress::LocalHost).toString();


         ui->status->setText("The server is running on ");
         ui->label->setText(ip_adress);



         if(tcpServer->listen(QHostAddress::Any,8080)){

             connect(tcpServer,SIGNAL(newConnection()),this,SLOT(newConnection()));

             QMessageBox::information(this,"","Server Started");

         }







     //    connect(tcpServer, &QTcpServer::newConnection, this, &Server::sendFortune);

























      }
}

void MainWindow::newConnection()
{
      while (tcpServer->hasPendingConnections()) {
         Add_New_Client_Connection(tcpServer->nextPendingConnection());

      }

}

void MainWindow::Read_Data_From_Socket()
{

}

void MainWindow::Add_New_Client_Connection(QTcpSocket *socket)
{


      Client_Connection_List.append(socket);

      connect(socket,SIGNAL(readyRead()),this,SLOT(Read_Data_From_Socket()));





}
