#ifndef SERIAL_PROCESSING_H
#define SERIAL_PROCESSING_H

#include <QSerialPort>

#include "util/core.h"

class serial_processing
{
public:
    serial_processing();
    ~serial_processing();

    void set_serial_port(QSerialPort *port, struct ser_kom *skom);
};

#endif // SERIAL_PROCESSING_H
