#include "synwindow.h"
#include "tester.h"
#include "getsynsfunc.h"

#include <QMessageBox>
#include <QVector>

using namespace Tester;
using namespace GetSynsFunc;

void SynWindow::onInputButtonClicked()
{
    QString inputWord = this->mainPage->inputZone.inputText.text();

    if (!Tester::testString(inputWord)) {
        QMessageBox::warning(this, "BAN", "Некорректный ввод");
        this->mainPage->inputZone.inputText.clear();
    }
    else {
        QMessageBox::information(this, "Введенное слово", inputWord);
        QVector<QString> syns = getSyns(inputWord);
        outputSyns(syns);
    }
}

void SynWindow::outputSyns(QVector<QString> syns) {
    // TODO(Masha): Вывод синонимов в scroll
}

SynWindow::SynWindow(Widget *parent)
    : Widget(parent),
      mainLayout(this),
      mainPage(new MainPage)

{
    mainLayout.addWidget(&pages);
    pages.insertWidget(0, mainPage);
    connect(&mainPage->inputZone.inputButton, &QPushButton::clicked, this, &SynWindow::onInputButtonClicked);
}

SynWindow::~SynWindow()
{
}
