#include "synwindow.h"
#include "tester.h"
#include "getsynsfunc.h"
#include "similarwords.h"
#include "helpwords.h"

using namespace Tester;
using namespace GetSynsFunc;
using namespace GetSimWords;

void SynWindow::onInputButtonClicked() {

    QString inputWord = this->mainPage->inputZone.inputText.text();
    clearOutputScroll(inputWord);
    if (!Tester::testString(inputWord)) {
        QMessageBox::warning(this, "BAN", "Некорректный ввод");
        this->mainPage->inputZone.inputText.clear();
        return;
    }

    int key = 0;
    QVector<QString> syns = getSims(inputWord, this, key);
    if (key == SYNONYM) {
        this->mainPage->outputZone.infoText.setText("Синонимы найдены");
    }
    if (key == SIMILAR) {
        this->mainPage->outputZone.infoText.setText("Возможно, вы имели в виду");
    }
    outputSyns(syns);
}

void SynWindow::outputSyns(QVector<QString> syns) {
    if (syns.length() == 0) {
        QLabel *syn = new QLabel("Нет данных :(");
        this->mainPage->outputZone.scrollLayout->addWidget(syn);
        return;
    }
    for (int i = 0; i < syns.length(); ++i) {
        QPushButton *synButton = new QPushButton(syns[i]);
        connect(synButton, &QPushButton::clicked, this,
                [this, synButton]
                    (bool checked)
                        {this->mainPage->inputZone.inputText.setText(synButton->text());});
        this->mainPage->outputZone.scrollLayout->addWidget(synButton);
    }
}

void SynWindow::clearOutputScroll(QString w) {
    if (this->mainPage->outputZone.scrollWidget) {
        delete this->mainPage;
        this->mainPage = new MainPage();
        pages.insertWidget(0, this->mainPage);
        this->mainPage->inputZone.inputText.setText(w);
        createWindow();
   }
}

void SynWindow::createWindow() {
    connect(&this->mainPage->inputZone.inputButton, &QPushButton::clicked, this, &SynWindow::onInputButtonClicked);
    //connect(&this->mainPage->inputZone.inputText, &QLineEdit::returnPressed, this, &SynWindow::onInputButtonClicked);

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

SynWindow::SynWindow(Widget *parent)
    : Widget(parent),
      mainLayout(this),
      mainPage(new MainPage)

{
    mainLayout.addWidget(&pages);
    pages.insertWidget(0, mainPage);
    createWindow();
}

SynWindow::~SynWindow()
{
}
