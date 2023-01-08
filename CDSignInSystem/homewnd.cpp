#include "homewnd.h"
#include "ui_homewnd.h"
#include"sql.h"
HomeWnd::HomeWnd(Sql*s,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeWnd)
{
    ui->setupUi(this);
    sql=s;

    //饼状图
    int total=sql->getTotleUserNum();
    int alive=sql->getAliveUserNum();
    double x=alive*1.0/total;
    QPieSlice *slice_1 = new QPieSlice(QStringLiteral("在线人数"),x , this);
    slice_1->setLabel(slice_1->label()+QString::asprintf(":%d人",alive));//设置标签信息
    slice_1->setLabelVisible(true); // 显示饼状区对应的数据label
    slice_1->setBrush(QBrush(QColor(76, 177, 255,80)));
    QPieSlice *slice_2 = new QPieSlice(QStringLiteral("不在线人数"), 1-x, this);
    slice_2->setLabel(slice_2->label()+QString::asprintf(":%d人",total-alive));//设置标签信息
    slice_2->setLabelVisible(true);
    slice_2->setBrush(QBrush(QColor(151, 232, 255,80)));

    // 将两个饼状分区加入series
    QPieSeries *series = new QPieSeries(this);
    series->append(slice_1);
    series->append(slice_2);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::AllAnimations); // 设置显示时的动画效果
    chart->setTitle("在线人数统计");
    chart->legend()->setAlignment(Qt::AlignRight);//图片放置

    QChartView *chartview = new QChartView(this);
    chartview->show();
    chartview->setChart(chart);

    ui->verticalLayout->insertWidget(0, chartview);
}

HomeWnd::~HomeWnd()
{
    delete ui;
}

/*void HomeWnd::PiewData()
{
    // 构造两个饼状分区，在线人数显示绿色占60%，不在线人数显示蓝色占40%
    //Sql* sq;
    //sq=new Sql;
    //int total=sql->getTotleUserNum();
    //int alive=sql->getAliveUserNum();
    //double x=alive*1.0/total;
    QPieSlice *slice_1 = new QPieSlice(QStringLiteral("在线人数"), 0.6, this);
    slice_1->setLabelVisible(true); // 显示饼状区对应的数据label
    slice_1->setBrush(QBrush(QColor(76, 177, 255,80)));
    QPieSlice *slice_2 = new QPieSlice(QStringLiteral("不在线人数"), 0.4, this);
    slice_2->setLabelVisible(true);
    slice_2->setBrush(QBrush(QColor(151, 232, 255,80)));

    // 将两个饼状分区加入series
    QPieSeries *series = new QPieSeries(this);
    series->append(slice_1);
    series->append(slice_2);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::AllAnimations); // 设置显示时的动画效果
    chart->setTitle("在线人数统计");
    chart->legend()->setAlignment(Qt::AlignRight);//图片放置

    QChartView *chartview = new QChartView(this);
    chartview->show();
    chartview->setChart(chart);

    ui->verticalLayout->insertWidget(0, chartview);


}*/
