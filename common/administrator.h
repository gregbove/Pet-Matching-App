#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <QString>

#include "user.h"

class Administrator : public BNBModel
{
public:
    Administrator();

    virtual void fromJson(const QJsonObject & obj);
    virtual void toJson(QJsonObject & obj) const;

    virtual QString validation() const;

    User & getUser();
    void setUser(const User &value);

    bool getIsSuperAdmin() const;
    void setIsSuperAdmin(bool value);

private:
    static constexpr const char* USER = "user";
    static constexpr const char* ISSUPERADMIN = "isSuperAdmin";

    User user;
    bool isSuperAdmin;
};

#endif // ADMINISTRATOR_H
