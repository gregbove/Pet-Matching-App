#ifndef BNBCLIENT_H
#define BNBCLIENT_H

#include "bnbrequest.h"
#include "bnbresponse.h"
#include "parent.h"

#include <memory>

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>
#include <QString>

using namespace std;

class BNBClient : public QObject
{
    Q_OBJECT
public:
    explicit BNBClient(QUrl baseUrl, QObject *parent = nullptr);

    void getParents();

signals:
    void getParentsFailed(QString err);
    void getParentsSucceeded(QVector<shared_ptr<Parent>> parents);

private slots:
    void getParentsFinish();

private:
    QUrl base;
    QNetworkAccessManager man;

    BNBResponse * parse(QNetworkReply * reply);
};

#endif // BNBCLIENT_H
