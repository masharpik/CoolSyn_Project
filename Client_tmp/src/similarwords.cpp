#include "similarwords.h"
#include "levdistance.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#define MaxSimWords 6

namespace GetSimWords {

    QVector<QString> getSims(QString inputWord, SynWindow *window, int& key) {

        QVector<QString> sim_words(MaxSimWords,inputWord);
        QVector<int> keys(MaxSimWords,inputWord.length());

        QFile file(":/paraphrase_russian_a_u.csv");
        if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
            QMessageBox::warning(window, "BAN", "Ошибка связи с БД");
            return sim_words;
        }
        QTextStream in(&file);
        int numberofsims = 0;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QVector<QString> dataForWord = line.split(",");
            int levdistanse = levenshteinDistance(inputWord.toLower(), dataForWord[0].toLower());
            if (!levdistanse) {
                key = SYNONYM;
                QVector<QString> syns = {};
                for (QString syn : dataForWord[1].split("|")) {
                    syns.push_back(syn);
                }
                return syns;
            }
            if (levdistanse < inputWord.length()) {
                if (numberofsims < MaxSimWords) {
                    ++numberofsims;
                }
                for (int i = 0; i < MaxSimWords; ++i) {
                    if (levdistanse < keys[i]) {
                        for (int j = numberofsims-1; j > i; --j) {
                            keys[j] = keys[j-1];
                            sim_words[j] = sim_words[j-1];
                        }
                        keys[i] = levdistanse;
                        sim_words[i] = dataForWord[0];
                        break;
                    }
                }
            }
        }
        if (numberofsims) {
            key = SIMILAR;
        }
        sim_words.resize(numberofsims);
        return sim_words;
    }
}
