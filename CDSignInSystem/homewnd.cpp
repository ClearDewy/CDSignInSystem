#include "homewnd.h"
#include "ui_homewnd.h"

HomeWnd::HomeWnd(Sql*s,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeWnd)
{
    ui->setupUi(this);
    sql=s;
}

HomeWnd::~HomeWnd()
{
    delete ui;
}
