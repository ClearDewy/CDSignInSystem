#include "accountwnd.h"
#include "ui_accountwnd.h"

AccountWnd::AccountWnd(Sql*s,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountWnd)
{
    ui->setupUi(this);
    sql=s;
    tmodel=new QSqlTableModel;
    tmodel->setTable("admin");
    tmodel->select();
    ui->accountView->setModel(tmodel);
    ui->accountView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //按钮
    ui->deleteUserButton->setIcon(QIcon(":/new/Img/1.png"));
    ui->deleteUserButton->setLayoutDirection(Qt::LeftToRight);
    ui->addButton->setIcon(QIcon(":/new/Img/2.png"));
    ui->addButton->setLayoutDirection(Qt::LeftToRight);
    ui->saveButton->setIcon(QIcon(":/new/Img/Icon_download.png"));
    ui->saveButton->setLayoutDirection(Qt::LeftToRight);
}

AccountWnd::~AccountWnd()
{
    delete ui;
}

void AccountWnd::on_addButton_clicked()
{
    tmodel->insertRow(tmodel->rowCount()); //添加一行
}


void AccountWnd::on_deleteUserButton_clicked()
{
    tmodel->removeRow(ui->accountView->currentIndex().row());
}


void AccountWnd::on_saveButton_clicked()
{
    tmodel->database().transaction(); //开始事务操作
            if (tmodel->submitAll()) {
                tmodel->database().commit(); //提交
            } else {
                tmodel->database().rollback(); //回滚
                QMessageBox::warning(this, tr("tabletmodel"),
                                     tr("数据库错误: %1")
                                     .arg(tmodel->lastError().text()));
            }
}

