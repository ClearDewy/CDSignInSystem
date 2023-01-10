#ifndef HOMEWND_H
#define HOMEWND_H

#include <QWidget>
#include "sql.h"
#include <QtCharts>
#include <QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QLineSeries>
class QChartView;
class QChart;

namespace Ui {
class HomeWnd;
}

class HomeWnd : public QWidget
{
    Q_OBJECT

public:
    explicit HomeWnd(Sql*,QWidget *parent = nullptr);
    ~HomeWnd();

private:
    Ui::HomeWnd *ui;
    Sql *sql;
};

#endif // HOMEWND_H
