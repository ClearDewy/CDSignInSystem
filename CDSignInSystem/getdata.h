#ifndef GETDATA_H
#define GETDATA_H

#include <QDialog>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/face.hpp>
#include <fstream>
#include <qtimer.h>
#include "user.h"

#define TIME_INTERVAL 20        //获取摄像头图片间隔
#define FACE_XML_PATH "D:\\Environment\\OpenCV\\etc\\haarcascades\\haarcascade_frontalface_alt.xml"     //face模型位置
#define FACE_PHOTOS_NUM 10                      //训练模型的图片张数
#define IMG_PATH "D:\\ClearDewy-Code\\QTCode\\Study\\img\\"                             // 图片位置
#define CSV_PATH "data.txt"
#define SEPARATOR ';'

namespace Ui {
class GetData;
}

class GetData : public QDialog
{
    Q_OBJECT

public:
    explicit GetData(QWidget *parent = nullptr);
    explicit GetData(User,QWidget *parent = nullptr);
    ~GetData();
    User getUserData();

private slots:
    void on_startButton_clicked();

    void on_cancelButton_clicked();

    void on_sureButton_clicked();

    bool get_pic();

protected:
    QImage Mat2QImage(cv::Mat cvImg);       //图片转换
    bool OpenCamara();      // 打开摄像头
    bool CloseCamara();     // 关闭摄像头
    bool TakePhotos();      // 拍照
    bool readFarme();       // 获取摄像头每一帧


private:
    Ui::GetData *ui;
    QTimer *timer;
    QImage imag;
    cv::Mat cap,cap_gray,cap_tmp; //定义一个Mat变量，用于存储每一帧的图像
    cv::VideoCapture capture;       // 声明视频读入类
    cv::CascadeClassifier face_cascade;    //载入分类器
    std::vector<cv::Rect> faceRect;
    // cv::Ptr<cv::face::FaceRecognizer> model = cv::face::EigenFaceRecognizer::create();      // 人脸分类器，检测是谁
    User user;
    QPixmap *pixmap;
};

#endif // GETDATA_H
