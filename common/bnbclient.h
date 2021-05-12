#ifndef BNBCLIENT_H
#define BNBCLIENT_H

#include "bnbrequest.h"
#include "bnbresponse.h"
#include "parent.h"
#include "shelterowner.h"
#include "administrator.h"

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

/**
 * @brief A web API client for Bread-N-Butter server
 *
 * Create an instance of this class with a provided base-url to a running
 * BNB server instance and use public methods to send requests. The
 * coorisponding responses will trigger the Failed/Succeeded signal
 * of the same name. Basically the signals are callbacks for each request.
 */
class BNBClient : public QObject
{
    Q_OBJECT
public:
    explicit BNBClient(QUrl baseUrl, QObject *parent = nullptr);

    void postLogin(User & u);

    /**
     * @brief Queue a getParents request
     *
     * Receive the result from getParentsFailed or getParentsSucceeded
     */
    void getParents();

    void postParent(Parent & p);

signals:
    void postLoginFailed(QString err);
    void postLoginSucceeded(shared_ptr<BNBModel> user, UserType uType);

    void getParentsFailed(QString err);
    void getParentsSucceeded(QVector<shared_ptr<Parent>> parents);

    void postParentFailed(QString err);
    void postParentSucceeded(const shared_ptr<Parent> & parent);

private slots:
    void postLoginFinish();
    void getParentsFinish();
    void postParentFinish();

private:
    QUrl base;
    QNetworkAccessManager man;

    BNBResponse * parse(QNetworkReply * reply);
};

#endif // BNBCLIENT_H
