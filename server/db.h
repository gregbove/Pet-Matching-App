#ifndef DB_H
#define DB_H

#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QVariant>
#include <QString>

#include "../common/user.h"
#include "../common/parent.h"
#include "../common/shelter.h"
#include "../common/pet.h"
#include "../common/shelterowner.h"
#include "../common/administrator.h"
#include "../common/petmatch.h"

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

    void foreachShelterOwner(const std::function<void(ShelterOwner &)> & f) const;

    void foreachAdmin(const std::function<void(Administrator &)> & f) const;

    void foreachPet(const std::function<void(Pet &)> & f) const;

    void foreachPetMatch(int parentId,
                         const std::function<void(PetMatch &)> & f,
                         QString * err = nullptr) const;

    bool getUser(QString userName, BNBModel ** user,
                 UserType & uType, QString * err = nullptr) const;

    bool getShelter(int id, Shelter & shelter, QString * err = nullptr) const;

    bool updatePetMatches(int parentId, QString * err = nullptr);

    bool createParentAndUser(Parent & parent, QString * err = nullptr);

    bool createAdministratorAndUser(
            Administrator & administrator, QString * err = nullptr);

    bool createShelterOwnerAndUser(
            ShelterOwner & shelterOwner, QString * err = nullptr);

    bool createUser(User & user, QString * err = nullptr);

    bool createPet(Pet & p, QString * err);


    QSqlDatabase db;

    Db(Db &other) = delete;
    void operator =(const Db &) = delete;
};

#endif // DB_H
