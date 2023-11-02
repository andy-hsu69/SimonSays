#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <simonmodel.h>

MainWindow::MainWindow(SimonModel& model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);

    // ====== connection for normal game mode ======= //
    connect(ui->startButton, &QPushButton::clicked, &model, &SimonModel::gameStartNormal);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::hideButton);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::gameStartButtons);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::changeNormalInstructions);
    connect(&model, &SimonModel::sendMove, this, &MainWindow::buttonFlash);
    connect(ui->redButton, &QPushButton::clicked, this, &MainWindow::redButtonPressed);
    connect(ui->blueButton, &QPushButton::clicked, this, &MainWindow::blueButtonPressed);
    connect(&model, &SimonModel::setProgressRange, this, &MainWindow::setProgressBarRange);
    connect(this, &MainWindow::playerMove, &model, &SimonModel::playerButtonPressed);
    connect(&model, &SimonModel::disablePlayerButtons, this, &MainWindow::disableButtons);
    connect(&model, &SimonModel::enablePlayerButtons, this, &MainWindow::enableButtons);
    connect(&model, &SimonModel::updateProgressBar, ui->progressBar, &QProgressBar::setValue);
    connect(&model, &SimonModel::turnOrder, ui->WinMessage, &QLabel::setText);
    connect(&model, &SimonModel::gameOver, ui->WinMessage, &QLabel::setText);
    connect(&model, &SimonModel::gameOver, this, &MainWindow::youLost);
    connect(&model, &SimonModel::sendRoundSpeed, this, &MainWindow::receiveRoundSpeed);
    connect(&model, &SimonModel::gameOver, this, &MainWindow::resetView);

    // ======= connection for unique feature ======= //
    connect(ui->uniqueButton, &QPushButton::clicked, &model, &SimonModel::gameStartFeature);
    connect(ui->uniqueButton, &QPushButton::clicked, this, &MainWindow::hideButton);
    connect(ui->uniqueButton, &QPushButton::clicked, this, &MainWindow::gameStartButtons);
    connect(ui->uniqueButton, &QPushButton::clicked, this, &MainWindow::changeUniqueInstructions);
}

void MainWindow::buttonFlash(int button)
{
    if(button == 0)
    {
        ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(255,100,100);}"));
        QTimer::singleShot(roundSpeedValue / 2, this, [this]() {ui ->redButton->setStyleSheet("QPushButton {background-color: red;} QPushButton:Pressed {background-color: rgb(255, 100, 100);}");});
    }
    else
    {
        ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(0,191,255);}"));
        QTimer::singleShot(roundSpeedValue / 2, this, [this]() {ui ->blueButton->setStyleSheet("QPushButton {background-color: blue;} QPushButton:Pressed {background-color: rgb(0, 191, 255);}");});
    }
}

void MainWindow::enableButtons()
{
    ui->redButton->setEnabled(true);
    ui->blueButton->setEnabled(true);
}

void MainWindow::disableButtons()
{
    ui->redButton->setDisabled(true);
    ui->blueButton->setDisabled(true);
}

void MainWindow::redButtonPressed()
{
    emit playerMove(0);
}

void MainWindow::blueButtonPressed()
{
    emit playerMove(1);
}

void MainWindow::receiveRoundSpeed(int speed)
{
    roundSpeedValue = speed;
}

void MainWindow::hideButton()
{
    ui->startButton->setVisible(false);
    ui->uniqueButton->setVisible(false);
}

void MainWindow::setProgressBarRange(int range)
{
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(range);
}

void MainWindow::changeNormalInstructions()
{
    ui->InstructMessage->setText("Click on the button that flashes!");
}

void MainWindow::changeUniqueInstructions()
{
    ui->InstructMessage->setText("Don't click on the button that flashes!");
}

void MainWindow::youLost()
{
    ui->redButton->setVisible(false);
    ui->blueButton->setVisible(false);
}

void MainWindow::gameStartButtons()
{
    ui->redButton->setVisible(true);
    ui->blueButton->setVisible(true);
}

void MainWindow::resetView()
{
    ui->startButton->setVisible(true);
    ui->uniqueButton->setVisible(true);
    ui->blueButton->setDisabled(true);
    ui->redButton->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

