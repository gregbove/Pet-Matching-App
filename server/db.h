#ifndef DB_H
#define DB_H

#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QVariant>
#include <QString>

#include "../common/parent.h"
#include "../common/shelter.h"
#include "../common/pet.h"
#include "../common/shelterowner.h"
#include "../common/administrator.h"

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

//    void foreachShelterOwner(const std::function<void(ShelterOwner &)> & f) const;

//    void foreachAdmin(const std::function<void(Administrator &)> & f) const;

    bool createParentAndUser(Parent & parent, QString * err = nullptr);

    bool createUser(User & user, QString * err = nullptr);

//    bool createShelter(Shelter & s, QString * err = nullptr);

//    bool createPet(Pet & p, QString * err = nullptr);
    
//    bool createShelterOwner(ShelterOwner & so, QString * err = nullptr);



    QSqlDatabase db;

    Db(Db &other) = delete;
    void operator =(const Db &) = delete;
};

#endif // DB_H
