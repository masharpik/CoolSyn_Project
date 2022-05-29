#include "getsynsfunc.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QChar>

namespace GetSynsFunc {

    QVector<QString> getSyns(QString inputWord, SynWindow *window) {
        inputWord = makeCorrectWord(inputWord);
        QVector<QString> syns;
        // Открываем файл из ресурсов
        QFile file(":/paraphrase.csv");
        if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
            QMessageBox::warning(window, "BAN", "Ошибка связи с БД");
            syns = {};
            return syns;
        }
        // Создаём поток для извлечения данных из файла
        QTextStream in(&file);
        // Считываем данные до конца файла
        while (!in.atEnd()) {
            // ... построчно
            QString line = in.readLine();
            QVector<QString> dataForWord = line.split(",");
            if (dataForWord[0] == inputWord) {
                for (QString syn : dataForWord[1].split("|")) {
                    syns.push_back(syn);
                }
            }
        }
        return syns;
    }

    QString makeCorrectWord(QString word) {
        QString result = toCapitalize(word);
        return result;
    }

    QString toCapitalize(QString word) {
        QString result = "";
        for (size_t i = 0; i < word.length(); ++i) {
            if (word[i] >= u'А' && word[i] <= u'Я' && i == 0) {
                result += word[i];
            } else if (word[i] >= u'а' && word[i] <= u'я' && i == 0) {
                result += word[i].toUpper();
            } else if (word[i] >= u'А' && word[i] <= u'Я') {
                result += word[i].toLower();
            } else {
                result += word[i];
            }
        }
        return result;
    }
}
