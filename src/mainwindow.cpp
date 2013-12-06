#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <thread>
#include <string>
#include <cstring>
#include <iostream>

extern "C" {
#undef __cplusplus
#include "net/packet.h"
#include "net/cryptnet.h"
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::closing()
{
    cnet_close();
}

void MainWindow::on_inputBox_returnPressed()
{
	net_packet_t pk;
    std::string msg;
    msg = (ui->inputBox->text()).toStdString() ;
	pk.size = msg.length();
	memcpy(pk.body,msg.c_str(),msg.length());

	cnet_send(&pk);

    ui->chatLog->append(QString( (std::string("<b><font color=\"blue\">You:</font></b> ") + msg).c_str()  ));

    ui->inputBox->setText(QString(""));

}

void MainWindow::on_sendButton_clicked()
{
    this->on_inputBox_returnPressed();
}

void MainWindow::listen(void)
{
    static std::thread t1(cli_recv,ui);
}

void cli_recv(Ui::MainWindow* ui)
{
    net_packet_t pk;

    while (1) {
        if (0 >= cnet_recv(&pk)) {
            std::cout << "Error in receiving message\n";
        }
        ui->chatLog->append(QString( (std::string("<b><font color=\"red\">Friend:</font></b> ") + std::string(pk.body)).c_str() ));

    }

}
