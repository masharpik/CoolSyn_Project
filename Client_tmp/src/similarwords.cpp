#include "similarwords.h"
#include "levdistance.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>

const int MAXSIMWORDS = 6;

namespace GetSimWords {

    QVector<QString> getSims(QString inputWord, SynWindow *window) {

        QVector<QString> simWords(MAXSIMWORDS, inputWord);
        QVector<int> keys(MAXSIMWORDS, inputWord.length());

        QFile file(":/paraphrase.csv");
        if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
            QMessageBox::warning(window, "BAN", "Ошибка связи с БД");
            return simWords;
        }
        QTextStream in(&file);
        int numberOfSims = 0;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QVector<QString> dataForWord = line.split(",");
            int levdistanse = levenshteinDistance(inputWord.toLower(), dataForWord[0].toLower());
            if (levdistanse < inputWord.length()) {
                if (numberOfSims < MAXSIMWORDS) {
                    ++numberOfSims;
                }
                for (int i = 0; i < MAXSIMWORDS; ++i) {
                    if (levdistanse < keys[i]) {
                        for (int j = numberOfSims - 1; j > i; --j) {
                            keys[j] = keys[j - 1];
                            simWords[j] = simWords[j - 1];
                        }
                        keys[i] = levdistanse;
                        simWords[i] = dataForWord[0];
                        break;
                    }
                }
            }
        }
        simWords.resize(numberOfSims);
        return simWords;
    }
}
