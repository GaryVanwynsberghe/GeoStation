#ifndef TIMER_H
#define TIMER_H

#include <QTimer>
#include "abstractapi.h"
#include "sncfapi.h"
#include "pollutionapi.h"
#include "pharmacieapi.h"
#include "evenementapi.h"
#include "museesapi.h"
#include "evenementapi.h"
#include "borneelectriqueapi.h"
#include "satelliteapi.h"
#include "nullapi.h"
#include "vigicruesapi.h"
#include "meteoapi.h"
//#include "avionsapi.h"
#include "geolocalisationapi.h"

class ordonnanceur;

class Timer : public QTimer
{

    Q_OBJECT

public:
    Timer(int Id_, ordonnanceur *ord_);
    int Id;
    ordonnanceur *ord;

public slots:
    void send_request();
};

#endif // TIMER_H
