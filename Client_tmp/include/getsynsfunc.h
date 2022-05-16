#pragma once

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <QVector>
#include <QString>

namespace GetSynsFunc
{
    class CSVRow {
        public:
            int getId() const;
            std::string getWord() const;

            void readNextRow(std::istream& str);
        private:
            int id;
            std::string word;
    };

    std::istream& operator>>(std::istream& str, CSVRow& data);

    bool clean_word(const std::string word, int& word_id);

    void search_synonyms(std::vector<std::string>& synonyms,const int id);

    QVector<QString> getSyns(QString s);
};
