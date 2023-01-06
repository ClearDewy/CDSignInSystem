#include "userwnd.h"
#include "ui_userwnd.h"

UserWnd::UserWnd(Sql*s,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWnd)
{
    ui->setupUi(this);
    sql=s;
    tmodel.setColumnCount(5);
    tmodel.setHeaderData(0,Qt::Horizontal,"Id");
    tmodel.setHeaderData(1,Qt::Horizontal,"姓名");
    tmodel.setHeaderData(2,Qt::Horizontal,"学号");
    tmodel.setHeaderData(3,Qt::Horizontal,"专业");
    tmodel.setHeaderData(4,Qt::Horizontal,"打卡时间");
    sql->getAllUser(tmodel);

    ui->userView->setModel(&tmodel);
    ui->userView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //按钮
    ui->deleteUserButton->setIcon(QIcon(":/new/Img/1.png"));
    ui->deleteUserButton->setLayoutDirection(Qt::LeftToRight);
    ui->addButton->setIcon(QIcon(":/new/Img/2.png"));
    ui->addButton->setLayoutDirection(Qt::LeftToRight);
    ui->updateUserButton->setIcon(QIcon(":/new/Img/3.png"));
    ui->updateUserButton->setLayoutDirection(Qt::LeftToRight);
    ui->saveButton->setIcon(QIcon(":/new/Img/Icon_download.png"));
    ui->saveButton->setLayoutDirection(Qt::LeftToRight);
}

UserWnd::~UserWnd()
{
    delete ui;
}

void UserWnd::startTrain(){
    train tra;
    std::vector<cv::Mat>faces;
    std::vector<int>lables;
    sql->getAllFaces(faces,lables);
    tra.run(faces,lables);
    QFile f(FACE_CLASSIFIER_PATH);
    f.open(QIODevice::ReadOnly);
    sql->updateModleXML(f.readAll());
    f.close();
}

void UserWnd::on_addButton_clicked()
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


void UserWnd::on_saveButton_clicked()
{
    for(User&i:updateUserList){
        if(i.getId()==-1) sql->addUser(i);   // 不存在用户则添加
        else sql->updateUser(i);
    }
    for(int &i:deleteUserIdList){
        qDebug()<<i;
        sql->deleteUser(i);
    }
    startTrain();
}


void UserWnd::on_updateUserButton_clicked()
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


void UserWnd::on_deleteUserButton_clicked()
{
    int row= ui->userView->currentIndex().row();
    deleteUserIdList.push_back(tmodel.data(tmodel.index(row,0)).toInt());
    tmodel.removeRow(row);
}
