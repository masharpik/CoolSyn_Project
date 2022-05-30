#pragma once

#include "widget.h"
#include "inputzone.h"
#include "mainpage.h"
#include "client.h"

#include <QWidget>
#include <QTextEdit>
#include <QStackedWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>
#include <QVector>
#include <QMessageBox>

class SynWindow : public Widget {
    Q_OBJECT

public slots:
    void onInputButtonClicked();

public:
    SynWindow(Widget *parent = nullptr);
    ~SynWindow();
    void outputSyns(QVector<QString> syns);
    void clearOutputScroll(QString w);
    void createWindow();

private:

    QString toCapitalize(QString word);

    QStackedWidget pages;
    QVBoxLayout mainLayout;
    MainPage* mainPage;
};
