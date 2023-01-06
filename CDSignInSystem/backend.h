#ifndef BACKEND_H
#define BACKEND_H

#include <QMainWindow>
#include <QButtonGroup>

#include "homewnd.h"
#include "userwnd.h"
#include "timewnd.h"
#include "accountwnd.h"

namespace Ui {
class Backend;
}

class Backend : public QMainWindow
{
    Q_OBJECT

public:
    explicit Backend(QWidget *parent = nullptr);
    ~Backend();

protected:


private slots:
    void on_LogOut_clicked();


private:
    Ui::Backend *ui;
    Sql *sql;
    QButtonGroup *btnGroup;
    HomeWnd *homeWnd;
    UserWnd *userWnd;
    TimeWnd *timeWnd;
    AccountWnd *accountWnd;
};

#endif // BACKEND_H
