#pragma once

#include "widget.h"
#include "inputzone.h"
#include "mainpage.h"

#include <QWidget>
#include <QTextEdit>
#include <QStackedWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>
#include <QVector>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class syn_window; }
QT_END_NAMESPACE

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
    QStackedWidget pages;
    QVBoxLayout mainLayout;
    MainPage* mainPage;
};
