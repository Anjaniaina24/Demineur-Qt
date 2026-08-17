#ifndef MENU_HPP
#define MENU_HPP

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = nullptr);

private slots:
    void onJouer();
    void onQuitter();

private:
    QLabel *titre;
    QPushButton *btnJouer;
    QPushButton *btnQuitter;
};

#endif // MENU_HPP