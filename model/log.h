#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <QPlainTextEdit>

class log
{
public:
    log();

    int print(QPlainTextEdit *memo, char *s, ...);

private:
    int number;

    char *buf_lay;
    char *buf_no;
};

#endif // LOG_H
