#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QRandomGenerator>



using namespace std;
/* last game */
/* user history */
/* password hashing */
/* object types QGridLayout , QPushButton , QLabel , QLineEdit */
/* 1->x -1->o */
/*                ->setText(QString(' '));*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Create the grid layout and button
    change_history=0;

    gridLayout = new QGridLayout();
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            buttons[row][col] = new QPushButton();
            buttons[row][col]->setFixedSize(120, 120);
            connect(buttons[row][col], &QPushButton::clicked, [this, row, col]()
                    {
                        handleButtonClick(row, col);
                    });
            gridLayout->addWidget(buttons[row][col], row+7, col+2);
            History2[row][col]=0;
            History[row][col]=0;

        }
    }
    // Create the status label
    empty = new QLabel();
    statusLabel = new QLabel();
    statusLabel_profile_username = new QLabel();
    statusLabel_profile_wins = new QLabel();
    statusLabel_profile_loses = new QLabel();
    statusLabel_profile_username2 = new QLabel();
    statusLabel_profile_wins2 = new QLabel();
    statusLabel_profile_loses2 = new QLabel();
    welecome_word = new QLabel();
    welecome_question = new QLabel();
    having_account = new QLabel();

    // create buttons
    twoPlayerButton = new QPushButton("Player-vs-Player");
    easy = new QPushButton("Player-vs-AI easy mode");
    medium = new QPushButton("Player-vs-AI medium mode");
    hard = new QPushButton("Player-vs-AI impossible mode");
    last_game_history=new QPushButton("Last game history");
    path_one_player = new QPushButton("One Player");
    path_two_player = new QPushButton("Two players");
    back = new QPushButton("Back to first page to select mode");
    return_current_game = new QPushButton("Return to current game");
    yes_have = new QPushButton("Yes");
    no_have = new QPushButton("No");
    button_register = new QPushButton("Register");
    button_login    = new QPushButton("Login");

    QFont buttonFont;
    buttonFont.setPointSize(13);
    path_one_player->setFont(buttonFont);
    path_two_player->setFont(buttonFont);

    yes_have->setFont(buttonFont);
    no_have->setFont(buttonFont);

    button_register->setFont(buttonFont);
    button_login->setFont(buttonFont);

    // connect buttons
    connect(twoPlayerButton, &QPushButton::clicked, this, &MainWindow::startTwoPlayerGame);
    connect(easy, &QPushButton::clicked, this, &MainWindow::startSingleeasy);
    connect(medium, &QPushButton::clicked, this, &MainWindow::startSinglemedium);
    connect(hard, &QPushButton::clicked, this, &MainWindow::startSinglehard);
    connect(last_game_history, &QPushButton::clicked, this, &MainWindow::last_game_history_func);
    connect(path_one_player, &QPushButton::clicked, this, &MainWindow::fun_one_player);
    connect(path_two_player, &QPushButton::clicked, this, &MainWindow::fun_two_player);
    connect(back, &QPushButton::clicked, this, &MainWindow::fun_back);
    connect(return_current_game, &QPushButton::clicked, this, &MainWindow::fun_return);
    connect(yes_have,&QPushButton::clicked, this, &MainWindow::fun_yes_have);
    connect(no_have,&QPushButton::clicked, this, &MainWindow::fun_no_have);


    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(gridLayout);
    layout->addWidget(statusLabel);
    layout->addWidget(twoPlayerButton);
    layout->addWidget(easy);
    layout->addWidget(medium);
    layout->addWidget(hard);
    layout->addWidget(last_game_history);
    layout->addWidget(back);
    layout->addWidget(return_current_game);

    player1 = new QLabel(this);
    label_username1 = new QLabel(this);
    label_password1 = new QLabel(this);

    player2 = new QLabel(this);
    label_username2 = new QLabel(this);
    label_password2 = new QLabel(this);

    label_profile_username1 = new QLabel(this);
    label_profile_username2 = new QLabel(this);
    label_profile_wins1 = new QLabel(this);
    label_profile_wins2 = new QLabel(this);
    label_profile_loses1 = new QLabel(this);
    label_profile_loses2 = new QLabel(this);

    player1_playing_screen = new QLabel(this);
    player2_playing_screen = new QLabel(this);


    //create line edit
    line_edit_username1 = new QLineEdit(this);
    line_edit_password1 = new QLineEdit(this);

    line_edit_username2 = new QLineEdit(this);
    line_edit_password2 = new QLineEdit(this);

    line_login_edit_username1 = new QLineEdit(this);
    line_login_edit_password1 = new QLineEdit(this);
    line_login_edit_username2 = new QLineEdit(this);
    line_login_edit_password2 = new QLineEdit(this);

    label_login_username1 = new QLabel(this);
    label_login_password1 = new QLabel(this);

    label_login_username2 = new QLabel(this);
    label_login_password2 = new QLabel(this);

    //make password hashing in login page
    line_login_edit_password1->setEchoMode(QLineEdit::Password);
    line_login_edit_password2->setEchoMode(QLineEdit::Password);


    //naming all text
    empty->setText("");

    welecome_word->setText("Welcome in Tic Tac Toe");
    welecome_question->setText("Which mode do you want to play?");

    having_account->setText("Do you have Account?");

    player1->setText("Player 1");
    player2->setText("Player 2");
    label_username1->setText("Username");
    label_password1->setText("Password");

    label_username2->setText("Username");
    label_password2->setText("Password");


    label_login_username1->setText("Username");
    label_login_password1->setText("Password");
    label_login_username2->setText("Username");
    label_login_password2->setText("Password");

    player1_playing_screen->setText("Player 1");
    player2_playing_screen->setText("Player 2");
    label_profile_username1->setText("Username");
    label_profile_username2->setText("Username");
    label_profile_wins1->setText("Num of wins");
    label_profile_wins2->setText("Num of wins");
    label_profile_loses1->setText("Num of losses");
    label_profile_loses2->setText("Num of losses");


    // change the size of all text
    QFont font1;
    font1.setPointSize(12); // Set the desired font size
    QFont font2;
    font2.setPointSize(15); // Set the desired font size
    QFont font3;
    font3.setPointSize(20); // Set the desired font size
    QFont font4;
    font4.setPointSize(30); // Set the desired font size

    welecome_word->setFont(font4);
    welecome_question->setFont(font3);

    having_account->setFont(font4);

    player1->setFont(font3);
    player2->setFont(font3);

    label_username1->setFont(font2);
    label_password1->setFont(font2);
    label_username2->setFont(font2);
    label_password2->setFont(font2);

    label_login_username1->setFont(font2);
    label_login_password1->setFont(font2);
    label_login_username2->setFont(font2);
    label_login_password2->setFont(font2);

    player1_playing_screen->setFont(font3);
    player2_playing_screen->setFont(font3);

    label_profile_username1->setFont(font1);
    label_profile_username2->setFont(font1);
    label_profile_wins1->setFont(font1);
    label_profile_wins2->setFont(font1);
    label_profile_loses1->setFont(font1);
    label_profile_loses2->setFont(font1);
    statusLabel_profile_username->setFont(font2);
    statusLabel_profile_username2->setFont(font2);
    statusLabel_profile_wins->setFont(font2);
    statusLabel_profile_wins2->setFont(font2);
    statusLabel_profile_loses->setFont(font2);
    statusLabel_profile_loses2->setFont(font2);



    connect(button_register, &QPushButton::clicked, this, &MainWindow::registerClicked);
    connect(button_login, &QPushButton::clicked, this, &MainWindow::loginClicked);

    //first page
    gridLayout->addWidget(welecome_word,0,1);
    gridLayout->addWidget(welecome_question,1,1);
    gridLayout->addWidget(path_one_player,2,0);
    gridLayout->addWidget(path_two_player,2,2);

    //second page
    gridLayout->addWidget(having_account,0,1);
    gridLayout->addWidget(yes_have,1,0);
    gridLayout->addWidget(no_have,1,2);

    //third page
    gridLayout->addWidget(empty, 7, 1);
    gridLayout->addWidget(player1, 0, 1);
    gridLayout->addWidget(player2, 0, 4);
    gridLayout->addWidget(label_username1, 1, 0);
    gridLayout->addWidget(line_edit_username1, 1, 1);
    gridLayout->addWidget(label_password1, 2, 0);
    gridLayout->addWidget(line_edit_password1, 2, 1);
    gridLayout->addWidget(label_username2, 1, 3);
    gridLayout->addWidget(line_edit_username2, 1, 4);
    gridLayout->addWidget(label_password2, 2, 3);
    gridLayout->addWidget(line_edit_password2, 2, 4);
    layout->addWidget(button_register);

    //fourth page
    gridLayout->addWidget(label_login_username1, 1, 0);
    gridLayout->addWidget(line_login_edit_username1, 1, 1);
    gridLayout->addWidget(label_login_password1, 2, 0);
    gridLayout->addWidget(line_login_edit_password1, 2, 1);
    gridLayout->addWidget(label_login_username2, 1, 3);
    gridLayout->addWidget(line_login_edit_username2, 1, 4);
    gridLayout->addWidget(label_login_password2, 2, 3);
    gridLayout->addWidget(line_login_edit_password2, 2, 4);
    layout->addWidget(button_login);

    //fifth page
    gridLayout->addWidget(player1_playing_screen, 0, 1);
    gridLayout->addWidget(player2_playing_screen, 0, 5);
    gridLayout->addWidget(label_profile_username1, 1, 0);
    gridLayout->addWidget(statusLabel_profile_username, 1, 2);
    gridLayout->addWidget(label_profile_wins1, 2, 0);
    gridLayout->addWidget(statusLabel_profile_wins, 2, 2);
    gridLayout->addWidget(label_profile_loses1, 3, 0);
    gridLayout->addWidget(statusLabel_profile_loses, 3, 2);
    gridLayout->addWidget(label_profile_username2, 1, 4);
    gridLayout->addWidget(statusLabel_profile_username2, 1, 6);
    gridLayout->addWidget(label_profile_wins2, 2, 4);
    gridLayout->addWidget(statusLabel_profile_wins2, 2, 6);
    gridLayout->addWidget(label_profile_loses2, 3, 4);
    gridLayout->addWidget(statusLabel_profile_loses2, 3, 6);


    ui->centralwidget->setLayout(layout);

    question_mode_page();
}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::question_mode_page()
{
    having_account->hide();
    yes_have->hide();
    no_have->hide();
    line_login_edit_username1->hide();
    line_login_edit_password1->hide();
    line_login_edit_username2->hide();
    line_login_edit_password2->hide();
    label_login_username1->hide();
    label_login_password1->hide();
    label_login_username2->hide();
    label_login_password2->hide();
    button_login->hide();
    statusLabel_profile_loses->hide();
    statusLabel_profile_wins->hide();
    statusLabel_profile_username->hide();
    statusLabel_profile_loses2->hide();
    statusLabel_profile_wins2->hide();
    statusLabel_profile_username2->hide();
    label_profile_username1->hide();
    label_profile_wins1->hide();
    label_profile_loses1->hide();
    label_profile_username2->hide();
    label_profile_wins2->hide();
    label_profile_loses2->hide();
    player1_playing_screen->hide();
    player2_playing_screen->hide();
    statusLabel->hide();
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            buttons[row][col]->hide();
        }
    }
    medium->hide();
    easy->hide();
    hard->hide();
    twoPlayerButton->hide();
    last_game_history->hide();
    back->hide();
    return_current_game->hide();
    label_username1->hide();
    label_password1->hide();
    label_username2->hide();
    label_password2->hide();
    button_register->hide();
    line_edit_username1->hide();
    line_edit_password1->hide();
    line_edit_username2->hide();
    line_edit_password2->hide();
    player1->hide();
    player2->hide();

    welecome_question->show();
    welecome_question->show();
    path_one_player->show();
    path_two_player->show();

}



void MainWindow::fun_one_player()
{

    mode=0;
    welecome_word->hide();
    welecome_question->hide();
    path_one_player->hide();
    path_two_player->hide();
    having_account->show();
    yes_have->show();
    no_have->show();
}



void MainWindow::fun_two_player()
{

    mode=1;
    welecome_word->hide();
    welecome_question->hide();
    path_one_player->hide();
    path_two_player->hide();
    having_account->show();
    yes_have->show();
    no_have->show();
}



void MainWindow::fun_yes_have()
{

    having_account->hide();
    yes_have->hide();
    no_have->hide();
    setLoginPage();
    if(mode==1)
    {
        player2->show();
        player1->setText("Player 1");
    }
    if(mode==0)
        player1->setText("");

    player1->show();
}



void MainWindow::fun_no_have()
{

    having_account->hide();
    yes_have->hide();
    no_have->hide();
    setRegisterPage();
}



void MainWindow::setRegisterPage()
{
    welecome_word->hide();
    welecome_question->hide();
    path_one_player->hide();
    path_two_player->hide();
    if(mode==1)
    {
        label_username2->show();
        label_password2->show();
        line_edit_username2->show();
        line_edit_password2->show();
        player2->show();
        player1->setText("Player 1");
    }
    if(mode==0)
        player1->setText("");

    player1->show();
    label_username1->show();
    label_password1->show();
    line_edit_username1->show();
    line_edit_password1->show();
    button_register->show();
}



void MainWindow::registerClicked()
{

    QString username1 = line_edit_username1->text();
    QString password1 = line_edit_password1->text();
    QString username2 = line_edit_username2->text();
    QString password2 = line_edit_password2->text();
    insertRow(username1, password1,0,0);
    insertRow(username2, password2,0,0);
    setLoginPage();
}



void MainWindow::setLoginPage()
{
    label_username1->hide();
    label_password1->hide();
    label_username2->hide();
    label_password2->hide();
    button_register->hide();
    line_edit_username1->hide();
    line_edit_password1->hide();
    line_edit_username2->hide();
    line_edit_password2->hide();
    line_login_edit_username1->show();
    line_login_edit_password1->show();
    label_login_username1->show();
    label_login_password1->show();
    if(mode==1)
    {
        line_login_edit_username2->show();
        line_login_edit_password2->show();
        label_login_username2->show();
        label_login_password2->show();
    }
    button_login->show();
}



void MainWindow::loginClicked()
{
    int the_id=0;
    current_player_id1=-1;
    current_player_id2=-1;
    back_mode=0;

    login_username1 = line_login_edit_username1->text();
    login_password1 = line_login_edit_password1->text();
    login_username2 = line_login_edit_username2->text();
    login_password2 = line_login_edit_password2->text();
    QSqlQuery miqry;
    //QSqlQuery miqry2;
    miqry.exec("SELECT user_name, pass, wins, loses FROM lop");
    miqry.next();
    QString  my_username = miqry.value(0).toString();
    QString my_password = miqry.value(1).toString();

    // Hash enterd password1
    string hashedPassword = sha256(login_password1.toStdString());
    login_password1= QString::fromStdString(hashedPassword);
    // Hash enterd password2
    string  hashedPassword2 = sha256(login_password2.toStdString());
    login_password2= QString::fromStdString(hashedPassword2);

    for(int i=0 ; i<200; i++)
    {
        the_id++;
        if(login_username1==my_username && my_password==login_password1 )
            if(login_username1!="" && my_password!="" )
            {
                current_player_id1=the_id;
                break;
            }
        miqry.next();
        my_username = miqry.value(0).toString();
        my_password = miqry.value(1).toString();
    }
    the_id=0;
    miqry.exec("SELECT user_name, pass, wins, loses FROM lop");
    miqry.next();

    QString  my_username2 = miqry.value(0).toString();
    QString my_password2 = miqry.value(1).toString();

    for(int i=0 ; i<200; i++)
    {
        the_id++;
        qDebug()<<"id_val"<<the_id;

        if(login_username2==my_username2 && my_password2==login_password2 )
            if(login_username2!="" && my_password2!="" )
            {
                current_player_id2=the_id;
                break;
            }
        miqry.next();
        my_username2 = miqry.value(0).toString();
        my_password2 = miqry.value(1).toString();
    }
    qDebug()<<"my_id1"<<current_player_id1;
    qDebug()<<"my_id2"<<current_player_id2;


    line_login_edit_username1->hide();
    line_login_edit_password1->hide();
    label_login_username1->hide();
    label_login_password1->hide();
    line_login_edit_username2->hide();
    line_login_edit_password2->hide();
    label_login_username2->hide();
    label_login_password2->hide();
    button_login->hide();
    player1->hide();
    player2->hide();

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            buttons[row][col]->show();
        }
    }
    if(mode==1)
    {
        twoPlayerButton->show();
        player2_playing_screen->show();
        player1_playing_screen->show();
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                gridLayout->addWidget(buttons[row][col], row+7, col+2);
            }
        }
    }
    if(mode==0)
    {
        medium->show();
        easy->show();
        hard->show();

        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                gridLayout->addWidget(buttons[row][col], row+4, col);
            }
        }
    }
    back->show();
    statusLabel->show();
    last_game_history->show();
    Profile_func();
    initializeGame();
}



void MainWindow::insertRow(const QString& username, const QString& password,int wins , int loses)
{
    qDebug() << "Username:" << username;
    qDebug() << "Password:" << password;
    //perform hashing to password
    string hashedPassword = sha256(password.toStdString());
    QString::fromStdString(hashedPassword);

    QSqlQuery iqry;
    iqry.prepare("INSERT INTO lop (user_name,pass,wins,loses) VALUES (:user,:password,:wins,:loses)");
    iqry.bindValue(":user", username);
    iqry.bindValue(":password", QString::fromStdString(hashedPassword));
    iqry.bindValue(":wins", wins);
    iqry.bindValue(":loses", loses);


    if(!iqry.exec())
        qDebug()<<"problem in exc";
}


void MainWindow::startTwoPlayerGame()
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            buttons[i][j]->setStyleSheet("background-color: rgba(238, 238, 238);");
    initializeGame();
    if(change_history==0) change_history=1;
    else change_history=0;
    empty_history();
    level= 0;
    QFont font = statusLabel->font();
    font.setPointSize(20); // Set the desired font size
    statusLabel->setFont(font);
    statusLabel->setText("Player 1's turn");
}



void MainWindow::startSingleeasy()
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            buttons[i][j]->setStyleSheet("background-color: rgba(238, 238, 238);");
    initializeGame();
    level = 1;
    if(change_history==0) change_history=1;
    else change_history=0;
    empty_history();
    QFont font = statusLabel->font();
    font.setPointSize(20); // Set the desired font size
    statusLabel->setFont(font);
    statusLabel->setText("Player 1's turn");
}



void MainWindow::startSinglemedium()
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            buttons[i][j]->setStyleSheet("background-color: rgba(238, 238, 238);");
    initializeGame();
    level= 2;
    if(change_history==0) change_history=1;
    else change_history=0;
    empty_history();
    QFont font = statusLabel->font();
    font.setPointSize(20); // Set the desired font size
    statusLabel->setFont(font);
    statusLabel->setText("Player 1's turn");
}



void MainWindow::startSinglehard()
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            buttons[i][j]->setStyleSheet("background-color: rgba(238, 238, 238);");
    initializeGame();
    level = 3;
    if(change_history==0) change_history=1;
    else change_history=0;
    empty_history();
    QFont font = statusLabel->font();
    font.setPointSize(20); // Set the desired font size
    statusLabel->setFont(font);
    statusLabel->setText("Player 1's turn");
}



void MainWindow::last_game_history_func()
{
    back_mode =true;
    medium->hide();
    easy->hide();
    hard->hide();
    twoPlayerButton->hide();
    last_game_history->hide();
    back->hide();

    return_current_game->show();

    if(change_history==1)
    {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col)
            {
                if(History[row][col] ==1)
                {
                    buttons[row][col]->setText(QString('X'));
                    board[row][col] =1;
                }
                else if (History[row][col] ==-1)
                {
                    buttons[row][col]->setText(QString('O'));
                    board[row][col]=-1;
                }
                else
                {
                    buttons[row][col]->setText(QString(' '));
                    board[row][col]=0;
                }
                buttons[row][col]->setStyleSheet("background-color: rgba(238, 238, 238);");

            }
        }
    }
    if(change_history==0)
    {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col)
            {
                if(History2[row][col] ==1)
                {
                    buttons[row][col]->setText(QString('X'));
                    board[row][col] =1;
                }
                else if (History2[row][col] ==-1)
                {
                    buttons[row][col]->setText(QString('O'));
                    board[row][col]=-1;
                }
                else
                {
                    buttons[row][col]->setText(QString(' '));
                    board[row][col]=0;
                }
                buttons[row][col]->setStyleSheet("background-color: rgba(238, 238, 238);");
            }
        }
    }
    if (checkWin('X')) {
        QFont font = statusLabel->font();
        font.setPointSize(20); // Set the desired font size
        statusLabel->setFont(font);
        statusLabel->setText("Player 1 won in the previous game");
    }
    else if (checkWin('O')) {
        QFont font = statusLabel->font();
        font.setPointSize(20); // Set the desired font size
        statusLabel->setFont(font);
        if(mode==1)
            statusLabel->setText("Player 2 won in the previous game");
        else statusLabel->setText("AI won in the previous game");
    }
    else
    {
        QFont font = statusLabel->font();
        font.setPointSize(20); // Set the desired font size
        statusLabel->setFont(font);
        statusLabel->setText("No one won in the previous game");
    }
}



void MainWindow::Profile_func()
{
    statusLabel_profile_loses->show();
    statusLabel_profile_wins->show();
    statusLabel_profile_username->show();
    label_profile_username1->show();
    label_profile_wins1->show();
    label_profile_loses1->show();
    if(mode==1)
    {
        statusLabel_profile_loses2->show();
        statusLabel_profile_wins2->show();
        statusLabel_profile_username2->show();
        label_profile_username2->show();
        label_profile_wins2->show();
        label_profile_loses2->show();
    }

    if(current_player_id1==-1)
    {
        statusLabel_profile_username->setText("unknown");
        statusLabel_profile_wins->setText("unknown");
        statusLabel_profile_loses->setText("unknown");
    }
    else
    {
        QSqlQuery miqry;
        miqry.exec("SELECT user_name, pass, wins, loses FROM lop");
        for(int i=0;i<current_player_id1;i++)
            miqry.next();

        QString  my_username = miqry.value(0).toString();
        int my_wins = miqry.value(2).toInt();
        int my_losses=miqry.value(3).toInt();
        statusLabel_profile_username->setText(my_username);
        statusLabel_profile_wins->setNum(my_wins);
        statusLabel_profile_loses->setNum(my_losses);
    }

    if(current_player_id2==-1)
    {
        statusLabel_profile_username2->setText("unknown");
        statusLabel_profile_wins2->setText("unknown");
        statusLabel_profile_loses2->setText("unknown");

    }
    else
    {
        QSqlQuery miqry2;
        miqry2.exec("SELECT user_name, pass, wins, loses FROM lop");
        for(int i=0;i<current_player_id2;i++)
            miqry2.next();

        QString  my_username2 = miqry2.value(0).toString();
        int my_wins2 = miqry2.value(2).toInt();
        int my_losses2=miqry2.value(3).toInt();
        statusLabel_profile_username2->setText(my_username2);
        statusLabel_profile_wins2->setNum(my_wins2);
        statusLabel_profile_loses2->setNum(my_losses2);
    }
}



void MainWindow::add_win(int id)
{
    int current_id=0;
    QSqlQuery miqry;

    miqry.exec("SELECT user_name, pass, wins, loses FROM lop");
    for(int i=0;i<id;i++)
    {
        current_id++;
        miqry.next();
    }
    QString  my_username = miqry.value(0).toString();
    int my_wins = miqry.value(2).toInt();

    int newwins=my_wins+1;
    QSqlQuery iqry;
    iqry.prepare("UPDATE lop SET wins = :newwins WHERE user_name =:the_name");
    iqry.bindValue(":newwins", newwins);
    iqry.bindValue(":the_name", my_username);

    if(!iqry.exec())
    {
        qDebug()<<"problem in excdwd";
    }
}



void MainWindow::add_lose(int id)
{
    int current_id=0;
    QSqlQuery miqry;

    miqry.exec("SELECT user_name, pass, wins, loses FROM lop");
    for(int i=0;i<id;i++)
    {
        current_id++;
        miqry.next();

    }
    QString  my_username = miqry.value(0).toString();
    int my_loses = miqry.value(3).toInt();

    int newloses=my_loses+1;
    QSqlQuery iqry;
    iqry.prepare("UPDATE lop SET loses = :newloses WHERE user_name =:the_name");
    iqry.bindValue(":newloses", newloses);
    iqry.bindValue(":the_name", my_username);

    qDebug()<<"lossnew"<<newloses;

    if(!iqry.exec())
    {
        qDebug()<<"problem in exc";
    }
}



void MainWindow::empty_history()
{
    if(change_history==0)
    {
        for(int row=0;row<3;++row)
            for(int col=0;col<3;++col)
                History[row][col]=0;
    }
    if(change_history==1)
    {
        for(int row=0;row<3;++row)
            for(int col=0;col<3;++col)
                History2[row][col]=0;
    }
}



void MainWindow::initializeGame()
{
    isPlayerTurn = true;
    if(mode==0)
        level = 1;
    else
        level=0;

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            buttons[row][col]->setText("");
            board[row][col] = 0;
        }
    }
    QFont font = statusLabel->font();
    font.setPointSize(20); // Set the desired font size
    statusLabel->setFont(font);
    statusLabel->setText("Player 1's turn");
}



void MainWindow::handleButtonClick(int row, int col)
{

    if (board[row][col] != 0) return;
    if (checkWin('X')) return;
    if (checkWin('O')) return;
    if(back_mode) return;
    updateBoard(row, col, isPlayerTurn ? 'X' : 'O');
    auto start = std::chrono::high_resolution_clock::now();
    if (checkWin('X')) {
        QFont font = statusLabel->font();
        font.setPointSize(20); // Set the desired font size
        statusLabel->setFont(font);
        statusLabel->setText("Player 1 wins!");
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        qDebug()<< "Execution time: " << elapsed.count() << " seconds\n";

        if(current_player_id1!=-1)
        {
            add_win(current_player_id1);
            Profile_func();
        }
        if(current_player_id2!=-1)
        {
            add_lose(current_player_id2);
            Profile_func();
        }
        return;
    }
    if (checkWin('O')) {
        QFont font = statusLabel->font();
        font.setPointSize(20); // Set the desired font size
        statusLabel->setFont(font);
        statusLabel->setText("Player 2 wins!");

        if(current_player_id2!=-1)
        {
            add_win(current_player_id2);
            Profile_func();
        }
        if(current_player_id1!=-1)
        {
            add_lose(current_player_id1);
            Profile_func();
        }
        return;
    }
    if (checkTie())
    {
        {
            QFont font = statusLabel->font();
            font.setPointSize(20); // Set the desired font size
            statusLabel->setFont(font);
            statusLabel->setText("It's a tie!");
            return;
        }
    }

    isPlayerTurn = !isPlayerTurn;
    if (level!=0 && !isPlayerTurn) computerMove();
    else {
        QFont font = statusLabel->font();
        font.setPointSize(20); // Set the desired font size
        statusLabel->setFont(font);
        statusLabel->setText(isPlayerTurn ? "Player 1's turn" : "Player 2's turn");
    }
}



void MainWindow::updateBoard(int row, int col, char symbol)
{
    QFont buttonFont;
    buttonFont.setPointSize(18);
    buttons[row][col]->setFont(buttonFont);

    buttons[row][col]->setText(QString(symbol));


    board[row][col] = (symbol == 'X') ? 1 : -1;
    if(change_history==0)
        History[row][col]= (symbol == 'X') ? 1 : -1;

    else   History2[row][col]= (symbol == 'X') ? 1 : -1;
}



bool MainWindow::checkWin(char symbol)
{
    int target = (symbol == 'X') ? 3 : -3;
    // Check rows
    for (int row = 0; row < 3; ++row) {
        if (board[row][0] + board[row][1] + board[row][2] == target)
        {

            for (int i = 0; i < 3; ++i)
                buttons[row][i]->setStyleSheet("background-color: gray");
            return true;
        };
    }

    // Check columns
    for (int col = 0; col < 3; ++col) {
        if (board[0][col] + board[1][col] + board[2][col] == target)
        {

            for (int i = 0; i < 3; ++i)
                buttons[i][col]->setStyleSheet("background-color: gray");
            return true;
        };
    }
    // Check diagonals
    if (board[0][0] + board[1][1] + board[2][2] == target )
    {
        for (int i = 0; i < 3; ++i)
            buttons[i][i]->setStyleSheet("background-color: gray");
        return true;
    }
    if (board[2][0] + board[1][1] + board[0][2] == target )
    {
        for (int i = 0; i < 3; ++i)
            buttons[2-i][i]->setStyleSheet("background-color: gray");
        return true;
    }
    return false;
}



bool MainWindow::checkTie()
{
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board[row][col] == 0) return false;
        }
    }
    return true;
}



void MainWindow::computerMove()
{
    // Implement your computer AI logic here
    int row=-1, col=-1;
    if(level==1)
        goto dahin;


    for(int r=0;r<3; ++r)
    {
        if(board[r][0]!=0&&(board[r][0]==board[r][1])&&(board[r][2]==0))
        {
            row=r, col=2;
            if(board[r][0]==-1) goto da;

        }
        if(board[r][0]!=0&&(board[r][0]==board[r][2])&&(board[r][1]==0))
        {
            row=r, col=1;
            if(board[r][0]==-1) goto da;

        }
        if(board[r][1]!=0&&(board[r][1]==board[r][2])&&(board[r][0]==0))
        {
            row=r, col=0;
            if(board[r][1]==-1) goto da;
        }

    }

    for(int c=0;c<3; ++c)
    {
        if(board[0][c]!=0&&(board[0][c]==board[1][c])&&(board[2][c]==0))
        {
            row=2, col=c;
            if(board[0][c]==-1) goto da;

        }
        if(board[0][c]!=0&&(board[0][c]==board[2][c])&&(board[1][c]==0))
        {
            row=1, col=c;
            if(board[0][c]==-1) goto da;

        }
        if((board[1][c]!=0&&board[1][c]==board[2][c])&&(board[0][c]==0))
        {
            row=0, col=c;
            if(board[1][c]==-1) goto da;

        }
    }
    if(board[0][0]!=0&&(board[0][0]==board[1][1])&&board[2][2]==0)
    {
        row=col=2;
        if(board[0][0]==-1) goto da;

    }
    if(board[0][0]!=0&&(board[0][0]==board[2][2])&&board[1][1]==0)
    {
        row=col=1;
        if(board[0][0]==-1) goto da;

    }
    if(board[1][1]!=0&&(board[1][1]==board[2][2])&&board[0][0]==0)
    {
        row=col=0;
        if(board[1][1]==-1) goto da;
    }

    if(board[0][2]!=0&&(board[0][2]==board[1][1])&&board[2][0]==0)
    {
        row=2; col=0;
        if(board[0][2]==-1) goto da;
    }
    if(board[1][1]!=0&&(board[2][0]==board[1][1])&&board[0][2]==0)
    {
        row=0; col=2;
        if(board[1][1]==-1) goto da;
    }
    if(board[0][2]!=0&&(board[0][2]==board[2][0])&&board[1][1]==0)
    {
        row=1; col=1;
        if(board[0][2]==-1) goto da;
    }

    if(col==-1)
    {
        if (level==3)
        {


            if(board[0][1]==1&&board[1][2]==1&&board[2][1]==-1&&board[0][0]==0)
            {
                row=0;col=0;
                goto da;
            }
            if(board[0][1]==1&&board[1][0]==1&&board[2][1]==-1&&board[0][2]==0)
            {
                row=0;col=2;
                goto da;
            }
            if(board[1][2]==1&&board[0][1]==1&&board[1][0]==-1&&board[2][2]==0)
            {
                row=2;col=2;
                goto da;
            }
            if(board[1][2]==1&&board[2][1]==1&&board[1][0]==-1&&board[0][2]==0)
            {
                row=0;col=2;
                goto da;
            }
            if(board[2][1]==1&&board[1][2]==1&&board[0][1]==-1&&board[2][0]==0)
            {
                row=2;col=0;
                goto da;
            }
            if(board[2][1]==1&&board[1][0]==1&&board[0][1]==-1&&board[2][2]==0)
            {
                row=2;col=2;
                goto da;
            }
            if(board[1][0]==1&&board[0][1]==1&&board[1][2]==-1&&board[2][0]==0)
            {
                row=2;col=0;
                goto da;
            }
            if(board[1][0]==1&&board[2][1]==1&&board[1][2]==-1&&board[0][0]==0)
            {
                row=0;col=0;
                goto da;
            }


            if(board[1][0]==1&&board[2][1]==1&&board[2][0]==0)
            {
                row=2;col=0;
                goto da;
            }
            if(board[0][1]==1&&board[1][2]==1&&board[0][2]==0)
            {
                row=0;col=2;
                goto da;
            }
            if(board[1][0]==1&&board[0][1]==1&&board[0][0]==0)
            {
                row=0;col=0;
                goto da;
            }
            if(board[1][2]==1&&board[2][1]==1&&board[2][2]==0)
            {
                row=2;col=2;
                goto da;
            }



            if(board[0][1]==1&&board[2][2]==1&&board[0][2]==0)
            {
                row=0;col=2;
                goto da;
            }
            if(board[0][1]==1&&board[2][0]==1&&board[0][0]==0)
            {
                row=0;col=0;
                goto da;
            }
            if(board[1][0]==1&&board[0][2]==1&&board[0][0]==0)
            {
                row=0;col=0;
                goto da;
            }
            if(board[1][0]==1&&board[2][2]==1&&board[2][0]==0)
            {
                row=2;col=0;
                goto da;
            }
            if(board[2][1]==1&&board[0][2]==1&&board[2][2]==0)
            {
                row=2;col=2;
                goto da;
            }
            if(board[2][1]==1&&board[0][0]==1&&board[2][0]==0)
            {
                row=2;col=0;
                goto da;
            }
            if(board[1][2]==1&&board[0][0]==1&&board[0][2]==0)
            {
                row=0;col=2;
                goto da;
            }
            if(board[1][2]==1&&board[2][0]==1&&board[2][2]==0)
            {
                row=2;col=2;
                goto da;
            }


            if(board[0][1]==1&&board[2][1]==0)
            {
                row=2;col=1;
                goto da;
            }
            if(board[1][2]==1&&board[1][0]==0)
            {
                row=1;col=0;
                goto da;
            }
            if(board[2][1]==1&&board[0][1]==0)
            {
                row=0;col=1;
                goto da;
            }
            if(board[1][0]==1&&board[1][2]==0)
            {
                row=1;col=2;
                goto da;
            }

            if(board[1][1]==0)
            {
                row=1;col=1;
                goto da;
            }
            if(board[1][1]==1&&board[0][2]==0)
            {
                row=0;col=2;
                goto da;
            }
            if(board[1][1]==1&&board[0][2]!=0&&board[0][0]==0)
            {
                row=0;col=0;
                goto da;
            }
            if(board[0][1]==0)
            {
                row=0;col=1;
                goto da;
            }
        }
    dahin: do {
            row = QRandomGenerator::global()->bounded(3);
            col = QRandomGenerator::global()->bounded(3);
        } while (board[row][col] != 0);
    }

da: updateBoard(row, col, 'O');
    if (checkWin('O')) {

        QFont font = statusLabel->font();
        font.setPointSize(20); // Set the desired font size
        statusLabel->setFont(font);
        statusLabel->setText("AI wins!");

        if(current_player_id1!=-1)
        {
            add_lose(current_player_id1);
            Profile_func();
        }
    } else if (checkTie()) {
        QFont font = statusLabel->font();
        font.setPointSize(20); // Set the desired font size
        statusLabel->setFont(font);
        statusLabel->setText("It's a tie!");
    } else {
        QFont font = statusLabel->font();
        font.setPointSize(20); // Set the desired font size
        statusLabel->setFont(font);
        statusLabel->setText("Player 1's turn");
    }
    isPlayerTurn = true;
}



void MainWindow::fun_back()
{

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            buttons[i][j]->setStyleSheet("background-color: rgba(238, 238, 238);");
            History[i][j]=0;  History2[i][j]=0;
        }
    question_mode_page();
}




void MainWindow::fun_return()
{


    back_mode =false;
    return_current_game->hide();
    if(mode==0)
    {
        medium->show();
        easy->show();
        hard->show();
    }
    else twoPlayerButton->show();
    last_game_history->show();
    back->show();


    if(change_history==0)
    {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col)
            {
                if(History[row][col] ==1)
                {
                    buttons[row][col]->setText(QString('X'));
                    board[row][col] =1;
                }
                else if (History[row][col] ==-1)
                {
                    buttons[row][col]->setText(QString('O'));
                    board[row][col]=-1;
                }
                else
                {
                    buttons[row][col]->setText(QString(' '));
                    board[row][col]=0;
                }
                buttons[row][col]->setStyleSheet("background-color: rgba(238, 238, 238);");

            }
        }
    }
    if(change_history==1)
    {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col)
            {
                if(History2[row][col] ==1)
                {
                    buttons[row][col]->setText(QString('X'));
                    board[row][col] =1;
                }
                else if (History2[row][col] ==-1)
                {
                    buttons[row][col]->setText(QString('O'));
                    board[row][col]=-1;
                }
                else
                {
                    buttons[row][col]->setText(QString(' '));
                    board[row][col]=0;
                }
                buttons[row][col]->setStyleSheet("background-color: rgba(238, 238, 238);");
            }
        }
    }
    if (checkWin('X')) {
        QFont font = statusLabel->font();
        font.setPointSize(20); // Set the desired font size
        statusLabel->setFont(font);
        statusLabel->setText("Player 1 win!");

    }
    else if (checkWin('O')) {
        QFont font = statusLabel->font();
        font.setPointSize(20); // Set the desired font size
        statusLabel->setFont(font);
        if(mode==1)
            statusLabel->setText("Player 2 win!");
        else statusLabel->setText("AI win!");
    }
    else if(checkTie())
    {
        QFont font = statusLabel->font();
        font.setPointSize(20); // Set the desired font size
        statusLabel->setFont(font);
        statusLabel->setText("It's tie!");
    }
    else if(isPlayerTurn)
    {
        QFont font = statusLabel->font();
        font.setPointSize(20); // Set the desired font size
        statusLabel->setFont(font);
        statusLabel->setText("Player 1's turn");
    }
    else
    {
        QFont font = statusLabel->font();
        font.setPointSize(20); // Set the desired font size
        statusLabel->setFont(font);
        statusLabel->setText("Player 2's turn");
    }
}


std::string MainWindow::sha256(const std::string& password) {
    std::string hashedPassword;
    std::array<unsigned char, 32> hash{};

    // Perform SHA-256 hashing
    std::hash<std::string> hasher;
    std::transform(password.begin(), password.end(), hash.begin(),
                   [&](char c) { return hasher(std::string(1, c)); });

    // Convert hash to hexadecimal string (truncated to 32 characters)
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (const auto& byte : hash) {
        oss << std::setw(2) << static_cast<unsigned>(byte);
    }
    hashedPassword = oss.str().substr(0, 64); // Truncate to 32 characters

    return hashedPassword;
}

////////////////////////End Code///////////////
