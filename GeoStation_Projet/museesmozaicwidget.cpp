#include "museesmozaicwidget.h"
#include "ui_museesmozaicwidget.h"

MuseesMozaicWidget::MuseesMozaicWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MuseesMozaicWidget)
{
    ui->setupUi(this);
}

MuseesMozaicWidget::~MuseesMozaicWidget()
{
    delete ui;
}

void MuseesMozaicWidget::receive_info(QMap<QString, QString> map_formulaire)
{
    //ui->tableWidget->refresh(map_formulaire);
}
