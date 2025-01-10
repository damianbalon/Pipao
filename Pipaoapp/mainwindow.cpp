#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Konfiguracja bazy danych
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/finances.db");

    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Failed to open the database: " + db.lastError().text());
        qDebug() << "Database error:" << db.lastError().text();
    } else {
        ensureDatabaseTables();
    }

    // Wypełnij listy rozwijane
    ui->incomeCategoryComboBox->addItems({"Salary", "Bonus", "Interest"});
    ui->expenseCategoryComboBox->addItems({"Shopping", "Bills", "Transport"});
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ensureDatabaseTables() {
    QSqlQuery query;

    if (!query.exec("CREATE TABLE IF NOT EXISTS incomes ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "date TEXT NOT NULL,"
                    "amount REAL NOT NULL,"
                    "category TEXT NOT NULL"
                    ")")) {
        QMessageBox::critical(this, "Error", "Failed to create incomes table: " + query.lastError().text());
        qDebug() << "Create table incomes error:" << query.lastError().text();
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS expenses ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "date TEXT NOT NULL,"
                    "amount REAL NOT NULL,"
                    "category TEXT NOT NULL"
                    ")")) {
        QMessageBox::critical(this, "Error", "Failed to create expenses table: " + query.lastError().text());
        qDebug() << "Create table expenses error:" << query.lastError().text();
    }
}

void MainWindow::on_addIncomeButton_clicked() {
    QString category = getSelectedIncomeCategory();
    Income *income = nullptr;

    if (category == "Salary") {
        income = new Salary(ui->dateEdit->date(), ui->lineEdit->text().toDouble());
    } else if (category == "Bonus") {
        income = new Bonus(ui->dateEdit->date(), ui->lineEdit->text().toDouble());
    } else if (category == "Interest") {
        income = new Interest(ui->dateEdit->date(), ui->lineEdit->text().toDouble());
    }

    if (income) {
        QSqlQuery query;
        query.prepare("INSERT INTO incomes (date, amount, category) VALUES (:date, :amount, :category)");
        query.bindValue(":date", income->getDate().toString("yyyy-MM-dd"));
        query.bindValue(":amount", income->getAmount());
        query.bindValue(":category", category);

        if (!query.exec()) {
            QMessageBox::critical(this, "Error", "Failed to add income: " + query.lastError().text());
            qDebug() << "Query error:" << query.lastError().text();
            qDebug() << "Last executed query:" << query.lastQuery();
        } else {
            QMessageBox::information(this, "Success", "Income added successfully!");
        }
        delete income;
    }

    check_sum();
}

void MainWindow::on_addExpenseButton_clicked() {
    QString category = getSelectedExpenseCategory();
    Expense *expense = nullptr;

    if (category == "Shopping") {
        expense = new Shopping(ui->dateEdit_2->date(), ui->lineEdit_2->text().toDouble());
    } else if (category == "Bills") {
        expense = new Bills(ui->dateEdit_2->date(), ui->lineEdit_2->text().toDouble());
    } else if (category == "Transport") {
        expense = new Transport(ui->dateEdit_2->date(), ui->lineEdit_2->text().toDouble());
    }

    if (expense) {
        QSqlQuery query;
        query.prepare("INSERT INTO expenses (date, amount, category) VALUES (:date, :amount, :category)");
        query.bindValue(":date", expense->getDate().toString("yyyy-MM-dd"));
        query.bindValue(":amount", expense->getAmount());
        query.bindValue(":category", category);

        if (!query.exec()) {
            QMessageBox::critical(this, "Error", "Failed to add expense: " + query.lastError().text());
            qDebug() << "Query error:" << query.lastError().text();
            qDebug() << "Last executed query:" << query.lastQuery();
        } else {
            QMessageBox::information(this, "Success", "Expense added successfully!");
        }
        delete expense;
    }

    check_sum();
}

void MainWindow::on_graph_clicked() {
    this->hide();
    grafy graphDialog(this);
    graphDialog.exec();
    this->show();
}

QString MainWindow::getSelectedIncomeCategory() {
    return ui->incomeCategoryComboBox->currentText();
}

QString MainWindow::getSelectedExpenseCategory() {
    return ui->expenseCategoryComboBox->currentText();
}

void MainWindow::check_sum() {
    double totalIncome = 0.0;
    double totalExpenses = 0.0;

    QSqlQuery query;

    if (query.exec("SELECT SUM(amount) FROM incomes")) {
        if (query.next()) {
            totalIncome = query.value(0).toDouble();
        }
    }

    if (query.exec("SELECT SUM(amount) FROM expenses")) {
        if (query.next()) {
            totalExpenses = query.value(0).toDouble();
        }
    }

    double balance = totalIncome - totalExpenses;
    ui->stanKonta->setText(QString::number(balance, 'f', 2));
}
