#include "login.h"
#include "ui_login.h"

LogIn::LogIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);
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

