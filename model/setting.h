#ifndef SETTING_H
#define SETTING_H

#include <QSettings>

#include <util/core.h>

class Setting
{
public:
    Setting();
    ~Setting();

    void read(struct ser_kom *skom);
    void write(struct ser_kom *skom);
};

#endif // SETTING_H
