#include "table.h"
#include "ui_table.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "expense_types.h"
#include "income_types.h"

Table::Table(QWidget *parent)
    : QDialog(parent), ui(new Ui::Table) {
    ui->setupUi(this);
    setupTable();
}

Table::~Table() {
    delete ui;
}

void Table::setupTable() {
    QTableWidget *table = ui->tableWidget;
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({"Date", "Amount", "Category", "Type", "Additional Info"});

    QSqlQuery query("SELECT date, amount, category, 'Income' AS type FROM incomes "
                    "UNION ALL "
                    "SELECT date, amount, category, 'Expense' AS type FROM expenses");

    if (!query.exec()) {
        qDebug() << "Error fetching data:" << query.lastError().text();
        return;
    }

    int row = 0;
    while (query.next()) {
        table->insertRow(row);

        table->setItem(row, 0, new QTableWidgetItem(query.value("date").toString()));
        table->setItem(row, 1, new QTableWidgetItem(query.value("amount").toString()));
        table->setItem(row, 2, new QTableWidgetItem(query.value("category").toString()));
        table->setItem(row, 3, new QTableWidgetItem(query.value("type").toString()));

        QString additionalInfo;
        QString type = query.value("type").toString();

        if (type == "Income") {
            Income* income = createIncome(query.value("date").toDate(), query.value("amount").toDouble(), query.value("category").toString());
            additionalInfo = income->additionalInfo();
            delete income;
        } else if (type == "Expense") {
            Expense* expense = createExpense(query.value("date").toDate(), query.value("amount").toDouble(), query.value("category").toString());
            additionalInfo = expense->additionalInfo();
            delete expense;
        }

        table->setItem(row, 4, new QTableWidgetItem(additionalInfo));

        ++row;
    }

    table->horizontalHeader()->setStretchLastSection(true);
    table->resizeColumnsToContents();
}

Income* Table::createIncome(const QDate &date, double amount, const QString &category) {
    if (category == "Salary") {
        return new Salary(date, amount);
    } else if (category == "Bonus") {
        return new Bonus(date, amount);
    } else if (category == "Interest") {
        return new Interest(date, amount);
    }else{
        return 0;
    }
}

Expense* Table::createExpense(const QDate &date, double amount, const QString &category) {
    if (category == "Shopping") {
        return new Shopping(date, amount);
    } else if (category == "Bills") {
        return new Bills(date, amount);
    } else if (category == "Transport") {
        return new Transport(date, amount);
    } else{
        return 0;
}


}
