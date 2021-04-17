#ifndef PARENT_H
#define PARENT_H

#include <QString>

#include "user.h"

class Parent : public BNBModel
{
public:
    Parent();

    virtual void fromJson(const QJsonObject & obj);
    virtual void toJson(QJsonObject & obj) const;

    virtual QString validation() const;

    User & getUser();
    void setUser(const User &value);

    QString getName() const;
    void setName(const QString &value);

private:
    static constexpr const char* USER = "user";
    static constexpr const char* NAME = "name";

    User user;
    QString name;
};

#endif // PARENT_H
