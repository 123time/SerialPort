#include "widget.h"
#include "ui_widget.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <iostream>

using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //create QSerialPort
    serialPort = new QSerialPort(this);
    //connect serialPort to deal
    connect(serialPort,SIGNAL(readyRead()),this,SLOT(serialPortRead_slot()));
    QStringList serialNamePort;
    //acquire SerialPort Number
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        serialNamePort<<info.portName();
    }
    //write the number to ui widget
    ui->serial_port_number_comboBox->addItems(serialNamePort);
}

Widget::~Widget()
{
    delete ui;
}

//serialPort close
void Widget::on_serialPort_open_pushButton_clicked()
{
    QSerialPort::BaudRate baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::StopBits stopBits;
    QSerialPort::Parity   checkBits;

    if(ui->serial_port_Baudrate_comboBox->currentText()=="4800"){
        baudRate = QSerialPort::Baud4800;
    }else if(ui->serial_port_Baudrate_comboBox->currentText()=="9600"){
        baudRate = QSerialPort::Baud9600;
    }else if (ui->serial_port_Baudrate_comboBox->currentText()=="115200") {
        baudRate = QSerialPort::Baud115200;
    }

    if(ui->serial_port_data_bit_comboBox->currentText()=="5"){
        dataBits = QSerialPort::Data5;
    }else if (ui->serial_port_data_bit_comboBox->currentText()=="6") {
        dataBits = QSerialPort::Data6;
    }else if (ui->serial_port_data_bit_comboBox->currentText()=="7") {
        dataBits = QSerialPort::Data7;
    }else if (ui->serial_port_data_bit_comboBox->currentText()=="8") {
        dataBits = QSerialPort::Data8;
    }

    if(ui->serial_port_stop_bit_comboBox->currentText() == "1"){
        stopBits = QSerialPort::OneStop;
    }else if (ui->serial_port_stop_bit_comboBox->currentText() == "1.5") {
        stopBits = QSerialPort::OneAndHalfStop;
    }else if (ui->serial_port_stop_bit_comboBox->currentText() == "2") {
        stopBits = QSerialPort::TwoStop;
    }

    if(ui->serial_port_check_bit_comboBox->currentText() == "none"){
        checkBits = QSerialPort::NoParity;
    }

    serialPort->setPortName(ui->serial_port_number_comboBox->currentText());
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(dataBits);
    serialPort->setStopBits(stopBits);
    serialPort->setParity(checkBits);

    if(serialPort->open(QIODevice::ReadWrite) == true){
        QMessageBox::information(this,"串口打开提示：","串口打开成功！");
    }else {
        QMessageBox::critical(this,"串口打开提示：","串口打开失败！");
    }
}

//serialPort close
void Widget::on_serialPort_close_pushButton_clicked()
{
    serialPort->close();
}

//deal with read and receive
void Widget::serialPortRead_slot(){
    QString buf;
    buf = QString(serialPort->readAll());
    ui->receive_TextEdit->appendPlainText(buf);
}


//deal with send
void Widget::on_serialPort_send_pushButton_clicked()
{
    cout<<ui->edit_lineEdit->text().toLocal8Bit().data()<<endl;
    int ret = serialPort->write(ui->edit_lineEdit->text().toLocal8Bit().data());
    if(ret == -1){
        QMessageBox::critical(this,"发送提示：","发送失败！");
    }else {
        QMessageBox::information(this,"发送提示：","发送成功！");
    }
}

//clear
void Widget::on_serialPort_clear_pushButton_clicked()
{
    ui->receive_TextEdit->clear();
}

