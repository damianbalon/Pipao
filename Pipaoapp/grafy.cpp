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

    // Utwórz serię danych
    QLineSeries *series = new QLineSeries();

    // Pobierz dane z bazy i oblicz saldo dla każdego dnia
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

    // Utwórz wykres
    QChart *chart = new QChart();
    chart->legend()->hide(); // Ukryj legendę
    chart->addSeries(series);
    chart->createDefaultAxes();

    // Ustaw formatowanie osi X
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Date");   // Tytuł osi pozostaje
    axisX->setLabelsVisible(false); // Ukryj etykiety osi X
    chart->setAxisX(axisX, series);

    // Ustaw formatowanie osi Y
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Balance");
    chart->setAxisY(axisY, series);

    // Wyświetl wykres w widoku
    QChartView *chartView = new QChartView(chart, this);
    chartView->setRenderHints(QPainter::Antialiasing);

    // Dodaj wykres do layoutu
    ui->verticalLayout->addWidget(chartView);
}

grafy::~grafy()
{
    delete ui;
}
