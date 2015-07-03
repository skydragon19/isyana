#include "interface.h"

interface::interface()
{
}

interface::~interface()
{
}

void interface::set_combo_port(QComboBox *cbx){
    QString item;

    /* Port Windows */
    for(int i = 0; i < 4; i++){
        item.sprintf("COM%d", i+1);
        cbx->addItem(item);
    }

    /* Port Unix */
    for(int i = 0; i < 4; i++){
        item.sprintf("/dev/ttyUSB%d", i);
        cbx->addItem(item);
    }
}

void interface::set_combo_baud(QComboBox *cbx){
    QString item;

    for (int i = 0; i < 5; i++){
        if(i == 0) item.sprintf("9600");
        if(i == 1) item.sprintf("19200");
        if(i == 2) item.sprintf("38400");
        if(i == 3) item.sprintf("57600");
        if(i == 4) item.sprintf("115200");
        cbx->addItem(item);
    }
}

void interface::set_combo_data(QComboBox *cbx){
    QString item;

    /* start from 5 bit - 8 bit */
    for(int i = 5; i < 9; i++){
        item.sprintf("%d", i);
        cbx->addItem(item);
    }
}

void interface::set_combo_prty(QComboBox *cbx){
    QString item;

    for (int i = 0; i < 3; i++){
        if(i == 0) item.sprintf("none");
        if(i == 1) item.sprintf("odd");
        if(i == 2) item.sprintf("even");
        cbx->addItem(item);
    }
}

void interface::set_combo_stop(QComboBox *cbx){
    QString item;

    for (int i = 0; i < 2; i++){
        item.sprintf("%d", i+1);
        cbx->addItem(item);
    }
}

void interface::set_combo_flow(QComboBox *cbx){
    QString item;

    item.sprintf("none");
    cbx->addItem(item);

#if 0
    for (int i = 0; i < 3; i++){
        if(i == 0) item.sprintf("none");
        if(i == 1) item.sprintf("RTS/CTS");
        if(i == 2) item.sprintf("Xon/Xoff");
        cbx->addItem(item);
    }
#endif
}

void interface::label_counter(QHBoxLayout *hbox, QLabel *name, QLabel *equal, QLabel *value, QString nim){
    name->setText(nim);
    equal->setText(":");
    value->setText("...");

    hbox->addWidget(name, Qt::AlignCenter);
    hbox->addWidget(equal, Qt::AlignCenter);
    hbox->addWidget(value, Qt::AlignCenter);
}
