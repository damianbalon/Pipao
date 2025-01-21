#include "grafy.h"
#include "ui_grafy.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QDebug>

grafy::grafy(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::grafy)
{
    ui->setupUi(this);

    QLineSeries *series = new QLineSeries();
    QSqlQuery query;
    QDate currentDate = QDate::currentDate();
    QDate startDate = currentDate.addMonths(-1);

    double runningBalance = 0.0;

    for (QDate date = startDate; date <= currentDate; date = date.addDays(1)) {
        double dailyIncome = 0.0;
        double dailyExpense = 0.0;

        // Pobierz dochody dla danego dnia
        query.prepare("SELECT SUM(amount) FROM incomes WHERE date = :date");
        query.bindValue(":date", date.toString("yyyy-MM-dd"));
        if (query.exec() && query.next()) {
            dailyIncome = query.value(0).toDouble();
        } else {
            qDebug() << "Error fetching incomes:" << query.lastError().text();
        }

        // Pobierz wydatki dla danego dnia
        query.prepare("SELECT SUM(amount) FROM expenses WHERE date = :date");
        query.bindValue(":date", date.toString("yyyy-MM-dd"));
        if (query.exec() && query.next()) {
            dailyExpense = query.value(0).toDouble();
        } else {
            qDebug() << "Error fetching expenses:" << query.lastError().text();
        }

        // Oblicz saldo
        runningBalance += (dailyIncome - dailyExpense);
        series->append(date.toJulianDay(), runningBalance);
    }



    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Date");
    axisX->setLabelsVisible(false);
    chart->setAxisX(axisX, series);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Balance");
    chart->setAxisY(axisY, series);

    QChartView *chartView = new QChartView(chart, this);
    chartView->setRenderHints(QPainter::Antialiasing);

    ui->verticalLayout->addWidget(chartView);
}

grafy::~grafy()
{
    delete ui;
}
