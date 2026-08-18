#ifndef MENU_HPP
#define MENU_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>

class Demineur; // forward declaration

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void goToGame();   // bascule vers la vue jeu
    void goToMenu();   // bascule vers la vue menu

private:
    QStackedWidget *stackedWidget;
    QWidget *menuPage;
    Demineur *gamePage;
    QPushButton *jouerButton;
    QPushButton *quitterButton;
};

#endif