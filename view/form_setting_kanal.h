#ifndef FORM_SETTING_KANAL_H
#define FORM_SETTING_KANAL_H

#include <QObject>
#include <QDialog>
#include <QComboBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QTimer>
#include <QSerialPort>

#include <unistd.h>

#include "util/core.h"

#include "controller/serial_processing.h"

namespace Ui {
class form_setting_kanal;
}

class form_setting_kanal : public QDialog
{
    Q_OBJECT

public:
    Ui::form_setting_kanal *ui;

    explicit form_setting_kanal(QWidget *parent = 0, QSerialPort *port = 0);
    ~form_setting_kanal();

    void set_timer(struct ser_kom *skom, QSerialPort *port);
    QTimer *tim_set;

    QComboBox *cmbox[NUM_KANAL];
    QCheckBox *chbox[NUM_KANAL];
    QLineEdit *lines[NUM_KANAL];

public slots:
    void set_kanal();

private slots:
    void on_pb_accept_clicked();

private:
    int c_dat;
    int num;

    int ch_val;
    int cm_val;
    QString l_val;

    QString str;

    void set_enabled(int cnt);
    void set_type(int cnt);
    void set_label(int cnt);

    QSerialPort *fs_port;
    serial_processing s_pro;
};

#endif // FORM_SETTING_KANAL_H
