#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <simonmodel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(SimonModel& SimonModel, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    ///
    /// \brief buttonFlash: Flashes either button for a predetermined period of time based on roundSpeed
    /// params: Int representing button
    ///
    void buttonFlash(int);

    ///
    /// \brief resetView Resets the view back to its default state
    ///
    void resetView();

    ///
    /// \brief redButtonPressed
    ///Runs the logic for sending a red button signal to the model
    void redButtonPressed();

    ///
    /// \brief blueButtonPressed
    ///Runs the logic for sending a blue button signal to the model
    void blueButtonPressed();

    ///
    /// \brief yellowButtonPressed
    ///Runs the logic for sending a yellow button signal to the model
    void yellowButtonPressed();

    ///
    /// \brief blueButtonPressed
    ///Runs the logic for sending a green button signal to the model
    void greenButtonPressed();

    ///
    /// \brief disableButtons
    ///Turns off player input buttons
    void disableButtons();

    ///
    /// \brief enableButtons
    ///Turns on player input buttons
    void enableButtons();

    ///
    /// \brief receiveRoundSpeed
    /// \param speed
    ///Takes in round speed from model
    void receiveRoundSpeed(int speed);

    ///
    /// \brief hideButton
    ///Hide disabled buttons
    void hideButton();

    ///
    /// \brief youLost
    ///Displays a loss message
    void youLost();

    ///
    /// \brief gameStartButtons
    ///Runs visual logic for the start game buttons
    void gameStartButtons();

    ///
    /// \brief setProgressBarRange
    /// \param range
    ///Sets bar based on round number
    void setProgressBarRange(int range);

    ///
    /// \brief changeNormalInstructions
    ///Fills in instruction text box with proper text
    void changeNormalInstructions();

    ///
    /// \brief changeUniqueInstructions
    ///Fills in instruction text box with proper text
    void changeUniqueInstructions();

signals:
    void playerMove(int move);

private:
    Ui::MainWindow *ui;
    int roundSpeedValue;
};
#endif // MAINWINDOW_H
