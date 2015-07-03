#ifndef FORM_RESET_KANAL_H
#define FORM_RESET_KANAL_H

#include <QDialog>
#include <QCheckBox>

#include <QIODevice>
#include <QSerialPort>
#include <QTimer>

#include <unistd.h>

#include <util/core.h>

namespace Ui {
class form_reset_kanal;
}

class form_reset_kanal : public QDialog
{
    Q_OBJECT

public:
    Ui::form_reset_kanal *ui;

    explicit form_reset_kanal(QWidget *parent = 0);
    ~form_reset_kanal();

private:
    QCheckBox *chbox[NUM_KANAL];
};

#endif // FORM_RESET_KANAL_H
