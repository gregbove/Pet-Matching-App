#ifndef ATTRIBUTEPREFERENCE_H
#define ATTRIBUTEPREFERENCE_H

#include <memory>

#include <QString>
#include <QJsonObject>

#include "attribute.h"
#include "bnbmodel.h"
#include "parent.h"

using namespace std;


class AttributePreference : public BNBModel
{
public:
    AttributePreference();
    ~AttributePreference();

    void fromJson(const QJsonObject & obj);
    void toJson(QJsonObject & obj) const;

    QString validation() const;



    int getParentId() const;
    void setParentId(int value);

    shared_ptr<Parent> getParent() const;
    void setParent(const shared_ptr<Parent> &value);

    int getAttributeId() const;
    void setAttributeId(int value);

    shared_ptr<Attribute> getAttribute() const;
    void setAttribute(const shared_ptr<Attribute> &value);

    double getWeight() const;
    void setWeight(double value);

protected:
    static constexpr const char* PARENT_ID = "parentId";
    static constexpr const char* PARENT = "parent";
    static constexpr const char* ATTRIBUTE_ID = "attribute_Id";
    static constexpr const char* ATTRIBUTE = "attribute";
    static constexpr const char* WEIGHT = "weight";

    int parentId;
    shared_ptr<Parent> parent;
    int attributeId;
    shared_ptr<Attribute>attribute;
    double weight;
};

#endif // ATTRIBUTEPREFERENCE_H
