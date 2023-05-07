#include "tester.h"

#include <QChar>

namespace Tester {
    bool testString(QString s)
    {
    if (s == "") {
            return false;
        }
        for (auto c: s) {
            if (!(c >= u'А' && c <= u'Я' || c >= u'а' && c <= u'я' || c == '!' || c == '?' || c == ' ' || c == '+' || c == '-')) {
                return false;
            }
        }
        return true;
    }
}
