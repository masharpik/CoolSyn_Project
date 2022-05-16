#pragma once

#include "widget.h"

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>

class OutputZone : public Widget
{
    Q_OBJECT
public:
    OutputZone(QWidget* parent = nullptr);

private:
    QVBoxLayout mainLayout;
    QLabel infoText;
    Widget *scrollWidget;
    QVBoxLayout scrollLayout;
    QScrollArea scrollSyn;
};
