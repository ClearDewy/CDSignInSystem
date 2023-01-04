#include "backend.h"
#include "ui_backend.h"
#include "MainWindow.h"

Backend::Backend(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Backend)
{
    ui->setupUi(this);
}

Backend::~Backend()
{
    delete ui;
}

void Backend::startTrain(){
    train tra;
    std::vector<cv::Mat>faces;
    std::vector<int>lables;
    sql.getAllFaces(faces,lables);
    tra.run(faces,lables);
    QFile f(FACE_CLASSIFIER_PATH);
    f.open(QIODevice::ReadOnly);
    sql.updateModleXML(f.readAll());
    f.close();
}

void Backend::on_LogOut_clicked()
{
    MainWindow *w=new MainWindow;
    this->close();
    w->show();
}


void Backend::on_addButton_clicked()
{
    GetData G(this);
    G.show();
    if(G.exec()==QDialog::Accepted){
        updateUserList.push_back(G.getUserData());
    }else{
        qDebug()<<"用户信息取消";
    }
}


void Backend::on_saveButton_clicked()
{
    for(User&i:updateUserList){
        if(i.getId()==-1) sql.addUser(i);   // 不存在用户则添加
        else sql.updateUser(i);
    }
    startTrain();
}

