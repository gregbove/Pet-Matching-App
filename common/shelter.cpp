#include "shelter.h"


Shelter::Shelter()
{
    name = QString();
}

Shelter::~Shelter()
{

}

void Shelter::fromJson(const QJsonObject &j)
{
    BNBModel::fromJson(j); // BNBModel must add the id

    if (j.contains(NAME) && j[NAME].isString())
        name = j[NAME].toString();

}

void Shelter::toJson(QJsonObject &j) const
{
    BNBModel::toJson(j); // BNBModel must add the id

    j[NAME] = name;

}

QString Shelter::validation() const
{
    QString v;

    if (name.isEmpty())
        v += "Shelter name must not be empty\n";

    return v;
}

QString Shelter::getName() const
{
    return name;
}

void Shelter::setName(const QString &value)
{
    name = value;
}
