#include "getdata.h"
#include "ui_getdata.h"


GetData::GetData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetData)
{
    ui->setupUi(this);
    timer=new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(get_pic()));  // 时间到，读取当前摄像头信息

    //videoLable大小更改
    pixmap = new QPixmap(":/new/Img/face.png");
    pixmap->scaled(ui->videoLable->size(), Qt::KeepAspectRatio);
    ui->videoLable->setScaledContents(true);
    ui->videoLable->setPixmap(*pixmap);
    ui->cancelButton->hide();

    ui->sureButton->setEnabled(false);
    //加载分类训练器，OpenCv官方文档提供的xml文档，可以直接调用
    //xml文档路径，  opencv\sources\data\haarcascades

    //LineEdit信息删除
    ui->nameEdit->setClearButtonEnabled(true);
    ui->stuNumEdit->setClearButtonEnabled(true);
    ui->majorEdit->setClearButtonEnabled(true);




    if (!face_cascade.load(FACE_XML_PATH))
    {
        qDebug("Load haarcascade_frontalface_alt failed!");
    }
}

GetData::GetData(User u,QWidget *parent):
    QDialog(parent),
    ui(new Ui::GetData)
{
    ui->setupUi(this);
    timer=new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(get_pic()));  // 时间到，读取当前摄像头信息

    //videoLable大小更改
    QPixmap *pixmap = new QPixmap(":/new/Img/face.png");
    pixmap->scaled(ui->videoLable->size(), Qt::KeepAspectRatio);
    ui->videoLable->setScaledContents(true);
    ui->videoLable->setPixmap(*pixmap);
    ui->cancelButton->hide();

    //加载分类训练器，OpenCv官方文档提供的xml文档，可以直接调用
    //xml文档路径，  opencv\sources\data\haarcascades

    if (!face_cascade.load(FACE_XML_PATH))
    {
        qDebug("Load haarcascade_frontalface_alt failed!");
    }
    user.setId(u.getId());
    ui->nameEdit->setText(u.getName());
    ui->stuNumEdit->setText(u.getStuNum());
    ui->majorEdit->setText(u.getMajor());
}

GetData::~GetData()
{
    delete timer;
    delete ui;
}

bool GetData::readFarme()
{
    if(!capture.isOpened()){
        qDebug("摄像头未打开");
        return false;
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
        return true;
    }
    else
    {
        qDebug("图片捕捉失败");
        return false;
    }
}

bool GetData::get_pic(){
    if(user.getPicNum()>=10){
        timer->stop();
        ui->videoLable->setPixmap(*pixmap);
        return true;
    }
    readFarme();
    if(faceRect.size()!=1){
        return false;
    }
    cap_tmp = cap_gray(faceRect[0]);//在灰度图中将圈出的脸所在区域裁剪出
    cv::resize(cap_tmp, cap_tmp, cv::Size(92, 112));//将兴趣域size为92*112
    //在 faces[0].tl()的左上角上面写序号
    // putText(cap, std::to_string(pic_num), faceRect[0].tl(), 3, 1.2, (0, 0, 225), 2, 0);


//    Mat temp;//临时保存RGB图像
//    cvtColor(frame, temp, CV_BGR2RGB);//BGR convert to RGB
//    QImage Qtemp = QImage((const unsigned char*)(temp.data),
//                          temp.cols, temp.rows, temp.step,
//                          QImage::Format_RGB888);
//    ui->label_face_2->setScaledContents(true);
//    ui->label_face_2->setPixmap(QPixmap::fromImage(Qtemp));
//    ui->label_face_2->show();

    //图片的存放位置
    //std::string dir_str = IMG_PATH + std::to_string(tol_num) + "\\" + std::to_string(pic_num) + ".png";


    //string filename = format("%s%d.jpg",pic_num);
    //imwrite(dir_str, cap_tmp);//存在当前目录下
    user.addFace(cap_tmp);
    return true;
}


void GetData::on_startButton_clicked()
{
    OpenCamara();   // 打开摄像头
    timer->start(TIME_INTERVAL);
    ui->startButton->setEnabled(false);
    ui->sureButton->setEnabled(true);
}

User GetData::getUserData(){
    user.setName(ui->nameEdit->text()).setStuNum(ui->stuNumEdit->text()).setMajor(ui->majorEdit->text());
    return user;
}

// 图片转换
QImage  GetData::Mat2QImage(cv::Mat cvImg)
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

bool GetData::OpenCamara()
{
    if(capture.isOpened())return true;
    capture.open(0);
    qDebug("打开摄像头");
    return capture.isOpened();
}
void GetData::on_cancelButton_clicked()
{
    capture.release();
    close();
}


void GetData::on_sureButton_clicked()
{
    accept();
}

