#ifndef CORE
#define CORE

#include <QDebug>

#include <QSerialPort>

#define  NUM_KANAL  10

struct ser_kom{
    char portname[16];
    int  baudrate;
    int  data;
    int  parity;
    int  stop;

    int port_index;
    int baud_index;
    int data_index;
    int parity_index;
    int stop_index;
};

#endif // CORE

