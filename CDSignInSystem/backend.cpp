#include "backend.h"
#include "ui_backend.h"
#include "MainWindow.h"

Backend::Backend(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Backend)
{
    ui->setupUi(this);
    tmodel.setColumnCount(5);
    tmodel.setHeaderData(0,Qt::Horizontal,"Id");
    tmodel.setHeaderData(1,Qt::Horizontal,"姓名");
    tmodel.setHeaderData(2,Qt::Horizontal,"学号");
    tmodel.setHeaderData(3,Qt::Horizontal,"专业");
    tmodel.setHeaderData(4,Qt::Horizontal,"打卡时间");
    sql.getAllUser(tmodel);
    ui->userView->setModel(&tmodel);
    ui->userView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
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
        User user=G.getUserData();
        updateUserList.push_back(user);
        int idx=0;
        for(int idx=0;idx<tmodel.rowCount();idx++){
            if(tmodel.data(tmodel.index(idx,2)).toString()>user.getStuNum())break;
        }

        QList<QStandardItem*> list;
        list << new QStandardItem(QString::number(user.getId())) << new QStandardItem(user.getName()) <<new QStandardItem(user.getStuNum())<< new QStandardItem(user.getMajor())<< new QStandardItem("未打卡");
        tmodel.insertRow(idx, list);
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
    for(int &i:deleteUserIdList){
        qDebug()<<i;
        sql.deleteUser(i);
    }
    startTrain();
}


void Backend::on_updateUserButton_clicked()
{
    int row= ui->userView->currentIndex().row();
    User user;
    user.setId(tmodel.data(tmodel.index(row,0)).toInt()).setName(tmodel.data(tmodel.index(row,1)).toString()).setStuNum(tmodel.data(tmodel.index(row,2)).toString()).setMajor(tmodel.data(tmodel.index(row,3)).toString());
    GetData G(user);
    G.show();
    if(G.exec()==QDialog::Accepted){
        user=G.getUserData();
        updateUserList.push_back(user);
        tmodel.setItem(row,1,new QStandardItem(user.getName()));
        tmodel.setItem(row,2,new QStandardItem(user.getStuNum()));
        tmodel.setItem(row,3,new QStandardItem(user.getMajor()));
    }else{
        qDebug()<<"用户信息取消";
    }
}


void Backend::on_deleteUserButton_clicked()
{
    int row= ui->userView->currentIndex().row();
    deleteUserIdList.push_back(tmodel.data(tmodel.index(row,0)).toInt());
    tmodel.removeRow(row);
}

