#ifndef TIMEWND_H
#define TIMEWND_H

#include <QWidget>
#include "sql.h"

namespace Ui {
class TimeWnd;
}

class TimeWnd : public QWidget
{
    Q_OBJECT

public:
    explicit TimeWnd(Sql*,QWidget *parent = nullptr);
    ~TimeWnd();

private:
    Ui::TimeWnd *ui;
    Sql *sql;
};

#endif // TIMEWND_H
