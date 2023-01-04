#ifndef TRAIN_H
#define TRAIN_H


#include <opencv2/face.hpp>
#include <QThread>
#include <QMessageBox>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <QDebug>
#include <opencv2\opencv.hpp>
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <math.h>
#include <fstream>
#include <sstream>
#include <getdata.h>


#define FACE_CLASSIFIER_PATH "MyFace.xml"       //face分类器位置

class train:public QThread
{
    Q_OBJECT
signals:
    void finished();
public:
    explicit train(QObject *parent = nullptr);
    ~train();
    void run(std::vector<cv::Mat>&,std::vector<int>&);
protected:

};

#endif // TRAIN_H
