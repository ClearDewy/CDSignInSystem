#include "timewnd.h"
#include "ui_timewnd.h"

TimeWnd::TimeWnd(Sql*s,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeWnd)
{
    ui->setupUi(this);
    sql=s;
    tmodel=new QStandardItemModel;
    tmodel->setColumnCount(4);
    tmodel->setHeaderData(0,Qt::Horizontal,"Id");
    tmodel->setHeaderData(1,Qt::Horizontal,"姓名");
    tmodel->setHeaderData(2,Qt::Horizontal,"学号");
    tmodel->setHeaderData(3,Qt::Horizontal,"时长/h");
    ui->timeView->setModel(tmodel);
    ui->timeView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

TimeWnd::~TimeWnd()
{
    delete ui;
}

void TimeWnd::on_pushButton_clicked()
{
    sql->getCountTime(*tmodel,ui->startTimeEdit->dateTime(),ui->endTimeEdit->dateTime());
}

