#include "expense_types.h"

Shopping::Shopping(const QDate &date, double amount)
    : Expense(date, amount) {}

QString Shopping::getDetails() const {
    return "Shopping on " + getDate().toString() + ", amount: " + QString::number(getAmount());
}

QString Shopping::additionalInfo()  {
    return "Shopping category: Groceries or personal items." + getDetails();
}

Bills::Bills(const QDate &date, double amount)
    : Expense(date, amount) {}

double Bills::applyDiscount(double percentage) {
    double discount = getAmount() * percentage / 100;
    return getAmount() - discount;
}

QString Bills::additionalInfo()  {

    QString s = QString::number(applyDiscount(10));

    return "Bills include electricity, water, or rent." +  s;
}

Transport::Transport(const QDate &date, double amount)
    : Expense(date, amount) {}

double Transport::calculateMileageCost(double mileage, double costPerMile) {
    return mileage * costPerMile;
}

QString Transport::additionalInfo()  {

    QString s = QString::number(calculateMileageCost(2,20));

    return "Transport costs for commuting or fuel. " + s;
}
