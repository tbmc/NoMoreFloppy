/********************************************************************************
** Form generated from reading UI file 'vuegui.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VUEGUI_H
#define UI_VUEGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VueGUI
{
public:
    QGridLayout *gridLayout;
    QGroupBox *clientserveur;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit;
    QPushButton *connectButton;
    QPushButton *pushButton;

    void setupUi(QWidget *VueGUI)
    {
        if (VueGUI->objectName().isEmpty())
            VueGUI->setObjectName(QStringLiteral("VueGUI"));
        VueGUI->resize(398, 165);
        gridLayout = new QGridLayout(VueGUI);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        clientserveur = new QGroupBox(VueGUI);
        clientserveur->setObjectName(QStringLiteral("clientserveur"));
        gridLayout_2 = new QGridLayout(clientserveur);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        lineEdit = new QLineEdit(clientserveur);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout_2->addWidget(lineEdit, 0, 0, 1, 1);

        connectButton = new QPushButton(clientserveur);
        connectButton->setObjectName(QStringLiteral("connectButton"));

        gridLayout_2->addWidget(connectButton, 1, 0, 1, 1);

        pushButton = new QPushButton(clientserveur);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_2->addWidget(pushButton, 2, 0, 1, 1);


        gridLayout->addWidget(clientserveur, 0, 0, 1, 1);


        retranslateUi(VueGUI);
        QObject::connect(lineEdit, SIGNAL(textChanged(QString)), VueGUI, SLOT(ipChange(QString)));

        QMetaObject::connectSlotsByName(VueGUI);
    } // setupUi

    void retranslateUi(QWidget *VueGUI)
    {
        VueGUI->setWindowTitle(QApplication::translate("VueGUI", "Form", 0));
        clientserveur->setTitle(QApplication::translate("VueGUI", "Client Serveur", 0));
        lineEdit->setInputMask(QString());
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QApplication::translate("VueGUI", "Adresse IP du serveur", 0));
        connectButton->setText(QApplication::translate("VueGUI", "Connexion", 0));
        pushButton->setText(QApplication::translate("VueGUI", "Attendre connexion ", 0));
    } // retranslateUi

};

namespace Ui {
    class VueGUI: public Ui_VueGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VUEGUI_H
