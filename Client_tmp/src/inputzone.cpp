#include "inputzone.h"



InputZone::InputZone(QWidget *parent) :
    Widget(parent),
    mainLayout(this),
    infoText("Введите текст:"),
    inputLineLayout(),
    inputText(),
    inputButton("Найти")
{
    mainLayout.addWidget(&infoText);

//    infoText.setObjectName("ourText");

    inputLineLayout.addWidget(&inputText);
    inputText.setObjectName("input");
    inputText.setMaximumHeight(30);

    inputLineLayout.addWidget(&inputButton);

    mainLayout.addLayout(&inputLineLayout);

//    setStyleSheet("#ourText {"
//                  "color:red;"
//                  "}"
//                  "#input {"
//                  "height: 40px;}");
//    mainLayout.setAlignment(Qt::AlignTop);
    mainLayout.setSizeConstraint(QBoxLayout::SetFixedSize);



}
