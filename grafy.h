#ifndef GRAFY_H
#define GRAFY_H

#include <QDialog>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>

namespace Ui {
class grafy;
}

class grafy : public QDialog
{
    Q_OBJECT

public:
    explicit grafy(QWidget *parent = nullptr);
    ~grafy();

private:
    Ui::grafy *ui;
};

#endif // GRAFY_H
