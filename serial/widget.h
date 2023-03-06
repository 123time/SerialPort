#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QSerialPort *serialPort;

private slots:
    void on_serialPort_open_pushButton_clicked();

    void on_serialPort_close_pushButton_clicked();

    void serialPortRead_slot();

    void on_serialPort_send_pushButton_clicked();

    void on_serialPort_clear_pushButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
