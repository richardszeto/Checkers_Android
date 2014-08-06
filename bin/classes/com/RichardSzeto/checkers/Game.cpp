/** Class that governs the majority of the UI
  *
  * @author Richard Szeto
  *
  *
  *
  */

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include "Game.h"
#include "ActionQueue.h"
#include "Action.h"
#include "globals.h"

namespace CheckersSzeto
{
    Game::Game()
    {

    }

    Game::~Game()
    {

    }

    void Game::startGame()
    {
        showMainMenu();
    }

    void Game::gobbleAll()
    {
        using std::cin;

        char symbol;

        do
        {
            cin.get(symbol);
        }
        while(symbol != '\n');
    }

    void Game::setNextDigit(int &number, int digit)
    {
        number = (number * 10) + digit;
    }

    int Game::getNextNumber()
    {
        using std::cin;

        char nextSymbol;

        int result = 0;

        bool isNegative = false;

        do
        {
            cin.get(nextSymbol);
        }while(nextSymbol == ' ' ||
            nextSymbol == '\n' ||
            nextSymbol == '\t' ||
            nextSymbol == '\r');

        cin.putback(nextSymbol);

        while(true)
        {

            cin.get(nextSymbol);

            switch(nextSymbol)
            {
                case '-':

                    if(result == 0)
                    {
                        isNegative = true;
                    }
                    else
                    {
                        gobbleAll();

                        char symbol;

                        symbol = '\n';

                        cin.putback(symbol);

                        return -10;
                    }

                    break;

                case '0':

                    setNextDigit(result, 0);

                    break;

                case '1':

                    setNextDigit(result, 1);

                    break;

                case '2':

                    setNextDigit(result, 2);

                    break;

                case '3':

                    setNextDigit(result, 3);

                    break;

                case '4':

                    setNextDigit(result, 4);

                    break;

                case '5':

                    setNextDigit(result, 5);

                    break;

                case '6':

                    setNextDigit(result, 6);

                    break;

                case '7':

                    setNextDigit(result, 7);

                    break;

                case '8':

                    setNextDigit(result, 8);

                    break;

                case '9':

                    setNextDigit(result, 9);

                    break;

                default:

                    if(nextSymbol == ' ' ||
                        nextSymbol == '\n' ||
                        nextSymbol == '\t' ||
                        nextSymbol == '\r')
                    {
                        if(nextSymbol == '\n')
                        {
                            cin.putback(nextSymbol);
                        }

                        if(isNegative)
                        {
                            return -1 * result;
                        }
                        else
                        {
                            return result;
                        }
                    }
                    else
                    {
                        gobbleAll();

                        char newLine = '\n';

                        cin.putback(newLine);

                        return -10;
                    }

                    break;
            }
        }
    }

    string Game::makeLower(const string &s)
    {
        using std::string;

        string temp(s);

        for(unsigned int i = 0; i < s.length(); i++)
        {
            temp[i] = tolower(s[i]);
        }

        return temp;
    }

    void Game::showMainMenu()
    {
        using std::cout;
        using std::endl;
        using std::cin;

        int selection;

        bool invalidSelection;

        while(true)
        {
            selection = 0;

            invalidSelection = true;

            cout << "-------------------------------------------\n";

            cout << "|             1. Play Checkers            |\n";

            cout << "|             2. Change Settings          |\n";

            cout << "|             3. Exit Checkers            |\n";

            cout << "-------------------------------------------\n";

            cout << endl;

            while(invalidSelection)
            {
                cout << "Enter a number from 1 - 3: ";

                selection = getNextNumber();

                gobbleAll();

                invalidSelection = false;

                switch(selection)
                {
                    case 1:
                        invalidSelection = false;
                        playCheckers();
                        break;

                    case 2:
                        invalidSelection = false;
                        changeSettings();
                        break;

                    case 3:
                        invalidSelection = false;
                        exit(0);
                        break;

                    default:
                        invalidSelection = true;
                        cout << "Invalid selection\n";
                        selection = 0;
                        break;
                }
            }
        }
    }

    void Game::playCheckers()
    {
        using std::cout;
        using std::endl;
        using std::cin;

        int selection;

        bool invalidSelection;

        while(true)
        {
            selection = 0;

            invalidSelection = true;

            cout << "-------------------------------------------\n";

            cout << "|             1. 1 Player                 |\n";

            cout << "|             2. 2 Players                |\n";

            cout << "|             3. Main Menu                |\n";

            cout << "-------------------------------------------\n";

            cout << endl;

            while(invalidSelection)
            {
                cout << "Enter a number from 1 - 3: ";

                selection = getNextNumber();

                gobbleAll();

                invalidSelection = false;

                switch(selection)
                {
                    case 1:
                        invalidSelection = false;
                        onePlayerGame();
                        break;

                    case 2:
                        invalidSelection = false;
                        twoPlayerGame();
                        break;

                    case 3:
                        invalidSelection = false;
                        return;
                        break;

                    default:
                        invalidSelection = true;
                        cout << "Invalid selection\n";
                        selection = 0;
                        break;
                }
            }
        }
    }

    void Game::showBeginningGame()
    {
        using std::cout;
        using std::endl;

        checkerBoard.printBoard();
        checkerBoard.printTurn();

        cout << endl;

        cout << "To exit, type -1\n";
        cout << "To reset the game, type -2\n";
    }

    void Game::onePlayerGame()
    {
        using std::cout;
        using std::endl;
        using std::cin;
        using std::string;

        const int maxDepth = 100;

        const unsigned long milliseconds = 500; // 0.5 seconds

        gameTree.setTime(milliseconds);

        bool isPreGame = true;

        bool isFirstTurn = true;

        bool humanIsWhite = false;

        bool validMove = false;

        string color = "";

        int startX, startY, endX, endY;

        startX = 0;

        startY = 0;

        endX = 0;

        endY = 0;

        while(true)
        {
            if(isPreGame)
            {
                cout << "Do you want to play as white or black? (white/black): ";

                cin >> color;

                color = makeLower(color);

                if(color == "white" || color == "w")
                {
                    humanIsWhite = true;
                }
                else if(color == "black" || color == "b")
                {
                    humanIsWhite = false;
                }
                else
                {
                    cout << "Invalid Input\n";

                    continue;
                }

                showBeginningGame();

                isPreGame = false;
            }

            checkerBoard.scanCapture();

            checkerBoard.scanMove();

            if(checkerBoard.isEndGame())
            {
                string response = "";

                cout <<"Would you like to play again? (yes/no): ";

                cin >> response;

                response = makeLower(response);

                if(response == "yes" || response == "y")
                {
                    checkerBoard.clear();

                    showBeginningGame();

                    isPreGame = true;

                    isFirstTurn = true;

                    humanIsWhite = false;

                    continue;
                }
                else
                {
                    break;
                }
            }

            if(!(humanIsWhite && isFirstTurn))
            {
                ActionQueue oldActionQueue;

                ActionQueue newActionQueue;

                for(int i = 3; i <= maxDepth; i++)
                {
                    oldActionQueue.clear();

                    oldActionQueue = newActionQueue;

                    newActionQueue.clear();

                    newActionQueue = gameTree.alphaBetaSearch(checkerBoard, i);

                    if(newActionQueue.isEmpty())
                    {
                        break;
                    }
                }

                while(!oldActionQueue.isEmpty())
                {
                    Action action = oldActionQueue.removeFront();

                    checkerBoard.scanCapture();

                    checkerBoard.scanMove();

                    checkerBoard.move(action.getStartX(),
                        action.getStartY(),
                        action.getEndX(),
                        action.getEndY());

                    checkerBoard.printBoard();
                    checkerBoard.printTurn();

                    cout << endl;
                }
            }

            checkerBoard.scanCapture();

            checkerBoard.scanMove();

            if(checkerBoard.isEndGame())
            {
                string response = "";

                cout <<"Would you like to play again? (yes/no): ";

                cin >> response;

                response = makeLower(response);

                if(response == "yes" || response == "y")
                {
                    checkerBoard.clear();

                    showBeginningGame();

                    isPreGame = true;

                    isFirstTurn = true;

                    humanIsWhite = false;

                    continue;
                }
                else
                {
                    break;
                }
            }

            validMove = false;

            isFirstTurn = false;

            while(!validMove || checkerBoard.getIsMultiJump())
            {

                cout << "Enter startX startY endX endY: ";
                
                startX = getNextNumber();
                
                if(startX == -1)
                {
                    checkerBoard.clear();

                    return;
                }
                else if(startX == -2)
                {
                    checkerBoard.clear();

                    showBeginningGame();

                    isPreGame = true;

                    isFirstTurn = true;

                    humanIsWhite = false;

                    validMove = false;

                    break;
                }
                else if(startX == -10 ||
                    startX < 0 ||
                    startX >= GRID_LENGTH)
                {
                    cout << "Invalid Input\n";

                    gobbleAll();

                    continue;
                }
                
                startY = getNextNumber();
                
                if(startY == -1)
                {
                    checkerBoard.clear();

                    return;
                }
                else if(startY == -2)
                {
                    checkerBoard.clear();
                    
                    showBeginningGame();

                    isPreGame = true;

                    isFirstTurn = true;

                    humanIsWhite = false;

                    validMove = false;

                    break;
                }
                else if(startY == -10 ||
                    startY < 0 ||
                    startY >= GRID_LENGTH)
                {
                    cout << "Invalid Input\n";

                    gobbleAll();

                    continue;
                }
                
                endX = getNextNumber();
                
                if(endX == -1)
                {
                    checkerBoard.clear();

                    return;
                }
                else if(endX == -2)
                {
                    checkerBoard.clear();
                    
                    showBeginningGame();

                    isPreGame = true;

                    isFirstTurn = true;

                    humanIsWhite = false;

                    validMove = false;

                    break;
                }
                else if(endX == -10 ||
                    endX < 0 ||
                    endX >= GRID_LENGTH)
                {
                    cout << "Invalid Input\n";

                    gobbleAll();

                    continue;
                }
                
                endY = getNextNumber();
                
                if(endY == -1)
                {
                    checkerBoard.clear();

                    return;
                }
                else if(endY == -2)
                {
                    checkerBoard.clear();
                    
                    showBeginningGame();

                    isPreGame = true;

                    isFirstTurn = true;

                    humanIsWhite = false;

                    validMove = false;

                    break;
                }
                else if(endY == -10 ||
                    endY < 0 ||
                    endY >= GRID_LENGTH)
                {
                    cout << "Invalid Input\n";

                    gobbleAll();

                    continue;
                }

                gobbleAll();
                
                validMove = checkerBoard.move(startX, startY, endX, endY);

                if(!validMove)
                {
                    cout << "Invalid Move\n";

                    continue;
                }

                checkerBoard.printBoard();
                checkerBoard.printTurn();

                cout << endl;
            }
        }
    }

    void Game::twoPlayerGame()
    {
        using std::cout;
        using std::endl;
        using std::cin;

        showBeginningGame();

        int startX, startY, endX, endY;
        
        startX = 0;
        startY = 0;
        endX = 0;
        endY = 0;
        
        while(true)
        {
            checkerBoard.scanCapture();

            checkerBoard.scanMove();

            if(checkerBoard.isEndGame())
            {
                using std::string;

                string response = "";

                cout <<"Would you like to play again? (yes/no): ";

                cin >> response;

                response = makeLower(response);

                if(response == "yes" || response == "y")
                {
                    checkerBoard.clear();

                    showBeginningGame();

                    continue;
                }
                else
                {
                    break;
                }
            }

            cout << "Enter startX startY endX endY: ";
            
            startX = getNextNumber();
            
            if(startX == -1)
            {
                checkerBoard.clear();

                break;
            }
            else if(startX == -2)
            {
                checkerBoard.clear();

                showBeginningGame();

                continue;
            }
            else if(startX == -10 ||
                startX < 0 ||
                startX >= GRID_LENGTH)
            {
                cout << "Invalid Input\n";

                gobbleAll();

                continue;
            }
            
            startY = getNextNumber();
            
            if(startY == -1)
            {
                checkerBoard.clear();

                break;
            }
            else if(startY == -2)
            {
                checkerBoard.clear();
                
                showBeginningGame();

                continue;
            }
            else if(startY == -10 ||
                startY < 0 ||
                startY >= GRID_LENGTH)
            {
                cout << "Invalid Input\n";

                gobbleAll();

                continue;
            }
            
            endX = getNextNumber();
            
            if(endX == -1)
            {
                checkerBoard.clear();

                break;
            }
            else if(endX == -2)
            {
                checkerBoard.clear();
                
                showBeginningGame();

                continue;
            }
            else if(endX == -10 ||
                endX < 0 ||
                endX >= GRID_LENGTH)
            {
                cout << "Invalid Input\n";

                gobbleAll();

                continue;
            }
            
            endY = getNextNumber();
            
            if(endY == -1)
            {
                checkerBoard.clear();

                break;
            }
            else if(endY == -2)
            {
                checkerBoard.clear();
                
                showBeginningGame();

                continue;
            }
            else if(endY == -10 ||
                endY < 0 ||
                endY >= GRID_LENGTH)
            {
                cout << "Invalid Input\n";

                gobbleAll();

                continue;
            }

            gobbleAll();
            
            if(!checkerBoard.move(startX, startY, endX, endY))
            {
                cout << "Invalid Move\n";

                continue;
            }

            checkerBoard.printBoard();
            checkerBoard.printTurn();

            cout << endl;
        }
    }

    void Game::changeSettings()
    {
        // placeholder
    }
}