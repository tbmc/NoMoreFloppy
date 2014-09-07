#ifndef VUEGUI_H
#define VUEGUI_H

#include <QWidget>
#include <QMessageBox>
#include <QString>
#include <thread>
#include <mutex>
#include "Controller.h"
#include "vueconsole.h"

namespace Ui {
class VueGUI;
}

class VueGUI : public QWidget
{
    Q_OBJECT

public:
    explicit VueGUI(QWidget *parent = 0);
    ~VueGUI();

    QString getState() const;
    void setState(const QString &value);

private:
    Ui::VueGUI *ui;
    QString state;
    Controller controller;
    std::mutex mutex;
    std::thread *secondaryThread;

    void threadConnexion();

public slots:
    void ipChange(QString newIp);
    void on_connectButton_clicked();
};

#endif // VUEGUI_H
