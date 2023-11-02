 #include "simonmodel.h"

SimonModel::SimonModel(QObject *parent) : QObject(parent)
{

}

// ======== normal feature ========/

void SimonModel::gameStartNormal()
{
    if(!gameActive)
    {
        normalClicked = true;
        gameActive = true;
        emit SimonModel::gameOver("Good Luck!");
        restartGame();
    }
}

void SimonModel::playerButtonPressed(int button)
{
    emit SimonModel::turnOrder("Player's Turn");
    playerMoves.push_back(button);

    if(normalClicked)
    {
        if(playerMoves.back() != gameMoves[playerMoves.size() - 1])
        {
            gameActive = false;
            emit SimonModel::gameOver("Skill issue. Try again?");
            normalClicked = false;
            restartGame();
        }
    }

    if(featureClicked)
    {
        if(playerMoves.back() == gameMoves[playerMoves.size() - 1])
        {
            gameActive = false;
            emit SimonModel::gameOver("Skill issue. Try again?");
            featureClicked = false;
            restartGame();
        }
    }
    emit SimonModel::updateProgressBar(++progress);

    if(playerMoves.size() == gameMoves.size())
    {
        QTimer::singleShot(1000, this, [=]() {startRound();});
        emit SimonModel::turnOrder("Computer's Turn");
    }
}

void SimonModel::startRound()
{
    if(roundSpeed > 250)
    {
        roundSpeed -= 50;
    }
    emit sendRoundSpeed(roundSpeed);
    progress = 0.0;
    emit SimonModel::updateProgressBar(progress);

    playerTurn = false;

    emit SimonModel::disablePlayerButtons();
    gameMoves.push_back(rand() % 4);
    emit SimonModel::setProgressRange(gameMoves.size());

    playerMoves.clear();
    playerMoves.resize(0);

    QTimer::singleShot(timeToWait(gameMoves.size()), this, [=]() {emit enablePlayerButtons();});
    QTimer::singleShot(timeToWait(gameMoves.size()), this, [=]() {playerTurn = true;});

    for(int i = 0; i < (int)gameMoves.size(); i++)
    {
        QTimer::singleShot(roundSpeed * i, this, [=]() {emit sendMove(gameMoves[i]);});
    }
}

void SimonModel::restartGame()
{
    roundSpeed = 1000;
    gameMoves.clear();
    gameMoves.resize(0);
    playerMoves.clear();
    playerTurn = false;
    startRound();
}

// ======== unique feature - doing NOT simon says ========= //

void SimonModel::gameStartFeature()
{
    if(!gameActive)
    {
        gameActive = true;
        featureClicked = true;
        emit SimonModel::gameOver("Good Luck!");
        restartGameFeature();
    }
}

void SimonModel::startRoundFeature()
{
    if(roundSpeed > 250)
    {
        roundSpeed -= 50;
    }
    emit sendRoundSpeed(roundSpeed);
    progress = 0.0;
    emit SimonModel::updateProgressBar(progress);

    playerTurn = false;

    emit SimonModel::disablePlayerButtons();
    gameMoves.push_back(rand() % 4);
    emit SimonModel::setProgressRange(gameMoves.size());

    playerMoves.clear();
    playerMoves.resize(0);

    QTimer::singleShot(timeToWait(gameMoves.size()), this, [=]() {emit enablePlayerButtons();});
    QTimer::singleShot(timeToWait(gameMoves.size()), this, [=]() {playerTurn = true;});

    for(int i = 0; i < (int)gameMoves.size(); i++)
    {
        QTimer::singleShot(roundSpeed * i, this, [=]() {emit sendMove(gameMoves[i]);});
    }
}

void SimonModel::restartGameFeature()
{
    roundSpeed = 1000;
    gameMoves.clear();
    gameMoves.resize(0);
    playerMoves.clear();
    playerTurn = false;
    startRoundFeature();
}

// ======== slots used by both modes ======== //

int SimonModel::timeToWait(int n)
{
    return roundSpeed * n;
}
