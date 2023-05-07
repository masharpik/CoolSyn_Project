#pragma once

#include "synwindow.h"

#include <QVector>
#include <QString>

#define SYNONYM 1
#define SIMILAR 2

namespace GetSimWords {
    QVector<QString> getSims(QString inputWord, SynWindow *window, int& key);
};
