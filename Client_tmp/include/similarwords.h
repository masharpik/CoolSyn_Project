#pragma once

#include "synwindow.h"

#include <QVector>
#include <QString>

namespace GetSimWords {
    QVector<QString> getSims(QString inputWord, SynWindow *window);
};
