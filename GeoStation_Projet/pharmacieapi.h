#ifndef PHARMACIEAPI_H
#define PHARMACIEAPI_H

#include "abstractapi.h"

#include <QtNetwork>


class PharmacieApi : public AbstractApi
{
    Q_OBJECT

public:
    PharmacieApi(int id = 0, QObject *parent = 0);
    ~PharmacieApi();

    QNetworkRequest request;
    QNetworkReply *reply;

private slots:
    void listePharmacie(QNetworkReply *reply);
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError);
    void slotSslErrors(QList<QSslError>);
};

#endif // PHARMACIEAPI_H
