#include "backend.h"
#include "ui_backend.h"
#include "MainWindow.h"

Backend::Backend(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Backend)
{
    ui->setupUi(this);
    // 变量分配
    sql=new Sql;
    btnGroup=new QButtonGroup(this);
    homeWnd=new HomeWnd(sql);
    userWnd=new UserWnd(sql);
    timeWnd=new TimeWnd(sql);
    accountWnd=new AccountWnd(sql);


    // 样式设置
    ui->LogOut->setIcon(QIcon(":/new/Img/4.png"));
    ui->LogOut->setLayoutDirection(Qt::LeftToRight);


    // 初始化
    btnGroup->addButton(ui->homeButton,2);
    btnGroup->addButton(ui->userButton,3);
    btnGroup->addButton(ui->timeButton,4);
    btnGroup->addButton(ui->accountButton,5);

    ui->stackedWidget->addWidget(homeWnd);
    ui->stackedWidget->addWidget(userWnd);
    ui->stackedWidget->addWidget(timeWnd);
    ui->stackedWidget->addWidget(accountWnd);


    connect(btnGroup,QOverload<int>::of(&QButtonGroup::idClicked), ui->stackedWidget, &QStackedWidget::setCurrentIndex);
    // 设置默认选中的页面
    btnGroup->button(2)->setChecked(true);
    ui->stackedWidget->setCurrentIndex(2);
}


Backend::~Backend()
{
    delete ui;
}



void Backend::on_LogOut_clicked()
{
    MainWindow *w=new MainWindow;
    this->close();
    w->show();
}




