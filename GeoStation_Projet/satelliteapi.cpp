#include "satelliteapi.h"

SatelliteApi::SatelliteApi(ordonnanceur *ord, QObject *parent) : AbstractApi(IdWidget(Satellite),ord,parent)
{
    //request information
    Obs_Latitude=48.871656;
    Obs_Longitude= 2.345931;
    Obs_Altitude=35;
    Seconds=1;
    APIKEY="QSJWEK-UEPBYL-FSPNEM-3X9G";
    BaseUrl="https://www.n2yo.com/rest/v1/satellite";
    NORAD_ID=25544;
    Days_Of_Predic=2;
    Minimun_Visibility=10;
    Minimim_Elevation=30;
    Search_Radius=8;
    API_Function << "tle" << "positions" << "visualpasses" << "radiopasses" << "above";

    //set the function needed for the satellite request
    fonction=above;

    //connection between Manager which request reply;
    connect(manager,SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)),this,SLOT(NetworkStatus(QNetworkAccessManager::NetworkAccessibility)));
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));

    //Set request URL
    for(int i=0;i<50;i++)
    {
        Request_Url(fonction,i);
        manager->get(request);
    }

}


void SatelliteApi::replyFinished(QNetworkReply* reply)
{
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),this, SLOT(slotSslErrors(QList<QSslError>)));

    //Read information from reply
    reply_string=(QString)reply->readAll();
    QJsonParseError jsonError;

    //Initialise un QJsonDocument en format Json avec le contenu en format QString de reply
    MyJsonDoc=QJsonDocument::fromJson(reply_string.toUtf8(),&jsonError);

    //Check for error at json parsing
    if (jsonError.error != QJsonParseError::NoError)
    {
        finish(1);
        return;
    }

    //get satcount and category
    satCount=MyJsonDoc.toVariant().toMap()["info"].toJsonObject().toVariantMap()["satcount"].toInt();
    satCatAny=MyJsonDoc.toVariant().toMap()["info"].toJsonObject().toVariantMap()["category"].toString();

    //get available satellite
    if (satCount!=0 && satCatAny!="ANY")
    {

        //Initialise Above_array avec le tableau above.
        Above_Array=MyJsonDoc.toVariant().toMap()["above"].toJsonArray();

        //Vérifie si le tableau est vide et avise si c'est bien le cas
        if (Above_Array.isEmpty())
        {
            //qDebug()  << QString("%1 JSON Array is empty.").arg(MyJsonDoc.toVariant().toMap()["info"].toJsonObject().toVariantMap()["category"].toString());
            finish(1);
            return;
        }

        //Show infos for each satellite in selected category

        for(int i=0;i<satCount;i++){

            RetrieveInfo("satname",i);
            RetrieveInfo("satid",i);
            RetrieveInfo("launchDate",i);
            RetrieveInfo("satlat",i);
            RetrieveInfo("satlng",i);
            RetrieveInfo("satalt",i);
            //list.push_back(RetrieveInfo("satalt",i));
        }
       }


}
void SatelliteApi::Request_Url(int pos,int category)
{

    switch (pos)
    {
    case tle:
        request.setUrl(QUrl(BaseUrl+"/"+API_Function.value(fonction)+"/"+QString::number(NORAD_ID)+"/&apiKey="+APIKEY));
        break;
    case positions:
        request.setUrl(QUrl(BaseUrl+"/"+API_Function.value(fonction)+"/"+QString::number(NORAD_ID)+"/"+QString::number(latitude)+"/"+QString::number(longitude)+"/"+QString::number(Obs_Altitude)+"/"+QString::number(Seconds)+"/&apiKey="+APIKEY));
        break;
    case visualpasses:
        request.setUrl(QUrl(BaseUrl+"/"+API_Function.value(fonction)+"/"+QString::number(NORAD_ID)+"/"+QString::number(latitude)+"/"+QString::number(longitude)+"/"+QString::number(Obs_Altitude)+"/"+QString::number(Days_Of_Predic)+"/"+QString::number(Minimun_Visibility)+"/&apiKey="+APIKEY));
        break;
    case radiopasses:
        request.setUrl(QUrl(BaseUrl+"/"+API_Function.value(fonction)+"/"+QString::number(NORAD_ID)+"/"+QString::number(latitude)+"/"+QString::number(longitude)+"/"+QString::number(Obs_Altitude)+"/"+QString::number(Days_Of_Predic)+"/"+QString::number(Minimim_Elevation)+"/&apiKey="+APIKEY));
        break;
    case above:
        request.setUrl(QUrl(BaseUrl+"/"+API_Function.value(fonction)+"/"+QString::number(latitude)+"/"+QString::number(longitude)+"/"+QString::number(Obs_Altitude)+"/"+QString::number(Search_Radius)+"/"+QString::number(category)+"/&apiKey="+APIKEY));
        break;

    }
}
void SatelliteApi::RetrieveInfo(QString request, int NumSat)
{

    //request that can be called: {"satid","satname","launchDate","satlat","satlng","satalt"}

    int id;

    if (request == "satid"){id=0;};
    if (request == "satname"){id=1;};
    if (request == "launchDate"){id=2;};
    if (request == "satlat"){id=3;};
    if (request == "satlng"){id=4;};
    if (request == "satalt"){id=5;};

    QMap<QString,QString>   element;

    switch (id)
    {
    case 0:
        element.insert("ID : ",QString::number(Above_Array.at(NumSat).toObject().toVariantMap()["satid"].toInt()));
        break;
    case 1:
        element.insert("Nom : ",QString(Above_Array.at(NumSat).toObject().toVariantMap()["satname"].toString()));
        break;
    case 2:
        element.insert("Date de lancement : ",QString(Above_Array.at(NumSat).toObject().toVariantMap()["launchDate"].toString()));
        break;
    case 3:
        element.insert("Altitude : ",QString::number(Above_Array.at(NumSat).toObject().toVariantMap()["satlat"].toFloat()));
        break;
    case 4:
        element.insert("Longitude : ",QString::number(Above_Array.at(NumSat).toObject().toVariantMap()["satlng"].toFloat()));
        break;
    case 5:
        element.insert("Altitude : ",QString::number(Above_Array.at(NumSat).toObject().toVariantMap()["satalt"].toFloat()));
        break;
    }
    add_list(element);

    //emit send_info(*map_ameliore);

    finish(1);
}
bool SatelliteApi::isMap(){
    return true;
}
bool SatelliteApi::hasBigLayout(){
    return true;
}
void SatelliteApi::slotError(QNetworkReply::NetworkError RequestNetworkError)
{
    if (RequestNetworkError!=0)
    {
        finish(0);
        //qDebug() << "RequestNetwork error" << "\t" << RequestNetworkError;
        return;
    }

}
void SatelliteApi::slotSslErrors(QList<QSslError>(SslErrors))
{
    for(int i=0;i<SslErrors.count();i++)
    {
        if (SslErrors.at(i).error()!=0){
            finish(0);
            //qDebug() << "SSL error" << "\t" << SslErrors.at(i).errorString();
            return;
        }
    }
}
void SatelliteApi::NetworkStatus(QNetworkAccessManager::NetworkAccessibility NetStatus)
{
    if (NetStatus!=1)
    {
        finish(0);
        //qDebug() << "Network Status" << "\t" << NetStatus;
        return;
    }
}
