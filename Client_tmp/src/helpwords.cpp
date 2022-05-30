#include "levdistance.h"
#include "helpwords.h"

QList<QString> helpWords() {
    QList<QString> words;
    QFile file(":/paraphrase.csv");
    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
        qInfo() <<  "Файл не открыт";
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        words.append(line.split(",")[0]);
    }
    return words;
}
