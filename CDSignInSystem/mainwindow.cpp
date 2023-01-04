#include "ui_mainwindow.h"
#include "mainwindow.h"
//时间显示
#include <QFont>
#include <QTime>
#include <QTimer>
#include <qdatetime.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cancelButton->hide();
    timer=new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  // 时间到，读取当前摄像头信息

    //时间显示
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdata()));
    timer->start(1000);

    //videoLable大小更改
    QImage img1("1.png");
    img1 = img1.scaled(ui->videoLable->width(), ui->videoLable->height());//图片大小设置，与videoLable大小适配
    ui->videoLable->setPixmap(QPixmap::fromImage(img1));
    //Frame1大小更改
    QImage img2("2.png");
    img2 = img2.scaled(ui->Frame1->width(), ui->Frame1->height());//图片大小设置，与Frame1大小适配
    ui->Frame1->setPixmap(QPixmap::fromImage(img2));


    //加载分类训练器，OpenCv官方文档提供的xml文档，可以直接调用
    //xml文档路径，  opencv\sources\data\haarcascades

    if (!face_cascade.load(FACE_XML_PATH))
    {
        qDebug("Load haarcascade_frontalface_alt failed!");
    }
    QFile f(FACE_CLASSIFIER_PATH);
    f.open(QIODevice::WriteOnly);
    f.write(sql.getModelXML());
    f.close();
    model->read(FACE_CLASSIFIER_PATH);      // 加载训练后的xml文件
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}


void MainWindow::on_LogIn_clicked()
{
    LogIn logIn(this);    // 登录对话框
    if(logIn.exec()==QDialog::Accepted){
        Backend *backend=new Backend;
        this->close();
        backend->show();
    }else{

    }
}


void MainWindow::readFarme()
{
    if(!capture.isOpened()){
        qDebug("摄像头未打开");
        return;
    }
    capture>>cap;
    if (!cap.empty()) //判断当前帧是否捕捉成功 **这步很重要
    {
        cvtColor(cap, cap_gray, CV_BGR2GRAY);//转为灰度图
        equalizeHist(cap_gray, cap_gray);//直方图均衡化，增加对比度方便处理

        //检测关于脸部位置
        face_cascade.detectMultiScale(cap_gray, faceRect, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(92, 112));//检测

        for (size_t i = 0; i < faceRect.size(); i++)
        {
            rectangle(cap, faceRect[i], cv::Scalar(0, 255, 0));      //用绿色矩形画出检测到的位置
        }


        imag = Mat2QImage(cap);
        imag = imag.scaled(ui->videoLable->width(), ui->videoLable->height(),
                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//设置图片大小和label的长宽一致

        //imshow(name, cap); //若当前帧捕捉成功，显示
        ui->videoLable->setPixmap(QPixmap::fromImage(imag));  // 将图片显示到label上
        // qDebug("图片捕捉成功");
        predict=Predict();
        if(predict){
            timer->stop();
            ui->SignIn->setEnabled(true);
            ui->cancelButton->hide();
            if(QMessageBox::question(this,"打卡确认",tr("用户：%1 是否打卡？").arg(sql.getUser(predict).getName()))==QMessageBox::Ok){

            }
        }
    }
    else
    {
        qDebug("图片捕捉失败");

    }
}

int MainWindow::Predict(){
    if(faceRect.size()!=1){

        return 0;
    }
    int predict = 0;
    if (cap_gray.rows >= 120)
    {
        //改变图像大小，使用双线性差值
        cv::resize(cap_gray, cap_tmp, cv::Size(92, 112));
    }
    //判断是否正确检测ROI
    if (!cap_tmp.empty())
    {
        //测试图像应该是灰度图
        predict = model->predict(cap_tmp);
    }
    qDebug("predict:%d",predict);
    return predict;
}

void MainWindow::on_SignIn_clicked()
{
    ui->cancelButton->show();
    ui->SignIn->setEnabled(false);
    OpenCamara();   // 打开摄像头
    predict=0;
    timer->start(TIME_INTERVAL);
}



// 图片转换
QImage  MainWindow::Mat2QImage(cv::Mat cvImg)
{
    QImage qImg;
    if(cvImg.channels()==3)     //3 channels color image
    {
        cv::cvtColor(cvImg,cvImg,CV_BGR2RGB);
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols, cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888);
    }
    else if(cvImg.channels()==1)                    //grayscale image
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_Indexed8);
    }
    else
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888);
    }
    return qImg;
}


bool MainWindow::OpenCamara()
{
    if(capture.isOpened())return true;
    capture.open(0);
    qDebug("打开摄像头");
    return capture.isOpened();
}
void MainWindow::on_cancelButton_clicked()
{
    // timer->stop();
    capture.release();
}

void MainWindow::timerUpdata()
{
    QFont font("Microsoft YaHei",10,50);
    //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75）
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    QString str1 = time.toString("yyyy-MM-dd hh:mm:ss");
    ui -> Time ->setFont(font);
    this -> ui->Time->setText(str);
    //ui->text->show();
}
