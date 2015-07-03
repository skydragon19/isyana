#include "form_reset_kanal.h"
#include "ui_form_reset_kanal.h"

form_reset_kanal::form_reset_kanal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_reset_kanal)
{
    ui->setupUi(this);
}

form_reset_kanal::~form_reset_kanal()
{
    delete ui;
}
