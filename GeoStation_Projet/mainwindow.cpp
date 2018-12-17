#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pollutionapi.h"
#include "pharmacieapi.h"
#include "evenementapi.h"
#include "sncfapi.h"
#include "evenementapi.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //AbstractApi *api_index;
    //SncfApi *sncf_api = new SncfApi(api_index->Sncf);
    /*QList<AbstractApi*> liste_api;
    SncfApi *ev;
    liste_api <<ev;
    AbstractApi *ptr=new lliste_api[0];*/
    //api_index =1
    /*SatelliteApi *satellite_api;
    BorneElectriqueApi *borne_electrique_api;a
    MuseeApi *musee_api;
    AvionApi *avion_api;
    GeolocalisationApi *geolocalisation_api;

    PharmacieApi *pharmacie_api;
    pharmacie_api = new PharmacieApi(this,pharmacie_api->Id);
    MeteoApi *meteo_api;
    PollutionApi *pollution_api;
    EvenementApi *evenement_api;
    evenement_api = new EvenementApi(this,evenement_api->Id);
    VegicrueApi *vegicrue_api;
    pollution_api=new PollutionApi(this,pollution_api->Id);

    liste_api.append(sncf_api);
    liste_api.append(satellite_api);
    liste_api.append(borne_electrique_api);
    liste_api.append(musee_api);
    liste_api.append(avion_api);
    liste_api.append(geolocalisation_api);
    liste_api.append(pharmacie_api);*/

    //liste_api.append(meteo_api);

    //liste_api.append(meteo_api);

    //liste_api.append(pollution_api);
    //liste_api.append(evenement_api);
    //liste_api.append(vegicrue_api);


}

MainWindow::~MainWindow()
{
    delete ui;
}
