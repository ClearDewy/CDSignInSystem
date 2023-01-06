#include "accountwnd.h"
#include "ui_accountwnd.h"

AccountWnd::AccountWnd(Sql*s,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountWnd)
{
    ui->setupUi(this);
    sql=s;
}

AccountWnd::~AccountWnd()
{
    delete ui;
}
