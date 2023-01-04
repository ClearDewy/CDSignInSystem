
#include "train.h"


train::train(QObject *parent):QThread(parent)
{

}

train::~train()
{

}

void train::run(std::vector<cv::Mat>& images,std::vector<int>& labels)
{
     qDebug()<<"启动训练线程";
    // 如果没有读取到足够图片，也退出.
    if (images.size() <= 1) {
        // std::string error_message = "至少需要2张图片才能运行,请添加更多的图片到您的数据集";
        // CV_Error(cv::CV_StsError, error_message);
    }

    for (int i = 0; i < images.size(); i++)
    {
        //cout<<images.size();
        if (images[i].size() != cv::Size(92, 112))
        {
            // cout << i << endl;
            // cout << images[i].size() << endl;
        }

    }
    // 下面的几行代码仅仅是从你的数据集中移除最后一张图片，作为测试图片
//    cv::Mat testSample = images[images.size() - 1];
//    int testLabel = labels[labels.size() - 1];
//    images.pop_back();//删除最后一张照片，此照片作为测试图片
//    labels.pop_back();//删除最有一张照片的labels
    //调用其中的成员函数train()来完成分类器的训练
    cv::Ptr<cv::face::FaceRecognizer> model = cv::face::EigenFaceRecognizer::create();
    model->train(images, labels);
    model->save(FACE_CLASSIFIER_PATH);//保存路径可自己设置，但注意用“\\”

//    Ptr<face::BasicFaceRecognizer> model1 = face::FisherFaceRecognizer::create();
//    model1->train(images, labels);
//    model1->save("MyFaceFisherModel.xml");

//    Ptr<face::LBPHFaceRecognizer> model2 = face::LBPHFaceRecognizer::create();
//    model2->train(images, labels);
//    model2->save("MyFaceLBPHModel.xml");

    // 下面对测试图像进行预测，predictedLabel是预测标签结果
    //注意predict()入口参数必须为单通道灰度图像，如果图像类型不符，需要先进行转换
    //predict()函数返回一个整形变量作为识别标签
//    int predictedLabel = model->predict(testSample);//加载分类器
//    int predictedLabel1 = model1->predict(testSample);
//    int predictedLabel2 = model2->predict(testSample);
//    std::string result_message = cv::format("Predicted class = %d / Actual class = %d.", predictedLabel, testLabel);
//    std::string result_message1 = format("Predicted class = %d / Actual class = %d.", predictedLabel1, testLabel);
//    std::string result_message2 = format("Predicted class = %d / Actual class = %d.", predictedLabel2, testLabel);
//    cout << result_message << endl;
//    cout << result_message1 << endl;
//    cout << result_message2 << endl;
    qDebug()<<"训练完成";
    emit finished();
}
