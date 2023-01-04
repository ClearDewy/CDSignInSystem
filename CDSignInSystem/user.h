#ifndef USER_H
#define USER_H

#include <QString>
#include <qdatetime.h>
#include <opencv2/opencv.hpp>
#include <iostream>

class User
{
public:
    User();
    int getId();
    User& setId(int);
    QString getName();
    QString getStuNum();
    QString getMajor();
    User& setName(QString);
    User& setStuNum(QString);
    User& setMajor(QString);
    QDateTime getStartTime();
    User& setStartTime(QDateTime);
    std::vector<cv::Mat>getFaces();
    User& addFace(cv::Mat);
    User& setFaces(std::vector<cv::Mat>);
    int getPicNum();


private:
    int Id;
    QString Name;
    QString StuNum;
    QString Major;
    QDateTime StartTime;
    std::vector<cv::Mat>Faces;
};

#endif // USER_H
