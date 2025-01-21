#include "income.h"

Income::Income(const QDate &date, double amount)
    : date(date), amount(amount) {}

QDate Income::getDate() const {
    return date;
}

double Income::getAmount() const {
    return amount;
}
