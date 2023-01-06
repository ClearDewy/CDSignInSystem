#ifndef ACCOUNTWND_H
#define ACCOUNTWND_H

#include <QWidget>
#include "sql.h"

namespace Ui {
class AccountWnd;
}

class AccountWnd : public QWidget
{
    Q_OBJECT

public:
    explicit AccountWnd(Sql*,QWidget *parent = nullptr);
    ~AccountWnd();

private:
    Ui::AccountWnd *ui;
    Sql *sql;
};

#endif // ACCOUNTWND_H
