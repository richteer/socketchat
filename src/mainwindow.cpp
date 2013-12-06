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


extern int argc_derp;
extern char **argv_derp;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    thread t1(MainWindow::cli_recv);

}

MainWindow::~MainWindow()
{
    delete ui;

    t1.join();
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

    std::cout << "Sent message: '" << msg << "'!" << std::endl;
}

void MainWindow::on_sendButton_clicked()
{

}

void MainWindow::cli_recv()
{
    net_packet_t pk;

    while (1) {
        cnet_recv(&pk);
        cout << "Received a message!";
        ui->chatLog->append();


    }


}
