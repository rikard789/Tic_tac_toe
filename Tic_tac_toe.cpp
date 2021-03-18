#include <iostream>
#include <fstream>
#include <stdlib.h>


std::fstream scores("scores.txt");


struct Player
{
    std::string name;
};


class Board
{
private:
    char fillingSpaceCharacter = '-';
public:
    const char circle = 'o';
    const char cross = 'x';

    Board(char fillingSpaceCharacter_input)  { fillingSpaceCharacter = fillingSpaceCharacter_input;   }

    char gameboard[5][5];

    void fillBoard()
    {
        for(int i = 0; i <5; i++)
        {
            for(int j = 0; j <5; j++)
            {
                gameboard[i][j] = fillingSpaceCharacter;
            }
        }
    }

    void boardShow()
    {
        int tmp = 0;
        for(int i = 0; i <5; i++)
        {
            for(int j = 0; j <11; j++)
            {
                if(j%2 == 0)
                {
                    std::cout << '|';
                }
                else
                {
                    std::cout << gameboard[i][tmp];
                    tmp++;
                }
            }
            tmp = 0;
            std::cout << std::endl;
        }
    }

    int putCircleOrCross(char XorO, int x, int y)
    {
        if( (y > 0) && (y < 6) && (x > 0) && (x < 6) )
        {
            if( (gameboard[x-1][y-1] == 'x') || (gameboard[x-1][y-1] == 'o') )
                return 0;
            else
            {
                gameboard[x-1][y-1] = XorO;
                return 1;
            }
        }
        else
        {
            return 0;
        }
    }

    int CheckWin( char XorO)
        {
        for(int i = 0; i <5; i++)
        {
            if( ( (gameboard[i][0] == XorO) && (gameboard[i][1] == XorO) && (gameboard[i][2] == XorO) && (gameboard[i][3] == XorO) && (gameboard[i][4] == XorO) ) || (  (gameboard[0][i] == XorO) && (gameboard[1][i] == XorO) && (gameboard[2][i] == XorO) && (gameboard[3][i] == XorO) && (gameboard[4][i] == XorO)  ) )
            {
                return 1;
            }
        }
        if( ( (gameboard[0][0] == XorO) && (gameboard[1][1] == XorO) && (gameboard[2][2] == XorO) && (gameboard[3][3] == XorO) && (gameboard[4][4] == XorO) ) || (  (gameboard[4][0] == XorO) && (gameboard[3][1] == XorO) && (gameboard[2][2] == XorO) && (gameboard[1][3] == XorO) && (gameboard[0][4] == XorO)  ) )
        {
            return 1;
        }
        return 0;

        }
};

void MainMenu(Player player1, Player player2);

void game(Player player1, Player player2);

int main()
{
    Player player1;
    Player player2;
    MainMenu(player1, player2);

    return 0;
}


void game(Player player1, Player player2)
{
    char XorOturn;
    int check = 1, checkwin;
    std::string x, y;
    int Whoseturn = 0;

    system("cls");
    Board exemplaryBoard('-');
    exemplaryBoard.fillBoard();

    std::cout << "Gre wygrywa gracz ktory ulozy 5 te same znaki w poziomej, pionowej lub ukosnej linii." << std::endl;
    std::cout << "Zaczyna gracz o nick-u: " << player1.name << " grajacy krzyzykiem." << std::endl;

    while(1)
    {
        exemplaryBoard.boardShow();

        if( Whoseturn%2 == 0)
        {
            std::cout << "Teraz tura gracza o nick-u: " << player1.name << " grajacego krzyzykiem." << std::endl;
            XorOturn = exemplaryBoard.cross;
        }
        else
        {
            std::cout << "Teraz tura gracza o nick-u: " << player2.name << " grajacego kolkiem." << std::endl;
            XorOturn = exemplaryBoard.circle;
        }

        do
        {
            if(check == 0)
                std::cout << "Zle wpisales. Wpisz jeszcze raz." << std::endl;

            std::cout << "Jesli wpiszesz s wtedy wyjdziesz z gry, a gra nie zostanie zapisana." << std::endl;

            std::cout << "Podaj wiersz od 1 do 5, gdzie chcesz postawic znak: ";
            std::cin >> x ;
            if( x ==  "s")
                exit(0);
            std::cout << "Podaj kolumne od 1 do 5, gdzie chcesz postawic znak: ";
            std::cin >> y;
            if( y ==  "s")
                exit(0);

            int k = std::atoi( x.c_str() );
            int l =  std::atoi( y.c_str() );
            check = exemplaryBoard.putCircleOrCross(XorOturn, k, l);

        }while(check == 0);

        system("cls");
        checkwin = exemplaryBoard.CheckWin(XorOturn);

        if(checkwin == 1)
        {
            scores.seekg(0, std::ios_base::end);
            if(Whoseturn%2 == 0)
            {
                std::cout << "Gratulacje " << player1.name << " wygrales gre." << std::endl;
                scores << "Gratulacje " << player1.name << " wygrales gre." << '\n';
            }
            else
            {
                std::cout << "Gratulacje " << player2.name << " wygrales gre." << std::endl;
                scores << "Gratulacje " << player2.name << " wygrales gre." << '\n';
            }
            break;
        }
        Whoseturn++;
        if(Whoseturn == 24)
        {
            scores.seekg(0, std::ios_base::end);
            scores << " Remis. Pomiedzy " << player1.name << player2.name << '\n';
        }
    }

}


void MainMenu(Player player1, Player player2)
{
    int work = 0, nick1Saved = 0, nick2Saved = 0;

    std::string nick;
    std::string line;


    std::string ChooseOption;
    while(!work)
    {
        std::cout << "Wybierz opcje od 1 do 3. " << std::endl;
        std::cout << "1 - Rozpocznij gre w kolko i krzyzyk " << std::endl;
        std::cout << "2 - Historia gier" << std::endl;
        std::cout << "3 - Wyjscie z gry " << std::endl;
        std::cin >> ChooseOption;
        if(ChooseOption == "1")
        {
            system("cls");
            while(!nick1Saved)
            {
                std::cout << "Wpisz swoj nick jako gracz 1 - grajacy krzyzykiem: " << std::endl;
                std::cin >> nick;
                player1.name = nick;
                nick1Saved = 1;

            }
            //system("cls");
            while(!nick2Saved)
            {
                std::cout << "Wpisz swoj nick jako gracz 2 - grajacy kolkiem: " << std::endl;
                std::cin >> nick;
                player2.name = nick;
                nick2Saved = 1;
            }
            game(player1, player2);
        }
        else if(ChooseOption == "2")
        {
            std::cout << "Wyniki poprzednich gier" << std::endl;
            scores.clear();
            scores.seekg(0);
            while( getline(scores, line) )
            {
                std::cout << line << std::endl;
            }
            std::cout << std::endl;

        }
        else if(ChooseOption == "3")
            exit(0);
        else
            std::cout << "Nie ma takiej opcji. Wybierz ponownie" << std::endl;
    }
}


