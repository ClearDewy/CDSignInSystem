#ifndef SQL_H
#define SQL_H
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include "user.h"
#include <QSqlError>
#include <QDataStream>
#include <QIODevice>

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
protected:
    void addFace(int,std::vector<cv::Mat>);
    QByteArray matToByte(cv::Mat&);
    cv::Mat byteToMat(QByteArray);

private:
    QSqlDatabase db;
    QSqlQuery query;
};

#endif // SQL_H
