#include "vuegui.h"
#include "ui_vuegui.h"

VueGUI::VueGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VueGUI)
{
    ui->setupUi(this);
    this->setState("clientserveur");
    this->ui->connectButton->setEnabled(false);
}

VueGUI::~VueGUI()
{
    delete ui;
    this->secondaryThread->join();
    if (this->secondaryThread != NULL)
    {
        delete this->secondaryThread;
    }
}

QString VueGUI::getState() const
{
    return state;
}

void VueGUI::setState(const QString &value)
{
    state = value;
    this->ui->clientserveur->hide();
    if(QString::compare(value, "clientserveur", Qt::CaseInsensitive) == 0)
    {
        this->ui->clientserveur->show();
    }
}

void VueGUI::threadConnexion()
{
    QByteArray toCharArray = this->ui->lineEdit->text().toLocal8Bit();
    const char *ip = toCharArray.data();
    STATUT t = controller.connect(ip);
    if (t == Ok)
    {
        std::cout << "Connecté" << std::endl;
    }
    else
    {
        std::cout << "Erreur : " << t << std::endl;
    }
}


void VueGUI::ipChange(QString newIp)
{
    QByteArray toCharArray = newIp.toLocal8Bit();
    const char *ip = toCharArray.data();

    if (VueConsole::isIpCorrect(ip))
    {
        this->ui->connectButton->setEnabled(true);
    }
    else
    {
        this->ui->connectButton->setEnabled(false);
    }
}

void VueGUI::on_connectButton_clicked()
{
    this->secondaryThread = new std::thread(&VueGUI::threadConnexion, this);
}
