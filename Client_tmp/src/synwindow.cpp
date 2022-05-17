#include "synwindow.h"
#include "tester.h"
#include "getsynsfunc.h"

#include <QMessageBox>
#include <QVector>
#include <QLabel>

using namespace Tester;
using namespace GetSynsFunc;

void SynWindow::onInputButtonClicked()
{
    QString inputWord = this->mainPage->inputZone.inputText.text();

    clearOutputScroll(inputWord);
    if (!Tester::testString(inputWord)) {
        QMessageBox::warning(this, "BAN", "Некорректный ввод");
        this->mainPage->inputZone.inputText.clear();
        return;
    }

    QVector<QString> syns = getSyns(inputWord, this);
    outputSyns(syns);
    return;
}

void SynWindow::outputSyns(QVector<QString> syns) {
    if (syns.length() == 0) {
        QLabel *syn = new QLabel("Нет данных :(");
        this->mainPage->outputZone.scrollLayout->addWidget(syn);
        return;
    }
    for (int i = 0; i < syns.length(); ++i) {
        QLabel *syn = new QLabel(syns[i]);
        this->mainPage->outputZone.scrollLayout->addWidget(syn);
    }
}

void SynWindow::clearOutputScroll(QString w) {
    if (this->mainPage->outputZone.scrollWidget) {
        delete this->mainPage;
        this->mainPage = new MainPage();
        pages.insertWidget(0, this->mainPage);
        this->mainPage->inputZone.inputText.setText(w);
        connect(&this->mainPage->inputZone.inputButton, &QPushButton::clicked, this, &SynWindow::onInputButtonClicked);
        this->mainPage->inputZone.infoText.setObjectName("infoTextInputZone");
        this->setStyleSheet("#infoTextInputZone {"
                            "border-radius: 5px;"
                            "font-size: 16px;"
                            "border: 2px solid #8000ff;"
                            "color: #8000ff;"
                            "font: bold;"
                            "padding: 6px;"
                            "}");
        this->mainPage->outputZone.infoText.setObjectName("infoTextOutputZone");
        this->mainPage->outputZone.setStyleSheet("#infoTextOutputZone {"
                            "border-radius: 5px;"
                            "font-size: 16px;"
                            "border: 2px solid #8000ff;"
                            "color: #8000ff;"
                            "font: bold;"
                            "padding: 6px;"
                            "}");
    }
}

SynWindow::SynWindow(Widget *parent)
    : Widget(parent),
      mainLayout(this),
      mainPage(new MainPage)

{
    mainLayout.addWidget(&pages);

    // Этот момент повторяется в очищении скролла, надо убрать эти костыли потом
    pages.insertWidget(0, mainPage);
    connect(&this->mainPage->inputZone.inputButton, &QPushButton::clicked, this, &SynWindow::onInputButtonClicked);
    this->mainPage->inputZone.infoText.setObjectName("infoTextInputZone");
    this->setStyleSheet("#infoTextInputZone {"
                        "border-radius: 5px;"
                        "font-size: 16px;"
                        "border: 2px solid #8000ff;"
                        "color: #8000ff;"
                        "font: bold;"
                        "padding: 6px;"
                        "}");
    this->mainPage->outputZone.infoText.setObjectName("infoTextOutputZone");
    this->mainPage->outputZone.setStyleSheet("#infoTextOutputZone {"
                        "border-radius: 5px;"
                        "font-size: 16px;"
                        "border: 2px solid #8000ff;"
                        "color: #8000ff;"
                        "font: bold;"
                        "padding: 6px;"
                        "}");
}

SynWindow::~SynWindow()
{
}
