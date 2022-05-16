#include "widget.h"

#include <QPainter>
#include <QStyleOption>

Widget::Widget(QWidget *parent)
    : QWidget{parent}
{}

void Widget::paintEvent(QPaintEvent *event) {
    QStyleOption opt;

    opt.initFrom(this);

    QPainter p(this);

    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(event);
}
