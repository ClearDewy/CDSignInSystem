#include "login.h"
#include "ui_login.h"

LogIn::LogIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);


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

