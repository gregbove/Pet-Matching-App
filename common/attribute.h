#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QString>
#include <QDateTime>
#include <QJsonObject>

#include "bnbmodel.h"

using namespace std;


class Attribute : public BNBModel
{
public:
    Attribute();
     ~Attribute();

    void fromJson(const QJsonObject & obj);
    void toJson(QJsonObject & obj) const;

    QString validation() const;



    QString getRange() const;
    void setRange(const QString &value);

    QString getOffset() const;
    void setOffset(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getName() const;
    void setName(const QString &value);

protected:
    static constexpr const char* RANGE = "range";
    static constexpr const char* OFFSET = "offset";
    static constexpr const char* DESCRIPTION = "description";
    static constexpr const char* NAME = "name";

    QString name;
    QString description;
    QString offset;
    QString range;
};

#endif // ATTRIBUTE_H
