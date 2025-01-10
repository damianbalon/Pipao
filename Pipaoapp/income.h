#ifndef INCOME_H
#define INCOME_H

#include <QString>
#include <QDate>

class Income {
public:
    Income(const QDate &date, double amount);

    QDate getDate() const;
    double getAmount() const;

private:
    QDate date;
    double amount;
};

#endif // INCOME_H
