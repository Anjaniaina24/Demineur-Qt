#ifndef DEMINEUR_HPP
#define DEMINEUR_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QVector>

class Demineur : public QWidget
{
    Q_OBJECT

public:
    explicit Demineur(QWidget *parent = nullptr);
    ~Demineur();

signals:
    void backToMenu();

private slots:
    void onBackClicked();
    void onModeToggleClicked();
    void onCellClicked(int row, int col);
    void onResetClicked();

private:
    int rows;
    int cols;
    int totalMines;
    int remainingBombs;
    bool flagMode;

    QVector<QVector<int>> grid;
    QVector<QVector<bool>> revealed;
    QVector<QVector<bool>> flagged;

    QLabel *bombCountLabel;
    QPushButton *modeButton;
    QPushButton *resetButton;
    QPushButton *backButton;
    QWidget *gridWidget;
    QVector<QVector<QPushButton*>> buttons;

    void initGrid();
    void revealCell(int row, int col);
    void toggleFlag(int row, int col);
    void updateBombCount();
    void checkWin();
    void gameOver(bool won);
    void resetGame();
};

#endif