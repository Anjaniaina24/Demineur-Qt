#ifndef DEMINEUR_HPP
#define DEMINEUR_HPP

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class Demineur : public QWidget
{
    Q_OBJECT
public:
    explicit Demineur(QWidget *parent = nullptr);

private slots:
    void onCaseCliquee(int ligne, int colonne);   // <--- CORRECTION : ajout des paramètres
    void onBasculeMode();
    void onRetourMenu();

private:
    QGridLayout *grille;
    QPushButton *cases[10][10];
    QLabel *labelMines;
    QPushButton *btnBascule;
    QPushButton *btnMenu;

    int nbMines = 10;
    int minesRestantes = 10;
    bool modeDrapeau = false;

    void initialiserGrille();
    void mettreAJourAffichage();
};

#endif // DEMINEUR_HPP