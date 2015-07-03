#ifndef PORT_PROCESSING_H
#define PORT_PROCESSING_H

#include "util/core.h"

/* model */
#include "model/setting.h"
#include "model/interface.h"

/* view */
#include "view/form_setting_port.h"
#include "ui_form_setting_port.h"

class port_processing
{
public:
    port_processing();
    ~port_processing();

    /* class */
    Setting set;
    interface iface;

    int x;
    void set_setting_value(form_setting_port *fport, struct ser_kom *skom);
    void get_setting_value(struct ser_kom *skom);
    void apply_setting_value(form_setting_port *fport, struct ser_kom *skom);
    void build_interface(form_setting_port *fport, struct ser_kom *skom);
};

#endif // PORT_PROCESSING_H
