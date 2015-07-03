#include "log.h"

log::log()
{
    number = 0;
    buf_lay = (char *) malloc(1024);
    buf_no = (char *) malloc(1024);
}

int log::print(QPlainTextEdit *memo, char *s, ...){
    va_list args;
    int i;

    va_start (args, s);

    i = vsprintf (buf_lay, s, args);
    va_end (args);

    //sprintf(buf_no, "%d. ", number++);

    strcat(buf_lay, "\r\n");
    //strcat(buf_no, buf_lay);

    //memo->insertPlainText(buf_no);
    memo->insertPlainText(buf_lay);

    /* supaya cursor selalu menunjuk paling akhir */
    QTextCursor c =  memo->textCursor();
    c.movePosition(QTextCursor::End);
    memo->setTextCursor(c);
}
