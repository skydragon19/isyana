#include "form_setting_kanal.h"
#include "ui_form_setting_kanal.h"

form_setting_kanal::form_setting_kanal(QWidget *parent, QSerialPort *port) :
    QDialog(parent),
    ui(new Ui::form_setting_kanal)
{
    ui->setupUi(this);this->ui->t_kanal->setColumnCount(4);

    this->ui->t_kanal->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Kanal")));
    this->ui->t_kanal->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Enable")));
    this->ui->t_kanal->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("Status")));
    this->ui->t_kanal->setHorizontalHeaderItem(3, new QTableWidgetItem(QString("Satuan")));

    this->ui->t_kanal->setRowCount(NUM_KANAL);
    this->ui->t_kanal->verticalHeader()->setHidden(true);

    this->ui->t_kanal->setColumnWidth(2, 140);

    for (int i = 0; i < NUM_KANAL; i++){
        chbox[i] = new QCheckBox("Active");
        cmbox[i] = new QComboBox();
        lines[i] = new QLineEdit();

        this->ui->t_kanal->setItem(i, 0, new QTableWidgetItem(QString::number(i+1)));
        this->ui->t_kanal->setCellWidget(i,1, chbox[i]);

        cmbox[i]->addItem("RPM");
        cmbox[i]->addItem("On/Off");
        cmbox[i]->addItem("Push Button");
        cmbox[i]->addItem("Flow");
        cmbox[i]->addItem("RPM_RH");
        cmbox[i]->addItem("Running Hour");
        cmbox[i]->addItem("On/Off_RH");
        cmbox[i]->addItem("Analog Monita");
        cmbox[i]->addItem("Analog RH");

        this->ui->t_kanal->setCellWidget(i,2, cmbox[i]);
        this->ui->t_kanal->setCellWidget(i,3, lines[i]);
    }

    fs_port = new QSerialPort(this);
}

form_setting_kanal::~form_setting_kanal()
{
    delete ui;
}

void form_setting_kanal::set_timer(ser_kom *skom, QSerialPort *port){
    c_dat = 0;
    num = this->ui->t_kanal->model()->rowCount();


    fs_port = port;
    //s_pro.set_serial_port(fs_port, skom);

    tim_set = new QTimer(this);
    connect(tim_set, SIGNAL(timeout()), this, SLOT(set_kanal()));
    tim_set->stop();
}

void form_setting_kanal::set_kanal(){
#if 1
    c_dat++;

    this->set_enabled(c_dat-1);
    sleep(1);
    this->set_type(c_dat-1);
    sleep(1);
    this->set_label(c_dat-1);
    sleep(1);

    if (c_dat == num){
        tim_set->stop();
        c_dat = 0;

        qDebug() << "selesai!";
    }
#endif
}

void form_setting_kanal::set_enabled(int cnt){
    switch (chbox[cnt]->isChecked()){
    case true:
        ch_val = 1;
        break;
    default:
        ch_val = 0;
        break;
    }
    str.sprintf("set_data %d status %d\r\n", c_dat, ch_val);
    fs_port->write(str.toLocal8Bit().data());
}

void form_setting_kanal::set_type(int cnt){
    switch (cmbox[cnt]->currentIndex()){
    case 0:
        cm_val = 1;
        break;
    case 1:
        cm_val = 2;
        break;
    case 2:
        cm_val = 3;
        break;
    case 3:
        cm_val = 6;
        break;
    case 4:
        cm_val = 7;
        break;
    case 5:
        cm_val = 8;
        break;
    case 6:
        cm_val = 9;
        break;
    case 7:
        cm_val = 250;
        break;
    default:
        cm_val = 999;
        break;
    }
    str.sprintf("set_kanal %d status %d\r\n", c_dat, cm_val);
    fs_port->write(str.toLocal8Bit().data());
}

void form_setting_kanal::set_label(int cnt){
    l_val = lines[cnt]->text();

    str.sprintf("set_data %d satuan %s\r\n", c_dat, l_val.toLocal8Bit().data());
    fs_port->write(str.toLocal8Bit().data());
}

void form_setting_kanal::on_pb_accept_clicked()
{
    this->tim_set->start(3500);
}
