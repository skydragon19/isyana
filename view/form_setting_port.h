#ifndef FORM_SETTING_PORT_H
#define FORM_SETTING_PORT_H

#include <QDialog>

#include "util/core.h"

namespace Ui {
class form_setting_port;
}

class form_setting_port : public QDialog
{
    Q_OBJECT

public:
    Ui::form_setting_port *ui;

    explicit form_setting_port(QWidget *parent = 0);
    ~form_setting_port();

private:

};

#endif // FORM_SETTING_PORT_H
