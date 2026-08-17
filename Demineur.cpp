#include "Demineur.hpp"
#include <QMessageBox>
#include <cstdlib>   // pour rand()

Demineur::Demineur(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);

    // Barre d'outils
    QHBoxLayout *barreOutils = new QHBoxLayout();

    labelMines = new QLabel("Mines : 10", this);
    labelMines->setStyleSheet("font-size: 16px; font-weight: bold;");

    btnBascule = new QPushButton("Mode : Pelle", this);
    btnBascule->setStyleSheet("background-color: #f39c12; color: white; padding: 5px 15px;");

    btnMenu = new QPushButton("Menu", this);
    btnMenu->setStyleSheet("background-color: #e74c3c; color: white; padding: 5px 15px;");

    barreOutils->addWidget(labelMines);
    barreOutils->addWidget(btnBascule);
    barreOutils->addStretch();
    barreOutils->addWidget(btnMenu);

    // Grille
    grille = new QGridLayout();
    initialiserGrille();

    layoutPrincipal->addLayout(barreOutils);
    layoutPrincipal->addLayout(grille);

    connect(btnBascule, &QPushButton::clicked, this, &Demineur::onBasculeMode);
    connect(btnMenu, &QPushButton::clicked, this, &Demineur::onRetourMenu);

    setWindowTitle("Démineur");
    resize(600, 600);
}

void Demineur::initialiserGrille()
{
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            QPushButton *btn = new QPushButton();
            btn->setFixedSize(40, 40);
            btn->setStyleSheet("background-color: #95a5a6; border: 1px solid #7f8c8d;");
            cases[i][j] = btn;
            // Capture des indices par valeur (i, j)
            connect(btn, &QPushButton::clicked, [this, i, j]() {
                onCaseCliquee(i, j);
            });
            grille->addWidget(btn, i, j);
        }
    }
}

void Demineur::onCaseCliquee(int ligne, int colonne)
{
    QPushButton *btn = cases[ligne][colonne];
    if (modeDrapeau) {
        if (btn->text() == "🚩") {
            btn->setText("");
            minesRestantes++;
        } else {
            btn->setText("🚩");
            minesRestantes--;
        }
    } else {
        // Simulation (à remplacer par la vraie logique plus tard)
        int val = rand() % 9;
        if (val == 0) {
            btn->setText("");
        } else if (val == 8) {
            btn->setText("💣");
            btn->setStyleSheet("background-color: red;");
            QMessageBox::critical(this, "Perdu !", "Vous avez cliqué sur une mine !");
        } else {
            btn->setText(QString::number(val));
        }
        btn->setEnabled(false);
        btn->setStyleSheet("background-color: #bdc3c7;");
    }
    mettreAJourAffichage();
}

void Demineur::onBasculeMode()
{
    modeDrapeau = !modeDrapeau;
    if (modeDrapeau) {
        btnBascule->setText("Mode : Drapeau");
        btnBascule->setStyleSheet("background-color: #e67e22; color: white;");
    } else {
        btnBascule->setText("Mode : Pelle");
        btnBascule->setStyleSheet("background-color: #f39c12; color: white;");
    }
}

void Demineur::onRetourMenu()
{
    this->close();
}

void Demineur::mettreAJourAffichage()
{
    labelMines->setText("Mines : " + QString::number(minesRestantes));
}