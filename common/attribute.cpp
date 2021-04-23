#include "attribute.h"

Attribute::Attribute()
{
    name = QString();
    description = QString();
    offset = 0;
    range = 0;
}

Attribute::~Attribute()
{

}

void Attribute::fromJson(const QJsonObject &j)
{
    BNBModel::fromJson(j); // BNBModel must add the id

    if (j.contains(NAME) && j[NAME].isString())
        name = j[NAME].toString();

    if (j.contains(OFFSET) && j[OFFSET].isString())
        offset = j[OFFSET].toInt();

    if (j.contains(RANGE) && j[RANGE].isString())
        range = j[RANGE].toInt();

    if (j.contains(DESCRIPTION) && j[DESCRIPTION].isString())
        description = j[DESCRIPTION].toString();
}

void Attribute::toJson(QJsonObject &j) const
{
    BNBModel::toJson(j); // BNBModel must add the id

    j[OFFSET] = offset;
    j[RANGE] = range;
    j[DESCRIPTION] = description;
    j[NAME] = name;
}

QString Attribute::validation() const
{
    QString v;

    if (name.isEmpty())
        v += "name must not be empty\n";

    if (range <= 0 )
        v += "Range should be positives\n";

    if (description.isEmpty())
        v += "Description must not be empty\n";

    return v;
}




QString Attribute::getDescription() const
{
    return description;
}

void Attribute::setDescription(const QString &value)
{
    description = value;
}

QString Attribute::getName() const
{
    return name;
}

void Attribute::setName(const QString &value)
{
    name = value;
}

int Attribute::getOffset() const
{
    return offset;
}

void Attribute::setOffset(int value)
{
    offset = value;
}

int Attribute::getRange() const
{
    return range;
}

void Attribute::setRange(int value)
{
    range = value;
}
