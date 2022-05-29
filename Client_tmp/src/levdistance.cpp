#include "levdistance.h"

int levenshteinDistance(const QString &source, const QString &target) {
    if (source == target) {
        return 0;
    }

    const int sourceCount = source.count();
    const int targetCount = target.count();

    if (source.isEmpty()) {
        return targetCount;
    }

    if (target.isEmpty()) {
        return sourceCount;
    }

    if (sourceCount > targetCount) {
        return levenshteinDistance(target, source);
    }

    QVector<int> column;
    column.fill(0, targetCount + 1);
    QVector<int> previousColumn;
    previousColumn.reserve(targetCount + 1);
    for (int i = 0; i < targetCount + 1; i++) {
        previousColumn.append(i);
    }

    for (int i = 0; i < sourceCount; i++) {
        column[0] = i + 1;
        for (int j = 0; j < targetCount; j++) {
            column[j + 1] = std::min({
                1 + column.at(j),
                1 + previousColumn.at(1 + j),
                previousColumn.at(j) + ((source.at(i) == target.at(j)) ? 0 : 1)
            });
        }
        column.swap(previousColumn);
    }

    return previousColumn.at(targetCount);
}
