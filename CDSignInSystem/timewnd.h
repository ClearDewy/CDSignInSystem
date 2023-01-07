#ifndef TIMEWND_H
#define TIMEWND_H

#include <QWidget>
#include "sql.h"
#include <QStandardItemModel>

namespace Ui {
class TimeWnd;
}

class TimeWnd : public QWidget
{
    Q_OBJECT

public:
    explicit TimeWnd(Sql*,QWidget *parent = nullptr);
    ~TimeWnd();

private slots:
    void on_pushButton_clicked();

private:
    Ui::TimeWnd *ui;
    Sql *sql;
    QStandardItemModel *tmodel;
};

#endif // TIMEWND_H
