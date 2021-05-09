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

    db.exec("CREATE TABLE IF NOT EXISTS attributePreferences ("
            "id INTEGER PRIMARY KEY ASC,"
            "parentId INTEGER NOT NULL,"
            "attributeId INTEGER NOT NULL,"
            "weight DOUBLE NOT NULL,"
            "FOREIGN KEY (parentId) REFERENCES parents (id),"
            "FOREIGN KEY (attributeId) REFERENCES attributes (id))");

    db.exec("CREATE TABLE IF NOT EXISTS petWatches ("
            "id INTEGER PRIMARY KEY ASC,"
            "parentId INTEGER NOT NULL,"
            "petId INTEGER NOT NULL,"
            "createdAt INTEGER NOT NULL,"
            "FOREIGN KEY (parentId) REFERENCES parents (id),"
            "FOREIGN KEY (petId) REFERENCES pets (id))");

    db.exec("CREATE TABLE IF NOT EXISTS petMatches ("
            "id INTEGER PRIMARY KEY ASC,"
            "parentId INTEGER NOT NULL,"
            "petId INTEGER NOT NULL,"
            "updatedAt INTEGER NOT NULL,"
            "score DOUBLE NOT NULL,"
            "FOREIGN KEY (parentId) REFERENCES parents (id),"
            "FOREIGN KEY (petId) REFERENCES pets (id))");

    db.exec("CREATE TABLE IF NOT EXISTS petAdoptions ("
            "id INTEGER PRIMARY KEY ASC,"
            "parentId INTEGER NOT NULL,"
            "petId INTEGER NOT NULL,"
            "createdAt INTEGER NOT NULL,"
            "active BOOLEAN NOT NULL,"
            "approved BOOLEAN NOT NULL,"
            "FOREIGN KEY (parentId) REFERENCES parents (id),"
            "FOREIGN KEY (petId) REFERENCES pets (id))");
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

void Db::foreachShelterOwner(const std::function<void(ShelterOwner &)> & func) const
{
    QSqlQuery q = db.exec("SELECT "
                          "users.id, "
                          "users.username, "
                          "users.password, "
                          "users.createdAt, "
                          "shelters.id, "
                          "shelters.name, "
                          "shelterOwners.id, "
                          "shelterOwners.name "
                          "FROM shelterOwners "
                          "LEFT JOIN shelters "
                          "ON shelters.id = shelterOwners.shelterId "
                          "LEFT JOIN users "
                          "ON shelterOwners.userId = users.id");

    while (q.next())
    {
        User u;
        shared_ptr<Shelter> s = make_shared<Shelter>();
        ShelterOwner so;

        u.setId(q.value(0).toInt());
        u.setUsername(q.value(1).toString());
        u.setPassword(q.value(2).toString());
        u.setCreatedAt(q.value(3).toDateTime());

        s->setId(q.value(4).toInt());
        s->setName(q.value(5).toString());

        so.setUser(u);
        so.setShelter(s);
        so.setShelterId(s->getId());

        so.setId(q.value(6).toInt());
        so.setName(q.value(7).toString());

        func(so);
    }
}

void Db::foreachAdmin(const std::function<void(Administrator &)> & func) const
{
    QSqlQuery q = db.exec("SELECT "
                          "users.id, "
                          "users.username, "
                          "users.password, "
                          "users.createdAt, "
                          "administrators.id, "
                          "administrators.isSuperAdmin "
                          "FROM administrators "
                          "LEFT JOIN users "
                          "ON administrators.userId = users.id");

    while (q.next())
    {
        User u;
        Administrator a;

        u.setId(q.value(0).toInt());
        u.setUsername(q.value(1).toString());
        u.setPassword(q.value(2).toString());
        u.setCreatedAt(q.value(3).toDateTime());

        a.setUser(u);
        a.setId(q.value(4).toInt());
        a.setIsSuperAdmin(q.value(5).toBool());

        func(a);
    }
}

bool Db::getUser(QString userName, BNBModel **model, UserType & uType, QString * err) const
{
    QSqlQuery q;
    q.prepare("SELECT "
              "users.id, "
              "users.username, "
              "users.password, "
              "users.createdAt, "
              "parents.id, "
              "parents.name, "
              "shelterOwners.id, "
              "shelterOwners.name, "
              "shelterOwners.shelterId, "
              "administrators.id, "
              "administrators.isSuperAdmin "
              "FROM users "
              "LEFT JOIN parents "
              "ON users.id = parents.userId "
              "LEFT JOIN shelterOwners "
              "ON users.id = shelterOwners.userId "
              "LEFT JOIN administrators "
              "ON users.id = administrators.userId "
              "WHERE users.username = ?");

    q.bindValue(0, userName);
    if (!q.exec())
    {
        *err = q.lastError().text();
        return false;
    }

    if (q.next())
    {

        User u;
        u.setId(q.value(0).toInt());
        u.setUsername(q.value(1).toString());
        u.setPassword(q.value(2).toString());
        u.setCreatedAt(q.value(3).toDateTime());

        if (!q.value(4).isNull())
        {
            Parent * p = new Parent();
            p->setUser(u);
            p->setId(q.value(4).toInt());
            p->setName(q.value(5).toString());
            *model = p;
            uType = PARENT;
        }
        else if (!q.value(6).isNull())
        {
            ShelterOwner * o = new ShelterOwner();
            o->setUser(u);
            o->setId(q.value(6).toInt());
            o->setName(q.value(7).toString());
            o->setShelterId(q.value(8).toInt());
            *model = o;
            uType = SHELTER_OWNER;
        }
        else if (!q.value(9).isNull())
        {
            Administrator * a = new Administrator();
            a->setUser(u);
            a->setId(q.value(9).toInt());
            a->setIsSuperAdmin(q.value(10).toBool());
            *model = a;
            uType = ADMINISTRATOR;
        }
        else
        {
            *err = "No matching subtype for user";
            return false;
        }

        return true;
    }

    *err = "User not found";
    return true;
}

void Db::foreachPet(const std::function<void(Pet &)> & func) const{
    QSqlQuery q = db.exec("SELECT "
                          "shelter.id, "
                          "shelter.name, "
                          "pet.id, "
                          "pet.petName, "
                          "pet.description"
                          "FROM pets "
                          "INNER JOIN shelter "
                          "ON pet.shelterId = shelter.id");

    while (q.next())
    {
        shared_ptr<Shelter> s = make_shared<Shelter>();
        Pet p;

        s->setId(q.value(0).toInt());
        s->setName(q.value(1).toString());

        p.setShelter(s);
        p.setShelterId(s->getId());
        p.setId(q.value(2).toInt());
        p.setPetName(q.value(3).toString());
        p.setDescription(q.value(4).toString());

        func(p);
    }
}

bool Db::getShelter(int id, Shelter &shelter, QString *err) const
{
    QSqlQuery q;
    q.prepare("SELECT name FROM shelters WHERE id = ?");
    q.bindValue(0, id);

    if (!q.exec())
    {
        *err = q.lastError().text();
    }
    else if (!q.next())
    {
        *err = "Shelter not found";
    }
    else
    {
        shelter.setId(id);
        shelter.setName(q.value(0).toString());
        return true;
    }

    return false;
}

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

bool Db::createAdministratorAndUser(Administrator &a, QString *err)
{
    if (!createUser(a.getUser(), err))
        return false;

    QSqlQuery q;
    q.prepare("INSERT INTO administrators "
              "(isSuperAdmin, userId) "
              "VALUES (?, ?)");
    q.bindValue(0, a.getIsSuperAdmin());
    q.bindValue(1, a.getUser().getId());

    if (q.exec())
    {
        a.setId(q.lastInsertId().toInt());
        return true;
    }
    else if (err != nullptr)
    {
        *err = q.lastError().text();
        return false;
    }
}

bool Db::createShelterOwnerAndUser(ShelterOwner &o, QString *err)
{
    Shelter s;
    if (!getShelter(o.getShelterId(), s, err))
        return false;

    if (!createUser(o.getUser(), err))
        return false;

    QSqlQuery q;
    q.prepare("INSERT INTO shelterOwners "
              "(name, userId, shelterId) "
              "VALUES (?, ?, ?)");
    q.bindValue(0, o.getName());
    q.bindValue(1, o.getUser().getId());
    q.bindValue(2, o.getShelterId());

    if (q.exec())
    {
        o.setId(q.lastInsertId().toInt());
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

bool Db::createPet(Pet & p, QString * err){
    QSqlQuery q;
    q.prepare("INSERT INTO pets "
              "(name, description, shelterID) "
              "VALUES (?, ?, ?)");
    q.bindValue(0, p.getPetName());
    q.bindValue(1, p.getDescription());
    q.bindValue(2, p.getShelterId());

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




