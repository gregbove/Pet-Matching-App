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


    QString getDescription() const;
    void setDescription(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    int getOffset() const;
    void setOffset(int value);

    int getRange() const;
    void setRange(int value);

protected:
    static constexpr const char* RANGE = "range";
    static constexpr const char* OFFSET = "offset";
    static constexpr const char* DESCRIPTION = "description";
    static constexpr const char* NAME = "name";

    QString name;
    QString description;
    int offset;
    int range;
};

#endif // ATTRIBUTE_H
