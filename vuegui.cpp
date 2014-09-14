#include "vuegui.h"
#include "ui_vuegui.h"

VueGUI::VueGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VueGUI)
{
    ui->setupUi(this);
    this->setState("clientserveur");
    this->ui->connectButton->setEnabled(false);

    this->groupesDeWidgets.push_back(this->ui->clientserveur);
    this->groupesDeWidgets.push_back(this->ui->groupConnexion);

    this->setState("clientserveur");
}

VueGUI::~VueGUI()
{
    delete ui;
    if (this->secondaryThread != NULL)
    {
        this->secondaryThread->join();
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
    this->cacherGroupesDeWidgets();
    if(QString::compare(value, "clientserveur", Qt::CaseInsensitive) == 0)
    {
        this->ui->clientserveur->show();
    }
    if(QString::compare(value, "connexion", Qt::CaseInsensitive) == 0)
    {
        this->ui->groupConnexion->show();
    }
}

void VueGUI::cacherGroupesDeWidgets()
{
    for (unsigned int i = 0; i < this->groupesDeWidgets.size(); i++)
    {
        this->groupesDeWidgets.at(i)->hide();
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
        this->setState("clientserveur");
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
    this->setState("connexion");
}
