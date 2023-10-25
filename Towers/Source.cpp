///////////////////////////////////////////////////////////
///// Towers! game
///////////////////////////////////////////////////////////

// headers
#include "TowersGame.h"

// namespaces
using namespace std;

// main function of getting inputs and launching game
void playGame() {
    cout << "Welcome in game Towers!" << endl;
    string playerOneName;
    string playerTwoName;
    cout << "Type a name of Player 1 : ";
    cin >> playerOneName;
    cout << "Type a name of Player 2 : ";
    cin >> playerTwoName;
    playerOneName = playerOneName.substr(0, 15);
    playerTwoName = playerTwoName.substr(0, 15);
    cout << "Starting game..." << endl;
    // create game object
    TowersGame game(800, 800, 400);
    // set up setting like player names etc.
    game.setPlayerNames(playerOneName, playerTwoName);
    // launch game
    game.launchGame();
    cout << "Thanks for playing ";
}
int main()
{
    playGame();
}