#ifndef DEMINEUR_HPP
#define DEMINEUR_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class Demineur : public QWidget
{
    Q_OBJECT

public:
    explicit Demineur(QWidget *parent = nullptr);
    ~Demineur();

signals:
    void backToMenu();   // signal pour revenir au menu

private slots:
    void onBackClicked();

private:
    QPushButton *retourButton;
    QLabel *gameLabel;
};

#endif