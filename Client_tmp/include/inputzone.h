#pragma once

#include "widget.h"
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QCompleter>
#include <QList>
#include <QString>


class InputZone : public Widget
{
    Q_OBJECT
    friend class MainPage;
    friend class SynWindow;
public:

    InputZone(QWidget* parent = nullptr);

private:
    QVBoxLayout mainLayout;
        QLabel infoText;
        QHBoxLayout inputLineLayout;
            QLineEdit inputText;
            QCompleter helpText;
            QList<QString> listHelpWords;
            QPushButton inputButton;
};
