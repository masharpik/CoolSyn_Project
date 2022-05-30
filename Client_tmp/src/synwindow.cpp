#include "synwindow.h"
#include "tester.h"
#include "similarwords.h"
#include "helpwords.h"
#include "getsynsfunc.h"

using namespace Tester;
using namespace GetSimWords;
using namespace GetSynsFunc;

void SynWindow::onInputButtonClicked() {

    QString inputWord = this->mainPage->inputZone.inputText.text();

    clearOutputScroll(inputWord);

    if (!Tester::testString(inputWord)) {
        QMessageBox::warning(this, "BAN", "Некорректный ввод");
        this->mainPage->inputZone.inputText.clear();
        return;
    }

//    Client *client = new Client(this);
//    inputWord = this->toCa    pitalize(inputWord);
    QVector<QString> syns;
//    try {
//        syns = client->getSyns(inputWord.toStdString());
//        delete client;
//    } catch (const std::string err) {
        syns = getSyns(inputWord, this);
//    }

    if (syns.length() != 0) {
        this->mainPage->outputZone.infoText.setText("Синонимы слова '" + inputWord + "'");
        outputSyns(syns);
    } else {
        QVector<QString> sims = getSims(inputWord, this);
        if (sims.length() != 0) {
            this->mainPage->outputZone.infoText.setText("Возможно, вы имели в виду");
            outputSyns(sims);
        } else {
            this->mainPage->outputZone.infoText.setText("Не удалось найти синонимы");
        }
    }
    return;
}

void SynWindow::outputSyns(QVector<QString> syns) {
    if (syns.length() == 0) {
        return;
    }
    for (int i = 0; i < syns.length(); ++i) {
        QPushButton *synButton = new QPushButton(syns[i]);
        synButton->setObjectName("wordButton");
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

QString SynWindow::toCapitalize(QString word) {
    QString result = "";
    for (uint i = 0; i < word.length(); ++i) {
        if (word[i] >= u'А' && word[i] <= u'Я' && i == 0) {
            result += word[i];
        } else if (word[i] >= u'а' && word[i] <= u'я' && i == 0) {
            result += word[i].toUpper();
        } else if (word[i] >= u'А' && word[i] <= u'Я') {
            result += word[i].toLower();
        } else {
            result += word[i];
        }
    }
    return result;
}

void SynWindow::createWindow() {
    connect(&this->mainPage->inputZone.inputButton, &QPushButton::clicked, this, &SynWindow::onInputButtonClicked);
    //connect(&this->mainPage->inputZone.inputText, &QLineEdit::returnPressed, this, &SynWindow::onInputButtonClicked);

    //Main window
    mainPage->setMaximumHeight(601);
    mainPage->setMaximumWidth(900);
    mainPage->setMinimumHeight(300);
    mainPage->setMinimumWidth(400);

    this->mainPage->inputZone.infoText.setObjectName("infoTextInputZone");
    this->mainPage->inputZone.inputButton.setObjectName("clickButton");
    this->mainPage->inputZone.inputText.setObjectName("textEdit");
    this->setStyleSheet("#infoTextInputZone {"
                        "border-radius: 5px;"
                        "font-size: 16px;"
                        "border: 2px solid #8000ff;"
                        "color: #8000ff;"
                        "background-color: #FFB8C6;"
                        "font: bold;"
                        "padding: 6px;"
                        "}"
                        "#clickButton {"
                        "color: #FFB8C6;"
                        "background-color: #8000ff;"
                        "border-style: new;"
                        "border-width: 2px;"
                        "border-radius: 10px;"
                        "font: bold 14px;"
                        "padding: 6px;"
                        "}"
                        "#clickButton:pressed {"
                        "color: #8000ff;"
                        "background-color: #CFA2FB;"
                         "}"
                        "#textEdit {"
                        "border-radius: 5px;"
                        "font-size: 16px;"
                        "border: 2px solid #8000ff;"
                        "color: #8000ff;"
                        "font: bold 12px;"
                        "}");


    //Second Label
    this->mainPage->outputZone.infoText.setObjectName("infoTextOutputZone");
    this->mainPage->outputZone.scrollSyn.setObjectName("scrollZone");
    this->mainPage->outputZone.scrollWidget->setObjectName("scroll");
    this->mainPage->outputZone.setStyleSheet("#infoTextOutputZone {"
                        "border-radius: 5px;"
                        "font-size: 16px;"
                        "border: 2px solid #8000ff;"
                        "color: #8000ff;"
                        "font: bold;"
                        "padding: 6px;"
                        "}"
                        "#scrollZone {"
                        "color: #8000ff;"
                        "border-radius: 5px;"
                        "border: 2px solid #8000ff;"
                        "font: bold;"
                        "}"
                        "#scroll {"
                        "background-color: #FFB8C6;"
                        "}"
                        "#wordButton {"
                        "color: #8000ff;"
                        "background-color: #FFB8C6;"
                        "border-style: new;"
                        "border-width: 2px;"
                        "border-radius: 10px;"
                        "font: bold 12px;"
                        "padding: 6px;"
                        "}"
                        "#wordButton:pressed {"
                        "color: #CFA2FB;"
                        "background-color: #8000ff;"
                        "}");
}

SynWindow::SynWindow(Widget *parent)
    : Widget(parent),
      mainLayout(this),
      mainPage(new MainPage)

{
    //mainLayout.setSizeConstraint( QLayout::SetFixedSize );
    mainLayout.addWidget(&pages);
    pages.insertWidget(0, mainPage);
    createWindow();
}

SynWindow::~SynWindow()
{
}
