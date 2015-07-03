#include "setting.h"

Setting::Setting()
{
}

Setting::~Setting()
{
}

void Setting::write(ser_kom *skom){
    QString pth = "config.ini";
    QSettings sett(pth, QSettings::IniFormat);

    QByteArray BA((char *) skom, sizeof (struct ser_kom));
    sett.setValue("global", BA);
}

void Setting::read(ser_kom *skom){
    QString pth = "config.ini";
    QSettings sett(pth, QSettings::IniFormat);

    memcpy( skom, (void *) sett.value("global").toByteArray().data(), sizeof (struct ser_kom));
}

