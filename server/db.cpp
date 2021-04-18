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
