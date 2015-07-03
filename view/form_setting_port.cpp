#include "form_setting_port.h"
#include "ui_form_setting_port.h"

form_setting_port::form_setting_port(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_setting_port)
{
    ui->setupUi(this);
}

form_setting_port::~form_setting_port()
{
    delete ui;
}
