#ifndef SQL_H
#define SQL_H
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include "user.h"
#include <QSqlError>
#include <QDataStream>
#include <QIODevice>
#include <QStandardItemModel>
#include <qdatetime.h>

class Sql
{
public:
    Sql();
    ~Sql();
    void addUser(User);
    void updateUser(User);
    int getId(QString);
    void deleteUser(int);
    QByteArray getModelXML();
    void updateModleXML(QByteArray);
    void getAllFaces(std::vector<cv::Mat>&,std::vector<int>&);
    bool logIn(QString,QString);
    User getUser(int);
    void getAllUser(QStandardItemModel&);
    void getCountTime(QStandardItemModel&,QDateTime,QDateTime);
    bool signIn(int);
    int getTotleUserNum();
    int getAliveUserNum();
protected:
    void addFace(int,std::vector<cv::Mat>);
    QByteArray matToByte(cv::Mat&);
    cv::Mat byteToMat(QByteArray);

private:
    QSqlDatabase db;
    QSqlQuery query;
};

#endif // SQL_H
