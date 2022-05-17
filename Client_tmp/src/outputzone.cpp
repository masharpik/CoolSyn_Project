#include "outputzone.h"

#include <QSize>

OutputZone::OutputZone(QWidget *parent) :
    Widget(parent),
    mainLayout(this),
    infoText("Синонимы"),
    scrollWidget(new Widget()),
    scrollLayout(new QVBoxLayout),
    scrollSyn()
{
    mainLayout.addWidget(&infoText);

    scrollWidget->setLayout(scrollLayout);
    scrollSyn.setWidget(scrollWidget);
    scrollSyn.setWidgetResizable(true);
    mainLayout.addWidget(&scrollSyn);
}
