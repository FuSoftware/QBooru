#include "qnamredirect.h"

QNAMRedirect::QNAMRedirect()
{
    connect(&nam, SIGNAL (finished(QNetworkReply*)),this, SLOT (replyFinished(QNetworkReply*)));
}

void QNAMRedirect::processUrl(QString url)
{
    QUrl file_url(url);

    //qDebug() << QString("QNAMRedirect::replyFinished: Starting from ").append(file_url.toString());

    QNetworkRequest request(file_url);
    nam.get(request);
}


void QNAMRedirect::replyFinished(QNetworkReply* reply) {
    /*
     * Reply is finished!
     * We'll ask for the reply about the Redirection attribute
     * http://doc.trolltech.com/qnetworkrequest.html#Attribute-enum
     */
    QVariant possibleRedirectUrl =
             reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    /* We'll deduct if the redirection is valid in the redirectUrl function */
    QUrl _urlRedirectedTo = this->redirectUrl(possibleRedirectUrl.toUrl(),_urlRedirectedTo);

    /* If the URL is not empty, we're being redirected. */
    if(!_urlRedirectedTo.isEmpty()) {
        //qDebug() << QString("QNAMRedirect::replyFinished: Redirected to ").append(_urlRedirectedTo.toString());

        /* We'll do another request to the redirection url. */
        this->nam.get(QNetworkRequest(_urlRedirectedTo));
    }
    else {
        /*
         * We weren't redirected anymore
         * so we arrived to the final destination...
         */
        //qDebug() << QString("QNAMRedirect::replyFinished: Arrived to ").append(reply->url().toString());
        last_url = reply->url();
        /* ...so this can be cleared. */
        _urlRedirectedTo.clear();

        emit finished();
    }
    /* Clean up. */
    reply->deleteLater();
}


QUrl QNAMRedirect::redirectUrl(const QUrl& possibleRedirectUrl,
                                             const QUrl& oldRedirectUrl) const {
    QUrl redirectUrl;
    /*
    * Check if the URL is empty and
    * that we aren't being fooled into a infinite redirect loop.
    * We could also keep track of how many redirects we have been to
    * and set a limit to it, but we'll leave that to you.
    */
    if(!possibleRedirectUrl.isEmpty() &&
        possibleRedirectUrl != oldRedirectUrl) {
        redirectUrl = possibleRedirectUrl;
    }
    return redirectUrl;
}

QUrl QNAMRedirect::getLastRedirect()
{
    return this->last_url;
}


