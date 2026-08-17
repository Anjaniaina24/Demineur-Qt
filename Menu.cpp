#include "Menu.hpp"
#include "Demineur.hpp"   // <--- AJOUT pour utiliser la classe Demineur
#include <QApplication>
#include <QMessageBox>
#include <QVBoxLayout>

Menu::Menu(QWidget *parent)
    : QWidget(parent)
{
    titre = new QLabel("Démineur", this);
    titre->setAlignment(Qt::AlignCenter);
    QFont font = titre->font();
    font.setPointSize(36);
    font.setBold(true);
    titre->setFont(font);
    titre->setStyleSheet("color: #2c3e50; padding: 20px;");

    btnJouer = new QPushButton("Jouer", this);
    btnQuitter = new QPushButton("Quitter", this);

    QString styleBouton = 
        "QPushButton {"
        "   background-color: #3498db;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 10px;"
        "   padding: 15px 30px;"
        "   font-size: 18px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2980b9;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #1f618d;"
        "}";
    btnJouer->setStyleSheet(styleBouton);
    btnQuitter->setStyleSheet(styleBouton);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(titre);
    layout->addWidget(btnJouer, 0, Qt::AlignCenter);
    layout->addWidget(btnQuitter, 0, Qt::AlignCenter);
    layout->addStretch();
    layout->setSpacing(30);

    connect(btnJouer, &QPushButton::clicked, this, &Menu::onJouer);
    connect(btnQuitter, &QPushButton::clicked, this, &Menu::onQuitter);

    resize(800, 600);
    setMinimumSize(400, 300);
    setStyleSheet("QWidget { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
                  "stop:0 #ecf0f1, stop:1 #bdc3c7); }");
}

void Menu::onJouer()
{
    this->hide();
    Demineur *jeu = new Demineur();
    jeu->show();
    connect(jeu, &Demineur::destroyed, this, &Menu::show);
}

void Menu::onQuitter()
{
    QApplication::quit();
}