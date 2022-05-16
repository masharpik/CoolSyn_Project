#include "getsynsfunc.h"

namespace GetSynsFunc {
    int CSVRow::getId() const {
        return id;
    }
    std::string CSVRow::getWord() const {
        return word;
    }

    void CSVRow::readNextRow(std::istream& str) {
        std::string id_str;
        std::string new_word;
        std::getline(str, id_str, ',');
        std::getline(str, new_word, '\n');
        new_word.erase(std::remove_if(new_word.begin(), new_word.end(), ::isspace), new_word.end());
        word = new_word;
        id = std::stoi(id_str);
    }

    std::istream& operator>>(std::istream& str, CSVRow& data) {
        data.readNextRow(str);
        return str;
    }

    bool clean_word(const std::string word, int& word_id) {
        std::ifstream  file("word.csv");
        CSVRow         row;
        while (file >> row) {
            if (row.getWord().empty()) {
                return 0;
            }
            if (word.compare(row.getWord()) == 0) {
                word_id = row.getId();
                return 1;
            }
        }
        return 0;
    }

    void search_synonyms(std::vector<std::string>& synonyms,const int id) {
        int flag = 0;
        synonyms.clear();
        std::ifstream  file("synonyms.csv");
        CSVRow         row;
        while (file >> row) {
            if (row.getId() == id) {
                synonyms.push_back(row.getWord());
                flag = 1;
            }
            if (flag == 1) {
                return;
            }
        }
    }

    QVector<QString> getSyns(QString word) {
        std::string word_read = word.toStdString();
        word_read.erase(std::remove_if(word_read.begin(), word_read.end(), ::isspace), word_read.end());
        int id;
        std::vector<std::string> synonyms;
        if (!clean_word(word_read, id)) {
            //Ошибка
        }
        else {
            search_synonyms(synonyms, id);
        }
        QVector<QString> syns;
        std::transform(synonyms.begin(), synonyms.end(), std::back_inserter(syns), [](const std::string &v){ return QString::fromStdString(v); });
        return syns;
    }
}
