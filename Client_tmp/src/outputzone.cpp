#include "outputzone.h"

OutputZone::OutputZone(QWidget *parent) :
    Widget(parent),
    mainLayout(this),
    infoText("Синонимы"),
    scrollWidget(new Widget()),
    scrollLayout(),
    scrollSyn()
{
    mainLayout.addWidget(&infoText);

    scrollWidget->setLayout(&scrollLayout);
    scrollSyn.setWidget(scrollWidget);
    scrollSyn.setWidgetResizable(true);
    mainLayout.addWidget(&scrollSyn);
}
