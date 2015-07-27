#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Monita Flow Monitoring");

    logs = new log();
    logs->print(this->ui->plainTextEdit, "Monita Flow Comp .. Start");
    logs->print(this->ui->plainTextEdit, "");

    stats = false;
    open = false;

    fport_status = false;

    string_dat.clear();
    n_label.clear();
    cnt = 0;
    cnt_data = 0;

    cnt_tes = 0;

    for (int i = 0 ; i < NUM_KANAL ; i++){
        counter[i].clear();
    }

    logs->print(this->ui->plainTextEdit, "Initialization Start ...");
    this->core_initialization();
    logs->print(this->ui->plainTextEdit, "Initialization Complete");
    logs->print(this->ui->plainTextEdit, "");
}

MainWindow::~MainWindow()
{
    port->close();    
    delete ui;
}

void MainWindow::core_initialization(){
    port_process = new port_processing();
    ser_process = new serial_processing();

    this->memory_initialization();
    this->interface_initialization();
    this->serialport_initialization();
    this->timer_initialization();
}

void MainWindow::memory_initialization(){
    skom = (struct ser_kom *) malloc (sizeof (struct ser_kom));
    memset((char *) skom, 0, sizeof(struct ser_kom));

    port_process->get_setting_value(skom);
}

void MainWindow::serialport_initialization(){
    port = new QSerialPort(this);
    connect(port, SIGNAL(readyRead()), this, SLOT(read_port()));

    fset = new form_setting_kanal(this);
    fport = new form_setting_port(this);
}

void MainWindow::timer_initialization(){
    tim = new QTimer(this);
    connect(tim, SIGNAL(timeout()), this, SLOT(request_to_santer()));
    tim->stop();

    tim_p = new QTimer(this);
    connect(tim_p, SIGNAL(timeout()), this, SLOT(print_value()));
    tim_p->stop();
}

void MainWindow::interface_initialization(){
    /* label counter */
    for (int i = 0; i < NUM_KANAL; i++){
        hboxl[i] = new QHBoxLayout(this);
        name_cnt[i] = new QLabel(this);
        equal[i] = new QLabel(this);
        value[i] = new QLabel(this);

        if (i < i-1){
            n_label.sprintf("Kanal %d  ", i+1);
        }
        else{
            n_label.sprintf("Kanal %d ", i+1);
        }

        iface->label_counter(hboxl[i], name_cnt[i], equal[i], value[i], n_label);
        this->ui->verticalLayout->addLayout(hboxl[i]);
    }
}

void MainWindow::request_to_santer(){
    time = QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss");

    logs->print(this->ui->plainTextEdit, "Request Data to Santer %s", time.toLocal8Bit().data());

    string_dat.clear();
    port->write("cek_data 1\r\n");

    tim_p->start(200);
}

void MainWindow::read_port(){
    string_dat.sprintf("%s%s", string_dat.toLocal8Bit().data(), port->readAll().data());
    qDebug() << string_dat.toLocal8Bit().data();
}

void MainWindow::print_value()
{
#if 1
    len = string_dat.length();

    strcpy((char *) char_dat, string_dat.toLatin1());

    for (int i = 0; i < len; i++){
        if(char_dat[i] == '['){
            stats = true;
        }
        else if(char_dat[i] == ']'){
            stats = false;
            cnt++;
        }

        if(stats == true){
            if (char_dat[i] == '0' || char_dat[i] == '1' || char_dat[i] == '2' || char_dat[i] == '3' || char_dat[i] == '4' ||
                char_dat[i] == '5' || char_dat[i] == '6' || char_dat[i] == '7' || char_dat[i] == '8' || char_dat[i] == '9' || char_dat[i] == '.'){

                counter[cnt].sprintf("%s%c", counter[cnt].toLocal8Bit().data(), char_dat[i]);
            }
        }
    }

    for (int i = 0 ; i < NUM_KANAL ; i++){
        /* ditampilkan dulu sebelum di hapus */
        value[i]->setText(counter[i]);

        /* dihapus */
        counter[i].clear();
    }

    /* selesai paket, cnt di reset , buff string di kosongkan
     * timer print (tim_p) di stop */
    cnt = 0;
    string_dat.clear();
    tim_p->stop();
#endif
}

void MainWindow::on_pb_reset_clicked()
{
    /* reset all */
    QString str;
    for (int i = 0; i < NUM_KANAL; i++){
        str.sprintf("set_mem %d 0\r\n", i+1);
        port->write(str.toLocal8Bit().data());
        sleep(0.2);
    }

    /* Info Selesai Reset */
}

void MainWindow::set_parameter_port(){

}

void MainWindow::on_actionPort_open_triggered()
{
    if (open == false){
        logs->print(this->ui->plainTextEdit, "Configure Serial Port ...");
        ser_process->set_serial_port(port, skom);

        logs->print(this->ui->plainTextEdit, "Port Name : %s, Baudrate : %d, Data Bits : %d, Parity %d, Stop Bits %d",
                    skom->portname, skom->baudrate, skom->data, skom->parity, skom->stop);

        logs->print(this->ui->plainTextEdit, "");
        logs->print(this->ui->plainTextEdit, "Port serial succesfully open!");

        this->ui->actionPort_open->setIcon(QIcon(":icon/icon/port_closed.png"));
        this->ui->actionPort_open->setToolTip("Close Port");

        open = true;

        this->ui->actionStart_monitoring->setEnabled(true);
        this->ui->actionPort_set->setDisabled(true);
    }
    else{
        if (tim->isActive()){
            tim->stop();
        }
        port->close();

        logs->print(this->ui->plainTextEdit, "Port serial closed!");

        this->ui->actionPort_open->setIcon(QIcon(":icon/icon/port.png"));
        this->ui->actionPort_open->setToolTip("Open Port");

        open = false;

        this->ui->actionStart_monitoring->setDisabled(true);
        this->ui->actionPort_set->setEnabled(true);
        this->ui->pb_reset->setDisabled(true);
    }
}

void MainWindow::on_actionPort_set_triggered()
{
    int res;

    fport->setWindowTitle("Setting Port");
    fport->setModal(true);

    if (fport_status == false){
        port_process->build_interface(fport, skom);
        fport_status = true;
    }

    port_process->apply_setting_value(fport, skom);

    res = fport->exec();

    if (res == 0){
        return;
    }
    else{
        port_process->set_setting_value(fport, skom);

        if (port->isOpen()){
            if (tim->isActive()){
                tim->stop();
            }

            port->close();

            ser_process->set_serial_port(port, skom);

            port->setFlowControl(QSerialPort::NoFlowControl);
            port->open(QIODevice::ReadWrite);

            tim->start(1000);
        }
    }
}

void MainWindow::on_actionChannel_set_triggered()
{
    int res;

    fset->setWindowTitle("Setting Kanal");
    fset->setModal(true);

    fset->set_timer(skom, port);

    res = fset->exec();

#if 0
    if (res == 0){
        /* open port */
        ser_process->set_serial_port(port, skom);

        port->setFlowControl(QSerialPort::NoFlowControl);
        port->open(QIODevice::ReadWrite);

        fset->tim_set->stop();
        delete fset->tim_set;

        return;
    }
    else{
        /* open port */
        fset->run();

        ser_process->set_serial_port(port, skom);

        port->setFlowControl(QSerialPort::NoFlowControl);
        port->open(QIODevice::ReadWrite);

        fset->tim_set->stop();
        delete fset->tim_set;
    }
#endif
}

void MainWindow::on_actionStart_monitoring_triggered()
{
    if (port->isOpen()){
        if(!tim->isActive()){
            tim->start(1000); /* 1000 ms = 1 s */
            this->ui->actionStart_monitoring->setText("Stop Monitoring!");
            this->ui->actionStart_monitoring->setIcon(QIcon(":icon/icon/stop.png"));
            this->ui->actionStart_monitoring->setToolTip("Stop");

            this->ui->pb_reset->setDisabled(true);
            this->ui->actionPort_open->setDisabled(true);
        }
        else{
            tim->stop();
            this->ui->actionStart_monitoring->setText("Start Monitoring!");
            this->ui->actionStart_monitoring->setIcon(QIcon(":icon/icon/play.png"));
            this->ui->actionStart_monitoring->setToolTip("Start");

            this->ui->pb_reset->setEnabled(true);
            this->ui->actionPort_open->setEnabled(true);
        }
    }
    else{
        logs->print(this->ui->plainTextEdit, "Port Not Connected");
    }
}
