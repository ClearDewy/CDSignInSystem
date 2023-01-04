#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/face.hpp>
// #include <opencv2/face/facerec.hpp>
#include <iostream>
#include "logIn.h"
#include "backend.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_LogIn_clicked();

    void on_SignIn_clicked();

    void on_cancelButton_clicked();
    void readFarme();       // 获取摄像头每一帧

protected:
    QImage Mat2QImage(cv::Mat cvImg);       //图片转换
    bool OpenCamara();      // 打开摄像头
    bool CloseCamara();     // 关闭摄像头

    int Predict();          // 根据cap识别具体人物

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QImage imag;
    cv::Mat cap,cap_gray,cap_tmp; //定义一个Mat变量，用于存储每一帧的图像
    cv::VideoCapture capture;       // 声明视频读入类
    cv::CascadeClassifier face_cascade;    //载入分类器
    std::vector<cv::Rect> faceRect;
    int predict=0;

    cv::Ptr<cv::face::FaceRecognizer> model = cv::face::EigenFaceRecognizer::create();      // 人脸分类器，检测是谁
    Sql sql;
};
#endif // MAINWINDOW_H
