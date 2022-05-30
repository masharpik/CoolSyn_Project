#include "inputzone.h"
#include "helpwords.h"

InputZone::InputZone(QWidget *parent) :
    Widget(parent),
    mainLayout(this),
    infoText("Введите слово:"),
    inputLineLayout(),
    inputText(),
    inputButton("Найти"),
    helpText(helpWords(), &inputText)
{
    mainLayout.addWidget(&infoText);

    inputLineLayout.addWidget(&inputText);
    helpText.setCaseSensitivity(Qt::CaseInsensitive);
    helpText.setMaxVisibleItems(4);
    inputText.setCompleter(&helpText);
    inputText.setObjectName("input");
    inputText.setMaximumHeight(30);

    inputLineLayout.addWidget(&inputButton);

    mainLayout.addLayout(&inputLineLayout);
}
