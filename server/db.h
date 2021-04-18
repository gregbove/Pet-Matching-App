#ifndef DB_H
#define DB_H

#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QVariant>

#include "../common/parent.h"

#include <iostream>
#include <functional>

class Db
{
protected:
    static Db * inst;

    Db();

public:
    static Db * instance();

    ~Db();

    void initialize(QString dbPath);

    void foreachParent(const std::function<void(Parent &)> & f) const;

    QSqlDatabase db;

    Db(Db &other) = delete;
    void operator =(const Db &) = delete;
};

#endif // DB_H
