#include "port_processing.h"

port_processing::port_processing()
{
}

port_processing::~port_processing()
{
}

void port_processing::get_setting_value(ser_kom *skom){
    set.read(skom);
}

void port_processing::set_setting_value(form_setting_port *fport, ser_kom *skom){
    strcpy(skom->portname, fport->ui->cb_port->currentText().toLatin1());

    skom->baudrate = fport->ui->cb_baud->currentText().toInt();
    skom->data = fport->ui->cb_bits->currentText().toInt();

    if (fport->ui->cb_parity->currentIndex() == 0) { x = 0; }
    else if(fport->ui->cb_parity->currentIndex() == 1) { x = 2; }
    else { x = 3; }

    skom->parity = x;
    skom->stop = fport->ui->cb_stops->currentText().toInt();

    skom->port_index = fport->ui->cb_port->currentIndex();
    skom->baud_index = fport->ui->cb_baud->currentIndex();
    skom->data_index = fport->ui->cb_bits->currentIndex();
    skom->parity_index = fport->ui->cb_parity->currentIndex();
    skom->stop_index = fport->ui->cb_stops->currentIndex();

    set.write(skom);
}

void port_processing::apply_setting_value(form_setting_port *fport, ser_kom *skom){
    fport->ui->cb_port->setCurrentIndex(skom->port_index);
    fport->ui->cb_baud->setCurrentIndex(skom->baud_index);
    fport->ui->cb_bits->setCurrentIndex(skom->data_index);
    fport->ui->cb_parity->setCurrentIndex(skom->parity_index);
    fport->ui->cb_stops->setCurrentIndex(skom->stop_index);
}

void port_processing::build_interface(form_setting_port *fport, ser_kom *skom){
    iface.set_combo_port(fport->ui->cb_port);
    iface.set_combo_baud(fport->ui->cb_baud);
    iface.set_combo_data(fport->ui->cb_bits);
    iface.set_combo_prty(fport->ui->cb_parity);
    iface.set_combo_stop(fport->ui->cb_stops);
}

