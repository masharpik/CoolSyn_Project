/********************************************************************************
** Form generated from reading UI file 'syn_window.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYN_WINDOW_H
#define UI_SYN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_syn_window
{
public:

    void setupUi(QWidget *syn_window)
    {
        if (syn_window->objectName().isEmpty())
            syn_window->setObjectName(QString::fromUtf8("syn_window"));
        syn_window->resize(800, 600);

        retranslateUi(syn_window);

        QMetaObject::connectSlotsByName(syn_window);
    } // setupUi

    void retranslateUi(QWidget *syn_window)
    {
        syn_window->setWindowTitle(QCoreApplication::translate("syn_window", "syn_window", nullptr));
    } // retranslateUi

};

namespace Ui {
    class syn_window: public Ui_syn_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYN_WINDOW_H
