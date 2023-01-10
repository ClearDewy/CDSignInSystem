#include "sql.h"


Sql::Sql()
{
    if(!db.isOpen()){
        db = QSqlDatabase::addDatabase("QMYSQL");   // 添加一个MySql数据库操作对象
        db.setHostName("43.142.187.104");      // 设置数据库地址
        db.setPort(1229);                       // 设置数据库端口
        db.setDatabaseName("cdsis");                // 设置数据库名称
        db.setUserName("root");
        db.setPassword("040110");
        if(!db.open()){
            qDebug("数据库连接失败");
        }
    }
    query=QSqlQuery(db);                    // 实例化操作数据库的对象
}

Sql::~Sql()
{
    db.close();
}

QByteArray Sql::matToByte(cv::Mat& cap){
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);

    stream << cap.type(); // cv::Mat type
    stream << cap.rows; // cv::Mat rows
    stream << cap.cols; // cv::Mat cols
    stream <<QByteArray::fromRawData( (const char*)cap.ptr(), cap.cols * cap.rows * cap.elemSize());
    return data;
}
cv::Mat Sql::byteToMat(QByteArray cap_byte){
    QDataStream stream(&cap_byte, QIODevice::ReadOnly);
    int matType, rows, cols;
    stream >> matType >> rows >> cols;
    QByteArray siftByte;
    stream >> siftByte;
    return cv::Mat(rows, cols, matType, (void*)siftByte.data()).clone();
}

void Sql::addFace(int Id,std::vector<cv::Mat>faces){
    for(int i=0;i<faces.size();i++){
        query.clear();
        query.prepare(QString("INSERT INTO `img`(`UserId`,`Img`,`Idx`) VALUES(%1,:Img,%2)").arg(Id).arg(i+1));
        query.bindValue(QString(":Img"),matToByte(faces[i]));
        if(query.exec()){
            // qDebug("插入图片成功");
        }else{
            qDebug("插入图片失败");return;
        }
    }
}

int Sql::getId(QString rule){
    query.clear();
    query.exec(QString("SELECT `Id` FROM `user` WHERE '%1' IN (`StuNum`, `Name`)").arg(rule));
    if(query.next()){
        return query.value("Id").toInt();
    }else{
        qDebug("查无此人");return -1;
    }
}

User Sql::getUser(int id){
    query.clear();
    query.exec(QString("SELECT * FROM `user` WHERE `Id`=%1").arg(id));
    if(query.next()){
        User user;
        user.setId(query.value("Id").toInt()).setName(query.value("Name").toString()).setMajor(query.value("Major").toString());
        return user;
    }else{
        qDebug()<<"查询用户信息失败";
    }
}

void Sql::getAllUser(QStandardItemModel&tmodel){
    query.clear();
    if(query.exec(QString("SELECT `Id`,`Name`,`StuNum`,`Major`,`IsAlive`,`StartTime` FROM `user`,`userstatus` WHERE `Id`=`UserId`"))){
        qDebug()<<"获取用户列表成功";

    }else{
        qDebug()<<"获取用户列表失败";
    }
    int idx=0;
    tmodel.setRowCount(query.size());
    while(query.next()){
        tmodel.setItem(idx,0,new QStandardItem(query.value(0).toString()));
        tmodel.setItem(idx,1,new QStandardItem(query.value(1).toString()));
        tmodel.setItem(idx,2,new QStandardItem(query.value(2).toString()));
        tmodel.setItem(idx,3,new QStandardItem(query.value(3).toString()));
        if(query.value(4).toBool()){
            tmodel.setItem(idx,4,new QStandardItem(query.value(5).toString()));
            for(int i=0;i<=4;i++){
                tmodel.item(idx,i)->setBackground(QColor(Qt::green));
            }
        }else{
            tmodel.setItem(idx,4,new QStandardItem("未打卡"));
        }
        idx++;
    }
}

std::vector<int>Sql::getRecent(int n){
    query.clear();
    std::vector<int>da(n+1);
    query.exec(QString("SELECT date_format(`EndTime`, '%Y-%m-%d') dif,COUNT(DISTINCT(`UserId`)) FROM `record` WHERE DATEDIFF(`EndTime`,NOW()) BETWEEN -%1 AND 0 GROUP BY dif").arg(n));
    while (query.next()) {
       QDateTime datetime=query.value(0).toDateTime();
       da[datetime.daysTo(QDateTime::currentDateTime())]=query.value(1).toInt();
    }
    return da;
}

void Sql::getCountTime(QStandardItemModel&tmodel,QDateTime startTime,QDateTime endTime){
    query.clear();
    query.prepare(QString("SELECT Id,Name,StuNum,SUM(Time) AS Time FROM user,record WHERE UserId=user.Id AND EndTime BETWEEN :StartDate AND :EndDate GROUP BY record.UserId ORDER BY Time DESC,UserId"));
    query.bindValue(":StartDate",startTime);
    query.bindValue(":EndDate",endTime);
    if(query.exec()){
        int idx=0;
        tmodel.setRowCount(query.size());
        while(query.next()){
            tmodel.setItem(idx,0,new QStandardItem(query.value(0).toString()));
            tmodel.setItem(idx,1,new QStandardItem(query.value(1).toString()));
            tmodel.setItem(idx,2,new QStandardItem(query.value(2).toString()));
            tmodel.setItem(idx,3,new QStandardItem(query.value(3).toString()));
            idx++;
        }
    }else{
        qDebug()<<"查询失败";
    }
}

int Sql::getTotleUserNum()
{
    query.clear();
    query.exec(QString("SELECT COUNT(*) FROM `userstatus`"));
    query.next();
    return query.value(0).toInt();
}
int Sql::getAliveUserNum()
{
    query.clear();
    query.exec(QString("SELECT COUNT(*) FROM `userstatus` WHERE `IsAlive`=TRUE"));
    query.next();
    return query.value(0).toInt();
}

void Sql::addUser(User user){
    query.clear();
    if(query.exec(QString("INSERT INTO `user`(`Name`,`StuNum`,`Major`) VALUES ('%1','%2','%3')").arg(user.getName()).arg(user.getStuNum()).arg(user.getMajor()))){
        user.setId(query.lastInsertId().toInt());       // 获取用户在用户列表的Id
        query.clear();query.exec(QString("INSERT INTO `userstatus`(`UserId`,`IsAlive`) VALUES (%1,FALSE)").arg(user.getId()));    // 添加用户状态记录
        addFace(user.getId(),user.getFaces());
        qDebug()<<"添加用户成功";
    }else{
        qDebug()<<"添加用户失败";
    }
}

void Sql::deleteUser(int id){
    query.clear();
    if(query.exec(QString("DELETE from `user` WHERE `Id` = %1").arg(id))){
        qDebug("删除用户成功");
    }else{
        qDebug("删除用户失败");
    }
}

void Sql::updateUser(User user){
    query.clear();
    if(query.exec(QString("UPDATE `user` SET `Name`='%1',`StuNum`='%2',`Major`='%3' WHERE `Id`='%4'").arg(user.getName()).arg(user.getStuNum()).arg(user.getMajor()).arg(user.getId()))){
        std::vector<cv::Mat>faces=user.getFaces();
        for(int i=0;i<faces.size();i++){
            query.clear();
            query.prepare(QString("UPDATE `img` SET `Img`=:Img WHERE `UserId`=%1 AND `Idx`=%2").arg(user.getId()).arg(i+1));
            query.bindValue(":Img",matToByte(faces[i]));
            if(query.exec()){

            }else{
                qDebug()<<"更新用户信息失败";return;
            }
        }
    }else{
        qDebug()<<"更新用户信息失败";
    }
}

void Sql::updateModleXML(QByteArray xml){
    query.clear();
    if(query.exec(QString("UPDATE `model` SET `data` = '%1'").arg(xml))){
        qDebug()<<"模型文件更新成功";
    }else{
        QSqlError err=query.lastError();
        qDebug()<<err.text();
        qDebug()<<"模型文件更新失败";
    }
}

QByteArray Sql::getModelXML(){
    query.clear();
    query.exec(QString("SELECT * FROM `model`"));
    if(query.next()){
        return query.value("data").toByteArray();
    }else{
        qDebug("获取XML文件失败");
    }
    return QByteArray();
}




void Sql::getAllFaces(std::vector<cv::Mat>&faces,std::vector<int>&lable){
    query.clear();
    if(query.exec(QString("SELECT * FROM `img`"))){
        while(query.next()){
            faces.push_back(byteToMat(query.value("Img").toByteArray()));
            lable.push_back(query.value("UserId").toInt());
        }
        qDebug("获取图片成功");
    }else{
        qDebug("获取图片失败");
    }
}

bool Sql::logIn(QString username,QString password){
    query.clear();
    if(query.exec(QString("SELECT * FROM `admin` WHERE `Username`='%1' AND `Password`='%2'").arg(username).arg(password))){
        return query.size();
    }else{
        qDebug()<<"账号密码查询失败";
        return false;
    }
}

bool Sql::signIn(int id){
    query.clear();
    if(query.exec(QString("SELECT `IsAlive`,`StartTime` FROM `userstatus` WHERE `UserId`=%1").arg(id))){
        query.next();
        if(!query.value(0).toBool()){
            query.clear();
            query.exec(QString("UPDATE `userstatus` SET `IsAlive`=true,`StartTime`=now() WHERE UserId=%1").arg(id));
            return 1;
        }else{
            QDateTime starttime=query.value(1).toDateTime();
            query.clear();
            query.prepare("INSERT `record`(`UserId`,`StartTime`,`EndTime`,`Time`) VALUES (:UserId,:StartTime,now(),(UNIX_TIMESTAMP(now())-UNIX_TIMESTAMP(:StartTime))/3600)");
            query.bindValue(":UserId",id);
            query.bindValue(":StartTime",starttime);
            query.exec();
            query.clear();
            query.exec(QString("UPDATE `userstatus` SET `IsAlive`=false,`StartTime`=null WHERE UserId=%1").arg(id));
            return 0;
        }
    }else{
        qDebug("打卡失败");
    }
}
