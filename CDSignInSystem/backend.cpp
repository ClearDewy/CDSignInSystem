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
    dragPosition = new QPoint;

    // 样式设置
    ui->LogOut->setIcon(QIcon(":/new/Img/4.png"));
    ui->LogOut->setLayoutDirection(Qt::LeftToRight);
    this->setFixedSize(1000,600);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->closeButton->setIcon(QIcon(":new/Img/close.png"));
    ui->minSizeButton->setIcon(QIcon(":new/Img/remove.png"));
    ui->closeButton->setIconSize(QSize(20,20));
    ui->minSizeButton->setIconSize(QSize(20,20));
    ui->closeButton->setGeometry(QRect(950, 20, 26, 30));
    ui->minSizeButton->setGeometry(QRect(920, 20, 26, 30));

    //滑动图标大小
    ui->homeButton->setIcon(QIcon(":/new/Img/home.png"));
    ui->homeButton->setIconSize(QSize(38,38));
    ui->userButton->setIcon(QIcon(":/new/Img/user.png"));
    ui->userButton->setIconSize(QSize(38,38));
    ui->timeButton->setIcon(QIcon(":/new/Img/time.png"));
    ui->timeButton->setIconSize(QSize(38,38));
    ui->accountButton->setIcon(QIcon(":/new/Img/root-list.png"));
    ui->accountButton->setIconSize(QSize(38,38));


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
    connect(ui->minSizeButton,&QToolButton::clicked,this,&QMainWindow::showMinimized);
    connect(ui->closeButton,&QToolButton::clicked,this,&QMainWindow::close);
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


void Backend::mousePressEvent(QMouseEvent *event) {

    if (event->button() == Qt::LeftButton) {

        *dragPosition = event->globalPos() - frameGeometry().topLeft();

        event->accept();

    }

}

void Backend::mouseMoveEvent(QMouseEvent *event) {

    if (event->buttons() & Qt::LeftButton) {

        move(event->globalPos() - *dragPosition);

        event->accept();

    }
 }

