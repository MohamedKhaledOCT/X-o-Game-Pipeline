#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <string>
#include <algorithm>
#include <functional>
#include <iterator>
#include <sstream>
#include <iomanip>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void handleButtonClick(int row, int col);
    void startSinglehard();
    void startSingleeasy();
    void startSinglemedium();
    void startTwoPlayerGame();
    void last_game_history_func();
    void registerClicked();
    void loginClicked();
    void Profile_func();
    void add_win(int id);
    void add_lose(int id);

private:

    QPushButton *buttons[3][3];
    QLabel  *statusLabel;
    QLabel  *statusLabel_profile_username;
    QLabel  *statusLabel_profile_wins;
    QLabel  *statusLabel_profile_loses;
    QLabel  *statusLabel_profile_username2;
    QLabel  *statusLabel_profile_wins2;
    QLabel  *statusLabel_profile_loses2;

    QPushButton *hard;
    QPushButton *twoPlayerButton;
    QPushButton *easy;
    QPushButton *medium;
    QPushButton *last_game_history;
    QPushButton *path_one_player;
    QPushButton *path_two_player;
    QPushButton *back;
    QPushButton *return_current_game;
    bool isPlayerTurn;
    bool isSinglePlayerMode;
    int board[3][3];
    int History [3][3];
    int History2 [3][3];
    void initializeGame();
    void updateBoard(int row, int col, char symbol);
    bool checkWin(char symbol);
    bool checkTie();
    void computerMove();
    int level;
    int mode;
    int change_history;
    int current_player_id1;
    int current_player_id2;
    void fun_one_player();
    void fun_two_player();
    void fun_back();
    void fun_return();
    bool back_mode;

    QString login_username1;
    QString login_password1;

    QString login_username2;
    QString login_password2;





    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Ui::MainWindow *ui;
    QLabel *empty;
    QLabel *label_username1;
    QLabel *label_username2;

    QGridLayout *gridLayout;
    QLabel *label_password1;
    QLabel *label_password2;

    QLabel *player1;
    QLabel *player2;

    QLabel *player1_playing_screen;
    QLabel *player2_playing_screen;

    QLabel * label_profile_username1  ;
    QLabel * label_profile_username2  ;
    QLabel * label_profile_wins1 ;
    QLabel * label_profile_wins2 ;
    QLabel * label_profile_loses1;
    QLabel * label_profile_loses2;


    QLabel * welecome_word;
    QLabel * welecome_question;

    QLabel * having_account;

    QPushButton* button_register;
    QPushButton* button_login;

    QPushButton* yes_have;
    QPushButton* no_have;

    QLineEdit* line_edit_username1;
    QLineEdit* line_edit_password1;
    QLineEdit* line_edit_username2;
    QLineEdit* line_edit_password2;

    QLabel* label_login_username1;
    QLabel* label_login_password1;
    QLabel* label_login_username2;
    QLabel* label_login_password2;
    std::string sha256(const std::string& password);

    QLineEdit* line_login_edit_username1;
    QLineEdit*  line_login_edit_password1;
    QLineEdit* line_login_edit_username2;
    QLineEdit*  line_login_edit_password2;

    void setRegisterPage();
    void setLoginPage();
    void question_mode_page();
    void empty_history();
    void fun_yes_have();
    void fun_no_have();
    void insertRow(const QString& username, const QString& password,int wins , int loses);
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
