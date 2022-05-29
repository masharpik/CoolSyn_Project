#include "levdistance.h"

QList<QString> helpWords() {
    QList<QString> helpwords;
    QFile file(":/paraphrase.csv");
    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
        qInfo() <<  "Файл не открыт";
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QVector<QString> dataForWord;
        auto tmp = line.split(",");
        for (auto &s: tmp) {
            dataForWord.push_back(s);
        }
        helpwords.append(dataForWord[0]);
    }
    return helpwords;
}
