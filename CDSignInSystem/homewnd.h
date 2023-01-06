#ifndef HOMEWND_H
#define HOMEWND_H

#include <QWidget>
#include "sql.h"

namespace Ui {
class HomeWnd;
}

class HomeWnd : public QWidget
{
    Q_OBJECT

public:
    explicit HomeWnd(Sql*,QWidget *parent = nullptr);
    ~HomeWnd();

private:
    Ui::HomeWnd *ui;
    Sql *sql;
};

#endif // HOMEWND_H
