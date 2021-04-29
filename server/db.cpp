#include "db.h"

Db * Db::inst = nullptr;

Db::Db()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

Db * Db::instance()
{
    if(inst == nullptr){
        inst = new Db();
    }

    return inst;
}

void Db::initialize(QString dbPath)
{
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        throw "Failed to open database during Db construction";
    }

    db.exec("CREATE TABLE IF NOT EXISTS users ("
            "id INTEGER PRIMARY KEY ASC,"
            "username TEXT,"
            "password TEXT, "
            "createdAt INTEGER)");

    db.exec("CREATE TABLE IF NOT EXISTS parents ("
            "id INTEGER PRIMARY KEY ASC,"
            "userId INTEGER NOT NULL,"
            "name TEXT,"
            "FOREIGN KEY (userId) REFERENCES users (id))");

    db.exec("CREATE TABLE IF NOT EXISTS administrators ("
            "id INTEGER PRIMARY KEY ASC,"
            "userId INTEGER NOT NULL,"
            "isSuperAdmin BOOLEAN NOT NULL,"
            "FOREIGN KEY (userId) REFERENCES users (id))");

    db.exec("CREATE TABLE IF NOT EXISTS shelters ("
            "id INTEGER PRIMARY KEY ASC,"
            "name TEXT NOT NULL)");

    db.exec("CREATE TABLE IF NOT EXISTS shelterOwners ("
            "id INTEGER PRIMARY KEY ASC,"
            "userId INTEGER NOT NULL,"
            "shelterId INTEGER NOT NULL,"
            "name TEXT NOT NULL,"
            "FOREIGN KEY (userId) REFERENCES users (id),"
            "FOREIGN KEY (shelterId) REFERENCES shelters (id))");

    db.exec("CREATE TABLE IF NOT EXISTS pets ("
            "id INTEGER PRIMARY KEY ASC,"
            "shelterId INTEGER NOT NULL,"
            "petName TEXT,"
            "description TEXT,"
            "FOREIGN KEY (shelterId) REFERENCES shelters (id))");

    db.exec("CREATE TABLE IF NOT EXISTS attributes ("
            "id INTEGER PRIMARY KEY ASC,"
            "name TEXT NOT NULL,"
            "description TEXT,"
            "range INTEGER NOT NULL,"
            "offset INTEGER NOT NULL)");

    db.exec("CREATE TABLE IF NOT EXISTS petAttributes ("
            "id INTEGER PRIMARY KEY ASC,"
            "petId INTEGER NOT NULL,"
            "attributeId INTEGER NOT NULL,"
            "value INTEGER NOT NULL,"
            "FOREIGN KEY (petId) REFERENCES pets (id),"
            "FOREIGN KEY (attributeId) REFERENCES attributes (id))");
}

Db::~Db()
{
    db.close();
}

void Db::foreachParent(const std::function<void(Parent &)> & func) const
{
    QSqlQuery q = db.exec("SELECT "
                          "users.id, "
                          "users.username, "
                          "users.password, "
                          "users.createdAt, "
                          "parents.id, "
                          "parents.name "
                          "FROM parents "
                          "INNER JOIN users "
                          "ON parents.userId = users.id");

    while (q.next())
    {
        User u;
        Parent p;

        u.setId(q.value(0).toInt());
        u.setUsername(q.value(1).toString());
        u.setPassword(q.value(2).toString());
        u.setCreatedAt(q.value(3).toDateTime());

        p.setUser(u);
        p.setId(q.value(4).toInt());
        p.setName(q.value(5).toString());

        func(p);
    }
}

//void Db::foreachShelterOwner(const std::function<void(ShelterOwner &)> & func) const
//{
//    QSqlQuery q = db.exec("SELECT "
//                          "users.id, "
//                          "users.username, "
//                          "users.password, "
//                          "users.createdAt, "
//                          "shelterOwner.id, "
//                          "shelterOwner.name "
//                          "FROM shelterOwner "
//                          "INNER JOIN users "
//                          "ON shelterOwner.userId = users.id");

//    while (q.next())
//    {
//        User u;
//        ShelterOwner s;

//        u.setId(q.value(0).toInt());
//        u.setUsername(q.value(1).toString());
//        u.setPassword(q.value(2).toString());
//        u.setCreatedAt(q.value(3).toDateTime());

//        s.setUser(u);
//        s.setId(q.value(4).toInt());
//        s.setName(q.value(5).toString());

//        func(s);
//    }
//}

//void Db::foreachAdmin(const std::function<void(Administrator &)> & func) const
//{
//    QSqlQuery q = db.exec("SELECT "
//                          "users.id, "
//                          "users.username, "
//                          "users.password, "
//                          "users.createdAt, "
//                          "admin.id, "
//                          "admin.name "
//                          "FROM admin "
//                          "INNER JOIN users "
//                          "ON shelterOwner.userId = users.id");

//    while (q.next())
//    {
//        User u;
//        Administrator a;

//        u.setId(q.value(0).toInt());
//        u.setUsername(q.value(1).toString());
//        u.setPassword(q.value(2).toString());
//        u.setCreatedAt(q.value(3).toDateTime());

//        a.setUser(u);
//        a.setId(q.value(4).toInt());

//        func(a);
//    }
//}

bool Db::createParentAndUser(Parent & p, QString * err)
{
    if (!createUser(p.getUser(), err))
        return false;

    QSqlQuery q;
    q.prepare("INSERT INTO parents (name, userId) VALUES (?, ?)");
    q.bindValue(0, p.getName());
    q.bindValue(1, p.getUser().getId());

    if (q.exec())
    {
        p.setId(q.lastInsertId().toInt());
        return true;
    }
    else if (err != nullptr)
    {
        *err = q.lastError().text();
        return false;
    }
}

bool Db::createUser(User & u, QString * err)
{
    QSqlQuery q;
    q.prepare("INSERT INTO users "
              "(username, password, createdAt) "
              "VALUES (?, ?, ?)");
    q.bindValue(0, u.getUsername());
    q.bindValue(1, u.getPassword());
    q.bindValue(2, u.getCreatedAt().toSecsSinceEpoch());

    if (q.exec())
    {
        u.setId(q.lastInsertId().toInt());
        return true;
    }
    else if (err != nullptr)
    {
        *err = q.lastError().text();
        return false;
    }
}

//bool createShelterOwner(ShelterOwner & so, QString * err = nullptr){
    
//    if (!createUser(so.getUser(), err))
//        return false;
    
//    QSqlQuery q;
//    q.prepare("INSERT INTO shelterOwners "
//              "(User, name, ShelterID) "
//              "VALUES (?, ?, ?)");
//    q.bindValue(0, so.getUser().getUsername());
//    q.bindValue(1, so.getName());
//    q.bindValue(2, so.getShelterId());

//    if (q.exec())
//    {
//        return true;
//    }
//    else if (err != nullptr)
//    {
//        *err = q.lastError().text();
//        return false;
//    }
//}

//bool Db::createShelter(Shelter & s, QString * err)
//{

//    QSqlQuery q;
//    q.prepare("INSERT INTO shelters "
//              "(name) "
//              "VALUES (?)");
//    q.bindValue(0, s.getName());

//    if (q.exec())
//    {
//        return true;
//    }
//    else if (err != nullptr)
//    {
//        *err = q.lastError().text();
//        return false;
//    }
//}

//bool Db::createPet(Pet & p, QString * err){
//    QSqlQuery q;
//    q.prepare("INSERT INTO pets "
//              "(name, description, shelterID) "
//              "VALUES (?, ?, ?)");
//    q.bindValue(0, p.getPetName());
//    q.bindValue(1, p.getDescription());
//    q.bindValue(2, p.getShelterId());

//    if (q.exec())
//    {
//        return true;
//    }
//    else if (err != nullptr)
//    {
//        *err = q.lastError().text();
//        return false;
//    }
//}


