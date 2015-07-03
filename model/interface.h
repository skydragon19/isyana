#ifndef INTERFACE_H
#define INTERFACE_H

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>

class interface
{
public:
    interface();
    ~interface();

    void set_combo_port(QComboBox *cbx);
    void set_combo_baud(QComboBox *cbx);
    void set_combo_data(QComboBox *cbx);
    void set_combo_prty(QComboBox *cbx);
    void set_combo_stop(QComboBox *cbx);
    void set_combo_flow(QComboBox *cbx);

    void label_counter(QHBoxLayout *hbox, QLabel *name, QLabel *equal, QLabel *value, QString nim);
};

#endif // INTERFACE_H
