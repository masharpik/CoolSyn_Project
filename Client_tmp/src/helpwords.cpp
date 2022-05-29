#include "levdistance.h"

QList<QString> helpWords() {
    QList<QString> helpwords;
    QFile file(":/paraphrase_russian_a_u.csv");
    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
        qInfo() <<  "Файл не открыт";
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QVector<QString> dataForWord = line.split(",");
        helpwords.append(dataForWord[0]);
    }
    return helpwords;
}
