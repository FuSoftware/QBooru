#ifndef QNAMREDIRECT_H
#define QNAMREDIRECT_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

class QNAMRedirect : public QObject
{
    Q_OBJECT
public:
    QNAMRedirect();
    void processUrl(QString url);

    QUrl redirectUrl(const QUrl& possibleRedirectUrl,const QUrl& oldRedirectUrl) const;
    QUrl getLastRedirect();

signals:
    void finished();

public slots:
    void replyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager nam;
    QUrl last_url;
};

#endif // QNAMREDIRECT_H
