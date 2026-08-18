#include "Demineur.hpp"
#include <QVBoxLayout>

Demineur::Demineur(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("background: #2c3e50;");

    gameLabel = new QLabel("🎮  JEU DÉMINEUR  🎮", this);
    gameLabel->setAlignment(Qt::AlignCenter);
    gameLabel->setStyleSheet(
        "QLabel {"
        "  color: #ecf0f1;"
        "  font: bold 36px 'Arial Black';"
        "  background: #34495e;"
        "  border: 3px solid #ecf0f1;"
        "  border-radius: 15px;"
        "  padding: 30px;"
        "}"
    );

    retourButton = new QPushButton("↩  Retour au menu", this);
    retourButton->setStyleSheet(
        "QPushButton {"
        "  background: #e74c3c;"
        "  color: white;"
        "  font: bold 20px 'Arial';"
        "  border: none;"
        "  border-radius: 10px;"
        "  padding: 15px 30px;"
        "}"
        "QPushButton:hover {"
        "  background: #c0392b;"
        "}"
        "QPushButton:pressed {"
        "  background: #a93226;"
        "}"
    );

    connect(retourButton, &QPushButton::clicked, this, &Demineur::onBackClicked);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(gameLabel, 0, Qt::AlignCenter);
    layout->addStretch();
    layout->addWidget(retourButton, 0, Qt::AlignCenter);
    layout->addStretch();
}

Demineur::~Demineur() {}

void Demineur::onBackClicked()
{
    emit backToMenu();
}