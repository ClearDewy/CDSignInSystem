#include "user.h"

User::User()
{
    Id=-1;
}

int User::getId(){
    return Id;
}
User& User::setId(int id){
    Id=id;
    return *this;
}
QString User::getName(){
    return Name;
}
QString User::getStuNum(){
    return StuNum;
}
QString User::getMajor(){
    return Major;
}
User& User::setName(QString name){
    Name=name;
    return *this;
}
User& User::setStuNum(QString stuNum){
    StuNum=stuNum;
    return *this;
}
User& User::setMajor(QString major){
    Major=major;
    return *this;
}
QDateTime User::getStartTime(){
    return StartTime;
}
User& User::setStartTime(QDateTime startTime){
    StartTime=startTime;
    return *this;
}
std::vector<cv::Mat>User::getFaces(){
    return Faces;
}
User& User::addFace(cv::Mat cap){
    Faces.push_back(cap);
    return *this;
}
User& User::setFaces(std::vector<cv::Mat>faces){
    Faces=faces;
    return *this;
}
int User::getPicNum(){
    return Faces.size();
}
