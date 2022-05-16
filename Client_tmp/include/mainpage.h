#pragma once

#include "widget.h"
#include "inputzone.h"
#include "outputzone.h"

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>

class MainPage : public Widget
{
    Q_OBJECT
    friend class SynWindow;

public:

    MainPage();

private:

    QVBoxLayout mainPageLayout;
    InputZone inputZone;
    OutputZone outputZone;
};
