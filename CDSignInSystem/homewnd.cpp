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
    series->setPieSize(0.5);//设置饼图大小

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::AllAnimations); // 设置显示时的动画效果
    chart->setTitle("在线人数统计");
    chart->legend()->setAlignment(Qt::AlignBottom);//图片放置


    QChartView *chartview = new QChartView(this);
    chartview->show();
    chartview->setChart(chart);
    ui->verticalLayout->insertWidget(0, chartview);



    //折线图
    QChart *chart_ = new QChart();
    chart_->setTitle("近4天签到人数");

    QLineSeries *series1 = new QLineSeries(chart_);

    series1->setName("近4天签到人数");

    std::vector<int>a(10);
    a=s->getRecent(5);
    for(int i=0;i<5;i++){
        series1->append(i,a[i]);
    }
    chart_->addSeries(series1);

    QScatterSeries *scatterSeries1 = new QScatterSeries();
    scatterSeries1->setPointLabelsFormat("@yPoint");
    scatterSeries1->setPointLabelsVisible();
    scatterSeries1->setMarkerSize(4);
    // *scatterSeries1 << QPointF(0,6);也可以
    for(int i=0;i<5;i++){
        scatterSeries1->append(i,a[i]);
    }
    chart_->addSeries(scatterSeries1);//数据显示
    chart_->legend()->hide();//隐藏legend（图例）

    //设置动画效果
    chart->setAnimationOptions(QChart::AllAnimations);

    chart_->createDefaultAxes();// 设置网格
    chart_->axes(Qt::Horizontal).first()->setRange(0, 4);//设置x轴范围
    chart_->axes(Qt::Vertical).first()->setRange(0, 20);//设置y轴范围

    // Add space to label to add space between labels and axis 在标签和轴之间加空格
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart_->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");
    chart_->setTheme(QChart::ChartThemeLight);//自带主题
    // 创建QChartView 对象
    QChartView *chartView_;
    // QChartView 对象载入折线图
    chartView_ = new QChartView(chart_);
    // 显示图标
    ui->verticalLayout_2->insertWidget(0, chartView_);


}

HomeWnd::~HomeWnd()
{
    delete ui;
}


