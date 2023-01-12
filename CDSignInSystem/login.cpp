#include "login.h"
#include "ui_login.h"

LogIn::LogIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);

    //背景设计
    dragPosition = new QPoint;
    this->setFixedSize(QSize(668,400));
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    ui->widget->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->closeButton->setIcon(QIcon(":new/Img/close.png"));
    ui->minSizeButton->setIcon(QIcon(":new/Img/remove.png"));
    ui->closeButton->setIconSize(QSize(20,20));
    ui->minSizeButton->setIconSize(QSize(20,20));

    //LineEdit前标识符添加
    QAction* userAction = new QAction(ui->usernameEdit);//新建action
    QAction* passwordAction = new QAction(ui->passwordEdit);
    userAction->setIcon(QIcon(":/new/Img/people_number.png"));//给action添加icon
    passwordAction->setIcon(QIcon(":/new/Img/password.png"));
    ui->usernameEdit->addAction(userAction,QLineEdit::LeadingPosition);//给空间添加action
    ui->passwordEdit->addAction(passwordAction,QLineEdit::LeadingPosition);

    //LineEdit信息删除
    ui->usernameEdit->setClearButtonEnabled(true);
    ui->passwordEdit->setClearButtonEnabled(true);

    connect(ui->minSizeButton,&QToolButton::clicked,this,&QDialog::showMinimized);
    connect(ui->closeButton,&QToolButton::clicked,this,&QDialog::close);


}

LogIn::~LogIn()
{
    delete ui;
}

void LogIn::on_confirmButton_clicked()
{
    if(sql.logIn(ui->usernameEdit->text(),ui->passwordEdit->text())){
        accept();
    }else{
        qDebug("用户名或密码错误");
        ui->logInMessage->setText("用户名或密码错误");
    }
}





void LogIn::on_concelButton_clicked()
{
    close();
}

void LogIn::mousePressEvent(QMouseEvent *event) {

    if (event->button() == Qt::LeftButton) {

        *dragPosition = event->globalPos() - frameGeometry().topLeft();

        event->accept();

    }

}

void LogIn::mouseMoveEvent(QMouseEvent *event) {

    if (event->buttons() & Qt::LeftButton) {

        move(event->globalPos() - *dragPosition);

        event->accept();

    }
}

