#include "getsynsfunc.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>

namespace GetSynsFunc {



    QVector<QString> getSyns(QString inputWord, SynWindow *window) {
        QVector<QString> syns;
        // Открываем файл из ресурсов
        QFile file(":/paraphrase_russian_a_u.csv");
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
}
