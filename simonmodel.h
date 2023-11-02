#ifndef SIMONMODEL_H
#define SIMONMODEL_H

#include <vector>
#include <QObject>
#include <QTimer>

class SimonModel : public QObject
{
    Q_OBJECT
private:
    std::vector<int> gameMoves;
    std::vector<int> playerMoves;

    bool playerTurn;
    bool gameActive = false;
    bool featureClicked;
    bool normalClicked;

    void restartGame();
    void restartGameFeature();
    void countTurn(int* turn);

    int timeToWait(int n);
    double progress;
    int roundSpeed;

public:
    explicit SimonModel(QObject *parent = nullptr);

public slots:
    ///
    /// \brief gameStartNormal
    ///Starts a normal game
    void gameStartNormal();

    ///
    /// \brief playerButtonPressed
    ///Verifies the player input and cross references it
    /// with the correct input
    void playerButtonPressed(int);

    ///
    /// \brief startRound
    ///Starts each round and runs the computers turn
    void startRound();

    ///
    /// \brief gameStartFeature
    ///Starts a game with the uniwue instructions
    void gameStartFeature();

    ///
    /// \brief startRoundFeature
    ///Starts each round with the feature instructions
    void startRoundFeature();


signals:
    void sendMove(int);
    void disablePlayerButtons();
    void enablePlayerButtons();
    void updateProgressBar(int);
    void turnOrder(QString);
    void sendRoundSpeed(int);
    void gameOver(QString);
    void setProgressRange(int);
};

#endif // SIMONMODEL_H
