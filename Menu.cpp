#include "Menu.hpp"
#include "Demineur.hpp"
#include <QVBoxLayout>
#include <QApplication>
#include <QLabel>

Menu::Menu(QWidget *parent) : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    stackedWidget = new QStackedWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->addWidget(stackedWidget);

    menuPage = new QWidget(this);
    menuPage->setStyleSheet("background: #c0c0c0;");

    QLabel *title = new QLabel("💣  DÉMINEUR  💣", menuPage);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "QLabel {"
        "  color: #2c3e50;"
        "  font: bold 42px 'Arial Black';"
        "  background: #ecf0f1;"
        "  border: 4px solid #2c3e50;"
        "  border-radius: 15px;"
        "  padding: 20px;"
        "  margin: 20px;"
        "}"
    );

    jouerButton = new QPushButton("🔍  Nouvelle Partie", menuPage);
    quitterButton = new QPushButton("❌  Quitter", menuPage);

    QString styleBouton =
        "QPushButton {"
        "  background: #ecf0f1;"
        "  color: #2c3e50;"
        "  font: bold 24px 'Arial';"
        "  border: 3px solid #7f8c8d;"
        "  border-radius: 10px;"
        "  padding: 15px 40px;"
        "  margin: 8px;"
        "}"
        "QPushButton:hover {"
        "  background: #bdc3c7;"
        "  border-color: #2c3e50;"
        "}"
        "QPushButton:pressed {"
        "  background: #95a5a6;"
        "  border-color: #2c3e50;"
        "}";

    jouerButton->setStyleSheet(styleBouton);
    quitterButton->setStyleSheet(styleBouton);

    QVBoxLayout *menuLayout = new QVBoxLayout(menuPage);
    menuLayout->addStretch();
    menuLayout->addWidget(title, 0, Qt::AlignCenter);
    menuLayout->addStretch();
    menuLayout->addWidget(jouerButton, 0, Qt::AlignCenter);
    menuLayout->addWidget(quitterButton, 0, Qt::AlignCenter);
    menuLayout->addStretch();

    gamePage = new Demineur();
    connect(gamePage, &Demineur::backToMenu, this, &Menu::goToMenu);

    stackedWidget->addWidget(menuPage);
    stackedWidget->addWidget(gamePage);

    connect(jouerButton, &QPushButton::clicked, this, &Menu::goToGame);
    connect(quitterButton, &QPushButton::clicked, QApplication::instance(), &QApplication::quit);

    resize(700, 600);
    setWindowTitle("Démineur");
}

Menu::~Menu() {}

void Menu::goToGame()
{
    stackedWidget->setCurrentIndex(1);
}

void Menu::goToMenu()
{
    stackedWidget->setCurrentIndex(0);
}