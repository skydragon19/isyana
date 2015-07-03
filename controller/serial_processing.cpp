#include "serial_processing.h"

serial_processing::serial_processing()
{
}

serial_processing::~serial_processing()
{
}

void serial_processing::set_serial_port(QSerialPort *port, ser_kom *skom){
    port->setPortName(skom->portname);
    port->setBaudRate(skom->baudrate);

    switch (skom->data){
    case 5:
        port->setDataBits(QSerialPort::Data5);
        break;
    case 6:
        port->setDataBits(QSerialPort::Data6);
        break;
    case 7:
        port->setDataBits(QSerialPort::Data7);
    default:
        port->setDataBits(QSerialPort::Data8);
        break;
    }

    switch (skom->parity){
    case 0:
        port->setParity(QSerialPort::NoParity);
        break;
    case 2:
        port->setParity(QSerialPort::EvenParity);
        break;
    default:
        port->setParity(QSerialPort::OddParity);
        break;
    }

    switch (skom->stop){
    case 1:
        port->setStopBits(QSerialPort::OneStop);
        break;
    default:
        port->setStopBits(QSerialPort::TwoStop);
        break;
    }

    port->setFlowControl(QSerialPort::NoFlowControl);
    port->open(QIODevice::ReadWrite);
}

