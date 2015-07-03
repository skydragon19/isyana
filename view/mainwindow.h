#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QIODevice>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QDateTime>

#include <QHBoxLayout>
#include <QLabel>

#include <unistd.h>

#include "model/setting.h"
#include "model/interface.h"
#include "model/log.h"

#include "view/form_setting_kanal.h"
#include "view/form_setting_port.h"

#include "controller/port_processing.h"
#include "controller/serial_processing.h"

#include "util/core.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void read_port();
    void print_value();
    void request_to_santer();

    void on_pb_reset_clicked();

    void on_actionPort_set_triggered();
    void on_actionPort_open_triggered();

    void on_actionChannel_set_triggered();
    void on_actionStart_monitoring_triggered();

private:
    Ui::MainWindow *ui;

    void core_initialization();

    void interface_initialization();
    void serialport_initialization();
    void timer_initialization();
    void memory_initialization();

    void set_parameter_port();

    QTimer *tim;
    QTimer *tim_p;
    QTimer *tim_set;

    QSerialPort *port;
    QSerialPortInfo *port_info;
    interface *iface;
    log *logs;
    form_setting_kanal *fset;
    form_setting_port *fport;
    Setting *settings;

    port_processing *port_process;
    serial_processing *ser_process;


    QString n_label;
    QString n_value;

    QString counter[NUM_KANAL];
    QString string_dat;

    char char_dat[8192];
    bool stats;
    int len;
    int cnt;

    QHBoxLayout *hboxl[NUM_KANAL];
    QLabel *name_cnt[NUM_KANAL];
    QLabel *equal[NUM_KANAL];
    QLabel *value[NUM_KANAL];

    QString port_name;
    QString baudrate;
    QString databits;
    QString parity;
    QString stopbits;

    QString str_request;
    QString time;

    bool open;

    QString coba;
    int cnt_data;
    int cnt_tes;

    struct ser_kom *skom;

    bool fport_status;
};

#endif // MAINWINDOW_H
