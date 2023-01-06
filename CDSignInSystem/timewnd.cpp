#include "timewnd.h"
#include "ui_timewnd.h"

TimeWnd::TimeWnd(Sql*s,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeWnd)
{
    ui->setupUi(this);
    sql=s;
}

TimeWnd::~TimeWnd()
{
    delete ui;
}
