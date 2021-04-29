#include "attributepreference.h"

AttributePreference::AttributePreference()
{
    attributeId = 0;
    parentId = 0;
    weight = 0;
}

AttributePreference::~AttributePreference()
{

}

void AttributePreference::fromJson(const QJsonObject &j)
{
    BNBModel::fromJson(j); // BNBModel must add the id


    if (j.contains(PARENT_ID) && j[PARENT_ID].isString())
        parentId = j[PARENT_ID].toInt();

    if (j.contains(ATTRIBUTE_ID) && j[ATTRIBUTE_ID].isString())
        attributeId = j[ATTRIBUTE_ID].toInt();

    if (j.contains(PARENT) && j[PARENT].isObject()){
        Parent parentObj;
        parentObj.fromJson(j[PARENT].toObject());
        parent = make_shared< Parent >( parentObj );
    }

    if (j.contains(ATTRIBUTE) && j[ATTRIBUTE].isObject()){
        Attribute attributeObj;
        attributeObj.fromJson(j[ATTRIBUTE].toObject());
        attribute = make_shared< Attribute >( attributeObj );
    }

    if (j.contains(WEIGHT) && j[WEIGHT].isDouble())
        weight = j[WEIGHT].toDouble();
}

void AttributePreference::toJson(QJsonObject &j) const
{
    BNBModel::toJson(j); // BNBModel must add the id

    QJsonObject attributeObj;
    attribute->toJson(attributeObj);

    QJsonObject parentObj;
    parent->toJson(parentObj);

    j[ATTRIBUTE] = attributeObj;
    j[PARENT] = parentObj;
    j[ATTRIBUTE_ID] = attributeId;
    j[PARENT_ID] = parentId;
    j[WEIGHT] = WEIGHT;

}

QString AttributePreference::validation() const
{
    QString v;

    if(parent == nullptr)
        v += "parent should not be null\n";

    if(parentId <= 0)
        v += "parent id should not be negative or zero\n";


    if(attribute == nullptr)
        v += "attribute should not be null\n";

    if(attributeId <= 0)
        v += "attribute id should not be negative or zero\n";

    if (weight < 0)
        v += "weight must not be negative\n";

    return v;
}

int AttributePreference::getParentId() const
{
    return parentId;
}

void AttributePreference::setParentId(int value)
{
    parentId = value;
}

shared_ptr<Parent> AttributePreference::getParent() const
{
    return parent;
}

void AttributePreference::setParent(const shared_ptr<Parent> &value)
{
    parent = value;
}

int AttributePreference::getAttributeId() const
{
    return attributeId;
}

void AttributePreference::setAttributeId(int value)
{
    attributeId = value;
}

shared_ptr<Attribute> AttributePreference::getAttribute() const
{
    return attribute;
}

void AttributePreference::setAttribute(const shared_ptr<Attribute> &value)
{
    attribute = value;
}

double AttributePreference::getWeight() const
{
    return weight;
}

void AttributePreference::setWeight(double value)
{
    weight = value;
}
