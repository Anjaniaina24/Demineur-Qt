#include "Demineur.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QMessageBox>
#include <QRandomGenerator>

Demineur::Demineur(QWidget *parent)
    : QWidget(parent),
      rows(9),
      cols(9),
      totalMines(10),
      remainingBombs(totalMines),
      flagMode(false)
{
    setStyleSheet("background: #2c3e50;");

    QHBoxLayout *topBar = new QHBoxLayout();

    bombCountLabel = new QLabel("💣 " + QString::number(remainingBombs), this);
    bombCountLabel->setStyleSheet(
        "QLabel {"
        "  color: #ecf0f1;"
        "  font: bold 20px 'Arial';"
        "  background: #34495e;"
        "  border: 2px solid #ecf0f1;"
        "  border-radius: 8px;"
        "  padding: 5px 15px;"
        "}"
    );

    modeButton = new QPushButton("⛏️", this);
    modeButton->setFixedSize(60, 60);
    modeButton->setStyleSheet(
        "QPushButton {"
        "  background: #f39c12;"
        "  color: white;"
        "  font: bold 28px;"
        "  border: 3px solid #f1c40f;"
        "  border-radius: 30px;"
        "}"
        "QPushButton:hover {"
        "  background: #e67e22;"
        "}"
        "QPushButton:pressed {"
        "  background: #d35400;"
        "}"
    );

    resetButton = new QPushButton("🔄", this);
    resetButton->setFixedSize(60, 60);
    resetButton->setStyleSheet(
        "QPushButton {"
        "  background: #27ae60;"
        "  color: white;"
        "  font: bold 28px;"
        "  border: 3px solid #2ecc71;"
        "  border-radius: 30px;"
        "}"
        "QPushButton:hover {"
        "  background: #229954;"
        "}"
        "QPushButton:pressed {"
        "  background: #1e8449;"
        "}"
    );

    backButton = new QPushButton("✕  Retour", this);
    backButton->setStyleSheet(
        "QPushButton {"
        "  background: #e74c3c;"
        "  color: white;"
        "  font: bold 16px 'Arial';"
        "  border: none;"
        "  border-radius: 8px;"
        "  padding: 8px 18px;"
        "}"
        "QPushButton:hover {"
        "  background: #c0392b;"
        "}"
        "QPushButton:pressed {"
        "  background: #a93226;"
        "}"
    );

    topBar->addWidget(bombCountLabel);
    topBar->addStretch();
    topBar->addWidget(modeButton, 0, Qt::AlignCenter);
    topBar->addWidget(resetButton, 0, Qt::AlignCenter);
    topBar->addStretch();
    topBar->addWidget(backButton, 0, Qt::AlignRight);
    topBar->setContentsMargins(10, 10, 10, 10);

    gridWidget = new QWidget(this);
    gridWidget->setStyleSheet("background: #34495e; border: 2px solid #ecf0f1; border-radius: 10px;");
    QGridLayout *gridLayout = new QGridLayout(gridWidget);
    gridLayout->setSpacing(2);
    gridLayout->setContentsMargins(5, 5, 5, 5);

    buttons.resize(rows);
    for (int r = 0; r < rows; ++r) {
        buttons[r].resize(cols);
        for (int c = 0; c < cols; ++c) {
            QPushButton *btn = new QPushButton("", gridWidget);
            btn->setFixedSize(40, 40);
            btn->setStyleSheet(
                "QPushButton {"
                "  background: #95a5a6;"
                "  border: 1px solid #7f8c8d;"
                "  border-radius: 3px;"
                "  font: bold 14px 'Arial';"
                "  color: #2c3e50;"
                "}"
                "QPushButton:hover {"
                "  background: #bdc3c7;"
                "}"
            );
            connect(btn, &QPushButton::clicked, this, [this, r, c]() {
                onCellClicked(r, c);
            });
            gridLayout->addWidget(btn, r, c);
            buttons[r][c] = btn;
        }
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topBar);
    mainLayout->addWidget(gridWidget, 1);

    connect(backButton, &QPushButton::clicked, this, &Demineur::onBackClicked);
    connect(modeButton, &QPushButton::clicked, this, &Demineur::onModeToggleClicked);
    connect(resetButton, &QPushButton::clicked, this, &Demineur::onResetClicked);

    initGrid();
}

Demineur::~Demineur() {}

void Demineur::initGrid()
{
    grid.resize(rows);
    revealed.resize(rows);
    flagged.resize(rows);
    for (int r = 0; r < rows; ++r) {
        grid[r].resize(cols);
        revealed[r].resize(cols);
        flagged[r].resize(cols);
        for (int c = 0; c < cols; ++c) {
            grid[r][c] = 0;
            revealed[r][c] = false;
            flagged[r][c] = false;
        }
    }

    int placed = 0;
    while (placed < totalMines) {
        int r = QRandomGenerator::global()->bounded(rows);
        int c = QRandomGenerator::global()->bounded(cols);
        if (grid[r][c] != -1) {
            grid[r][c] = -1;
            placed++;
        }
    }

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == -1) continue;
            int count = 0;
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) continue;
                    int nr = r + dr, nc = c + dc;
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == -1)
                        count++;
                }
            }
            grid[r][c] = count;
        }
    }

    remainingBombs = totalMines;
    updateBombCount();
}

void Demineur::resetGame()
{
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            revealed[r][c] = false;
            flagged[r][c] = false;
            buttons[r][c]->setText("");
            buttons[r][c]->setEnabled(true);
            buttons[r][c]->setStyleSheet(
                "QPushButton {"
                "  background: #95a5a6;"
                "  border: 1px solid #7f8c8d;"
                "  border-radius: 3px;"
                "}"
                "QPushButton:hover {"
                "  background: #bdc3c7;"
                "}"
            );
        }
    }

    initGrid();

    flagMode = false;
    modeButton->setText("⛏️");
    modeButton->setStyleSheet(
        "QPushButton {"
        "  background: #f39c12;"
        "  color: white;"
        "  font: bold 28px;"
        "  border: 3px solid #f1c40f;"
        "  border-radius: 30px;"
        "}"
        "QPushButton:hover {"
        "  background: #e67e22;"
        "}"
        "QPushButton:pressed {"
        "  background: #d35400;"
        "}"
    );

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            buttons[r][c]->setEnabled(true);
        }
    }
}

void Demineur::revealCell(int row, int col)
{
    if (row < 0 || row >= rows || col < 0 || col >= cols) return;
    if (revealed[row][col] || flagged[row][col]) return;

    if (grid[row][col] == -1) {
        gameOver(false);
        return;
    }

    revealed[row][col] = true;
    QPushButton *btn = buttons[row][col];
    btn->setStyleSheet(
        "QPushButton {"
        "  background: #ecf0f1;"
        "  border: 1px solid #7f8c8d;"
        "  border-radius: 3px;"
        "  font: bold 14px 'Arial';"
        "  color: #2c3e50;"
        "}"
    );
    if (grid[row][col] > 0) {
        btn->setText(QString::number(grid[row][col]));
        QString color = "#2c3e50";
        if (grid[row][col] == 1) color = "#2980b9";
        else if (grid[row][col] == 2) color = "#27ae60";
        else if (grid[row][col] == 3) color = "#e74c3c";
        else if (grid[row][col] == 4) color = "#8e44ad";
        else if (grid[row][col] == 5) color = "#d35400";
        else if (grid[row][col] == 6) color = "#16a085";
        else if (grid[row][col] == 7) color = "#2c3e50";
        else if (grid[row][col] == 8) color = "#7f8c8d";
        btn->setStyleSheet(
            "QPushButton {"
            "  background: #ecf0f1;"
            "  border: 1px solid #7f8c8d;"
            "  border-radius: 3px;"
            "  font: bold 14px 'Arial';"
            "  color: " + color + ";"
            "}"
        );
    } else {
        btn->setText("");
        QVector<QPair<int,int>> queue;
        queue.append(qMakePair(row, col));
        while (!queue.isEmpty()) {
            QPair<int,int> p = queue.takeFirst();
            int r = p.first;
            int c = p.second;
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) continue;
                    int nr = r + dr, nc = c + dc;
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !revealed[nr][nc] && !flagged[nr][nc]) {
                        if (grid[nr][nc] == -1) continue;
                        revealed[nr][nc] = true;
                        QPushButton *nbtn = buttons[nr][nc];
                        nbtn->setStyleSheet(
                            "QPushButton {"
                            "  background: #ecf0f1;"
                            "  border: 1px solid #7f8c8d;"
                            "  border-radius: 3px;"
                            "  font: bold 14px 'Arial';"
                            "  color: #2c3e50;"
                            "}"
                        );
                        if (grid[nr][nc] > 0) {
                            nbtn->setText(QString::number(grid[nr][nc]));
                            QString color = "#2c3e50";
                            if (grid[nr][nc] == 1) color = "#2980b9";
                            else if (grid[nr][nc] == 2) color = "#27ae60";
                            else if (grid[nr][nc] == 3) color = "#e74c3c";
                            else if (grid[nr][nc] == 4) color = "#8e44ad";
                            else if (grid[nr][nc] == 5) color = "#d35400";
                            else if (grid[nr][nc] == 6) color = "#16a085";
                            else if (grid[nr][nc] == 7) color = "#2c3e50";
                            else if (grid[nr][nc] == 8) color = "#7f8c8d";
                            nbtn->setStyleSheet(
                                "QPushButton {"
                                "  background: #ecf0f1;"
                                "  border: 1px solid #7f8c8d;"
                                "  border-radius: 3px;"
                                "  font: bold 14px 'Arial';"
                                "  color: " + color + ";"
                                "}"
                            );
                        } else {
                            nbtn->setText("");
                            queue.append(qMakePair(nr, nc));
                        }
                    }
                }
            }
        }
    }
    checkWin();
}

void Demineur::toggleFlag(int row, int col)
{
    if (revealed[row][col]) return;
    if (flagged[row][col]) {
        flagged[row][col] = false;
        buttons[row][col]->setText("");
        buttons[row][col]->setStyleSheet(
            "QPushButton {"
            "  background: #95a5a6;"
            "  border: 1px solid #7f8c8d;"
            "  border-radius: 3px;"
            "}"
        );
        remainingBombs++;
    } else {
        flagged[row][col] = true;
        buttons[row][col]->setText("🚩");
        buttons[row][col]->setStyleSheet(
            "QPushButton {"
            "  background: #95a5a6;"
            "  border: 1px solid #7f8c8d;"
            "  border-radius: 3px;"
            "  font: 18px;"
            "}"
        );
        remainingBombs--;
    }
    updateBombCount();
    checkWin();
}

void Demineur::updateBombCount()
{
    bombCountLabel->setText("💣 " + QString::number(remainingBombs));
}

void Demineur::checkWin()
{
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] != -1 && !revealed[r][c]) {
                return;
            }
        }
    }
    gameOver(true);
}

void Demineur::gameOver(bool won)
{
    if (won) {
        QMessageBox::information(this, "Victoire", "🎉 Vous avez gagné !");
    } else {
        QMessageBox::critical(this, "Perdu", "💥 Vous avez cliqué sur une mine !");
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == -1) {
                    buttons[r][c]->setText("💣");
                    buttons[r][c]->setStyleSheet(
                        "QPushButton {"
                        "  background: #e74c3c;"
                        "  border: 1px solid #7f8c8d;"
                        "  border-radius: 3px;"
                        "  font: 16px;"
                        "}"
                    );
                }
            }
        }
    }
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            buttons[r][c]->setEnabled(false);
        }
    }
}

void Demineur::onCellClicked(int row, int col)
{
    if (!buttons[row][col]->isEnabled()) return;
    if (flagMode)
        toggleFlag(row, col);
    else
        revealCell(row, col);
}

void Demineur::onResetClicked()
{
    resetGame();
}

void Demineur::onBackClicked()
{
    emit backToMenu();
}

void Demineur::onModeToggleClicked()
{
    flagMode = !flagMode;
    if (flagMode) {
        modeButton->setText("🚩");
        modeButton->setStyleSheet(
            "QPushButton {"
            "  background: #2980b9;"
            "  color: white;"
            "  font: bold 28px;"
            "  border: 3px solid #3498db;"
            "  border-radius: 30px;"
            "}"
            "QPushButton:hover {"
            "  background: #1f618d;"
            "}"
            "QPushButton:pressed {"
            "  background: #154360;"
            "}"
        );
    } else {
        modeButton->setText("⛏️");
        modeButton->setStyleSheet(
            "QPushButton {"
            "  background: #f39c12;"
            "  color: white;"
            "  font: bold 28px;"
            "  border: 3px solid #f1c40f;"
            "  border-radius: 30px;"
            "}"
            "QPushButton:hover {"
            "  background: #e67e22;"
            "}"
            "QPushButton:pressed {"
            "  background: #d35400;"
            "}"
        );
    }
}
