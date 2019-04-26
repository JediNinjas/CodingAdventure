//  Copyright © 2017 James Prochaska. All rights reserved.

#include <iostream>
#include <string>

using namespace std;

class Player
{
private:
  
    int      // all my variables
    rope,
    waterScroll,
    toughShoes,
    grappleHook,
    magicDoor,
    lava,
    rewardSecret,
    islandMonster,
    spikes,
    amount,
    secretStone1,
    secretStone2,
    secretStone3,
    sa, // stone answer
    choiceDirection;
    
    string map[20][20];
    string mapCopy[20][20];
    string filledMap[20][20];
    string filledMapCopy[20][20];
    string info;
    
    bool          // true and false statements
    hasStone1,
    hasStone2,
    hasStone3,
    hasTrident,
    foundMap,
    backToMap,
    foundMonster,
    hasHook,
    foundEntrance,
    hasMap,
    hasShoes,
    hasSword,
    levelComplete,
    foundLava,
    foundSpikes,
    foundPit,
    isAlive,
    hasCipher;
    
    int
    xPos,
    yPos,
    correctStones;
    
public:
    
    bool checkBounds(int, int),
    isComplete(),
    getAlive();
    
    int placeStone(int, int);
    
    void         // these are all the functions that have different if statements and loops that make the code run. From moving to picking up items to trigger events, its all here.
    cipher(),
    getStone1(),
    stone1(),
    getStone2(),
    stone2(),
    getStone3(),
    stone1Location(),
    stone2Location(),
    stone3Location(),
    goLeft(),
    goUp(),
    goDown(),
    goRight(),
    getInput(),
    introStory(),
    directions(),
    playerPosition(),
    mapReset(),
    printMap(),
    foundSecretStone1(),
    foundSecretStone2(),
    foundSecretStone3(),
    hitMountain(),
    hitObject(int, int);
    
    char
    getChoice();
    Player();
    
    void resetGame();
};

void Player::resetGame()       // this is player checking level stats and whether to reset the game. Also it feels in the map with the appropriate locations and legend
{
    hasStone1 = false;
    hasStone2 = false;
    hasStone3 = false;
    hasTrident = false;
    foundMap = false;
    backToMap = true;
    foundMonster = false;
    hasHook = false;
    foundEntrance = false;
    hasMap = false;
    hasShoes = false;
    hasSword = false;
    levelComplete = false;
    foundLava = false;
    foundSpikes = false;
    foundPit = false;
    isAlive = true;
    hasCipher = false;
    
    correctStones = 0;
    
    info = "";
    for(int i = 1; i < 20; i++)
    {
        for(int j = 1; j < 20; j++)
        {
            map[i][j] = '.';
            mapCopy[i][j] = '.';
            filledMap[i][j] = ".";
        }
    }
    filledMap[1][1] = "†";
    filledMap[2][1] = "Ø";
    filledMap[6][1] = "∆";
    filledMap[13][1] = "∆";
    filledMap[14][1] = "∆";
    filledMap[18][1] = "Ø";
    filledMap[19][1] = "†";
    
    filledMap[1][2] = "∆";
    filledMap[2][2] = "∆";
    filledMap[6][2] = "∆";
    filledMap[18][2] = "∆";
    filledMap[19][2] = "∆";
    
    filledMap[9][3] = "∫";
    
    filledMap[5][4] = "∆";
    
    filledMap[5][5] = "∆";
    
    filledMap[2][6] = "O";
    filledMap[5][6] = "∆";
    filledMap[17][6] = "¥";
    filledMap[15][6] = "∆";
    
    filledMap[9][9] = "∆";
    filledMap[10][9] = "∆";
    filledMap[11][9] = "∆";
    
    filledMap[2][10] = "∆";
    filledMap[3][10] = "∆";
    filledMap[5][10] = "O";
    filledMap[9][10] = "∆";
    filledMap[11][10] = "Ø";
    filledMap[12][10] = "Ω";
    
    filledMap[2][11] = "∆";
    filledMap[9][11] = "∆";
    filledMap[10][11] = "∆";
    filledMap[11][11] = "∆";

    filledMap[8][19] = "~"; 
    filledMap[2][12] = "∆";
    filledMap[16][12] = "∆";
    filledMap[17][12] = "∆";
    
    filledMap[2][14] = "O";
    filledMap[9][14] = "∆";
    filledMap[10][14] = "∆";
    
    filledMap[9][15] = "∆";
    filledMap[15][15] = "∆";
    filledMap[16][15] = "∆";
    filledMap[17][15] = "∆";
    
    filledMap[5][16] = "√";
    filledMap[14][16] = "Ø";
    filledMap[15][16] = "∑";
    filledMap[16][16] = "∆";
    
    filledMap[2][17] = "∆";
    filledMap[3][17] = "∆";
    filledMap[15][17] = "∆";
    
    filledMap[9][18] = "∆";
    filledMap[10][18] = "Ø";
    filledMap[11][18] = "∆";
    
    filledMap[1][19] = "≈";
    filledMap[4][19] = "∆";
    filledMap[5][19] = "∆";
    filledMap[9][19] = "∆";
    filledMap[10][19] = "†";
    filledMap[11][19] = "∆";
    
    for(int i = 1; i < 20; i++)
    {
        for(int j = 1; j < 20; j++)
        {
            filledMapCopy[i][j] = filledMap[i][j];
        }
    }
    
    map[10][10] = mapCopy[10][10] = 'x';
    filledMap[10][10] = filledMapCopy[10][10] = "x";
    xPos = 19;
    yPos = 19;
    map[yPos][xPos] = '@';
    filledMap[yPos][xPos] = "@";
}

int Player::placeStone(int x, int y) //////////////////////// this is the stone location decisions. shares the story of the stones and checks to see if the player has the appropriate items needed to open secret door for reward.
{
    if(x == 10)
    {
        if (hasCipher == false) {
            cout << "You found a stone location! It has an engraving on the rock. It reads\n\n ˙ø∑ µå˜¥ ç®´∑ µå†´ß ∂ˆ∂ ¥ø¨ ˙å√´÷\n";
        } else {
            cout << "You found a stone location! It has an engraving on the rock. It reads\n\n How many crew mates did you have?\n";
        }
    }
    else if(x == 6)
    {
        if (hasCipher == false) {
            cout << "You found a stone location! It has an engraving on the rock. It reads\n\n ˙ø∑ µå˜¥ µø¨˜†åˆ˜ß å®´ †˙´®´ ø˜ †˙ˆß ˆß¬å˜∂÷\n";
        } else {
            cout << "You found a stone location! It has an engraving on the rock. It reads\n\n How many mountains are on this island?\n";
        }
    }
    else if(x == 14)
    {
        if(hasCipher == false){
            cout << "You found a stone location! It has an engraving on the rock. It reads\n\n ∑˙å† ˆß †˙´ å©´ øƒ ∆åç˚÷\n";
        }else{
            cout << "You found a stone location! It has an engraving on the rock. It reads\n\n What is the age of Jack?\n";
        }
    }
    cout << "Hey, you have a stone! Wanna place it in the stone location?\n";
    if(hasStone1)
    {
        if(hasCipher == false)
        cout  << "A = ƒø¨® Ω´®ø\n";
        else cout << "A = 40\n";
    }
    if(hasStone2)
    {
        if(hasCipher == false)
        cout << "B = ƒø¨® ø˜´\n";
        else cout << "B = 41\n";
    }
    if(hasStone3)
    {
        if(hasCipher == false)
        cout << "C = ƒø¨® †∑ø\n";
        else cout << "C = 42\n";
    }
    cout << "D = Don't put a stone down!\n";
    string c;
    while(true)
    {
        cout << "\nEnter Choice here: ";
        cin >> c;
        switch(c.at(0))
        {
            case 'A':
            case 'a': if(x == 10 && y == 5) {hasStone1 = false; return 0;} else return 1;
            case 'B':
            case 'b': if(x == 6 && y == 2) {hasStone2 = false; return 0;} else return 1;
            case 'C':
            case 'c': if(x == 14 && y == 2) {hasStone3 = false; return 0;} else return 1;
            case 'D':
            case 'd': return 2;
            default: cout << "Needs to be 'A', 'B', 'C', or 'D'.\n";
                break;
        }
    }
}

bool Player::checkBounds(int x, int y)    // so the player can not go off the map
{
    return (x >= 1 && x < 20 && y >= 1 && y < 20 && filledMap[y][x] == ".");
}

bool Player::getAlive()    // is the player alive in certain situations
{
    return isAlive;
}

bool Player::isComplete()    // has all goals been completed on the map?
{
    return levelComplete;
}

Player::Player()    // filling in the map when player colides with objects
{
    hasStone1 = false;
    hasStone2 = false;
    hasStone3 = false;
    hasTrident = false;
    foundMap = false;
    backToMap = true;
    foundMonster = false;
    hasHook = false;
    foundEntrance = false;
    hasMap = false;
    hasShoes = false;
    hasSword = false;
    levelComplete = false;
    foundLava = false;
    foundSpikes = false;
    foundPit = false;
    isAlive = true;
    hasCipher = false;
    
    correctStones = 0;
  
    info = "";
    for(int i = 1; i < 20; i++)
    {
        for(int j = 1; j < 20; j++)
        {
            map[i][j] = '.';
            mapCopy[i][j] = '.';
            filledMap[i][j] = ".";
        }
    }
    filledMap[1][1] = "†";
    filledMap[2][1] = "Ø";
    filledMap[6][1] = "∆";
    filledMap[13][1] = "∆";
    filledMap[14][1] = "∆";
    filledMap[18][1] = "Ø";
    filledMap[19][1] = "†";
    
    filledMap[1][2] = "∆";
    filledMap[2][2] = "∆";
    filledMap[6][2] = "∆";
    filledMap[18][2] = "∆";
    filledMap[19][2] = "∆";
    
    filledMap[9][3] = "∫";
    
    filledMap[5][4] = "∆";
    
    filledMap[5][5] = "∆";
    
    filledMap[2][6] = "O";
    filledMap[5][6] = "∆";
    filledMap[17][6] = "¥";
    filledMap[15][6] = "∆";
    
    filledMap[9][9] = "∆";
    filledMap[10][9] = "∆";
    filledMap[11][9] = "∆";
    
    filledMap[2][10] = "∆";
    filledMap[3][10] = "∆";
    filledMap[5][10] = "O";
    filledMap[9][10] = "∆";
    filledMap[11][10] = "Ø";
    filledMap[12][10] = "Ω";
    
    
    // for debugging - instant win
     // filledMap[11][10] = "."; //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     // filledMap[12][10] = "."; //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    filledMap[2][11] = "∆";
    filledMap[9][11] = "∆";
    filledMap[10][11] = "∆";
    filledMap[11][11] = "∆";
    
    filledMap[8][19] = "~";
    filledMap[2][12] = "∆";
    filledMap[16][12] = "∆";
    filledMap[17][12] = "∆";
    
    filledMap[2][14] = "O";
    filledMap[9][14] = "∆";
    filledMap[10][14] = "∆";
    
    filledMap[9][15] = "∆";
    filledMap[15][15] = "∆";
    filledMap[16][15] = "∆";
    filledMap[17][15] = "∆";
    
    filledMap[5][16] = "√";
    filledMap[14][16] = "Ø";
    filledMap[15][16] = "∑";
    filledMap[16][16] = "∆";
    
    filledMap[2][17] = "∆";
    filledMap[3][17] = "∆";
    filledMap[15][17] = "∆";
    
    filledMap[9][18] = "∆";
    filledMap[10][18] = "Ø";
    filledMap[11][18] = "∆";
    
    filledMap[1][19] = "≈";
    filledMap[4][19] = "∆";
    filledMap[5][19] = "∆";
    filledMap[9][19] = "∆";
    filledMap[10][19] = "†";
    filledMap[11][19] = "∆";
    
    for(int i = 1; i < 20; i++)
    {
        for(int j = 1; j < 20; j++)
        {
            filledMapCopy[i][j] = filledMap[i][j];
        }
    }
    
    map[10][10] = mapCopy[10][10] = 'x';
    filledMap[10][10] = filledMapCopy[10][10] = "x";
    xPos = 19;
    yPos = 19;
    map[yPos][xPos] = '@';
    filledMap[yPos][xPos] = "@";
}

void Player::printMap()    // prints the map after each valid move.
{
    system("clear");
    for(int i = 1; i < 20; i++)
    {
        cout << "          ";
        for(int j = 1; j < 20; j++)
        {
            if(!hasMap)
                cout << map[i][j] << " ";
            else
                cout << filledMap[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

char Player::getChoice()       // lets the player move freely around the map based on a switch statement
{
    cout << info << endl;
    cout << "A = Left\nD = Right\nW = Up\nS = Down\nK = Kill Yourself" << endl;
    string c;
    while(true)
    {
        cout << "\nEnter Choice here: ";
        cin >> c;
        switch(c.at(0))
        {
            case 'A':
            case 'a':
            case 'D':
            case 'd':
            case 'W':
            case 'w':
            case 'S':
            case 's':
            case 'K':
            case 'k': return toupper(c.at(0));
            default: cout << "Needs to be 'A', 'B', 'C','D', or 'K'.\n";
                break;
        }
    }
}

void Player::mapReset()    // resets the map after each move or item pick up.
{
    for(int i = 1; i < 20; i++)
    {
        for(int j = 1; j < 20; j++)
        {
            map[i][j] = mapCopy[i][j];
            filledMap[i][j] = filledMapCopy[i][j];
        }
    }
}

void Player::hitMountain()  // unused hit mountain collision. used for later dlc.
{
    
}

void Player::hitObject(int x, int y)    // more collision detection for items / pick ups
{
    map[y][x] = mapCopy[y][x] = filledMap[y][x];
    if(map[y][x] == "∆")
    {
        info = "You hit a mountain. You can't go this way!";
    }
    else if(map[y][x] == "¥")
    {
        info = "You found the Trident!";
        hasTrident = true;
        map[y][x] = mapCopy[y][x] = filledMap[y][x] = filledMapCopy[y][x] = ".";
    }
    else if(map[y][x] == "~")
    {
        info = "You found the Cipher!";
        hasCipher = true;
        map[y][x] = mapCopy[y][x] = filledMap[y][x] = filledMapCopy[y][x] = ".";
    }
    else if(map[y][x] == "∑")
    {
        info = "You found the Map!";
        hasMap = true;
        map[y][x] = mapCopy[y][x] = filledMap[y][x] = filledMapCopy[y][x] = ".";
    }
    else if(map[y][x] == "Ø" && y == 18 && x == 1)
    {
        info = "You found a ravine!";
        foundEntrance = true;
        if (hasHook == true) {
            info += " You found a grapple hook earlier, you see a ledge on the other side. You toss the grapple to the other side and use it to swing across!";
            map[y][x] = mapCopy[y][x] = filledMap[y][x] = filledMapCopy[y][x] = ".";
            isAlive = true;
        }
        else if (hasHook == false && foundPit == true)
        {
            cout << "You attempt to walk across the ravine and plummet down to your death... wth dude your not Indiana Jones" << endl;
            isAlive = false;
        }
        else
        {
            foundPit = true;
        }
    }
    else if(map[y][x] == "Ø" && y == 2 && x == 1)
    {
        info = "You found a floor of spikes!";
        foundEntrance = true;
        if (hasShoes == true) {
            info += " You pull out those tough shoes that you found earlier and put them on... Jack says to make sure you do a flip\nYou slowly walk forward and realize that the spikes do not penetrate the shoes and you walk across.";
            map[y][x] = mapCopy[y][x] = filledMap[y][x] = filledMapCopy[y][x] = ".";
            isAlive = true;
        }
        else if (hasShoes == false && foundSpikes == true)
        {
            cout << "You walk forward and get impaled by spikes. You get shish kabobed." << endl;
            isAlive = false;
        }
        else
        {
            foundSpikes = true;
        }
    }
    else if(map[y][x] == "Ø" && y == 10 && x == 18)
    {
        info = "You found a pit of lava!";
        foundEntrance = true;
        if (hasTrident == true) {
            info += " You pull out the trident you found, you notice a dusty engraving, you wipe it off and realize this is Posiedons staff.\nYou place the staff in the lava and the staff activates. The lava turns into rock as water spews out of the staff.";
            map[y][x] = mapCopy[y][x] = filledMap[y][x] = filledMapCopy[y][x] = ".";
            isAlive = true;
        }
        else if (hasTrident == false && foundLava == true)
        {
            cout << "You fall into the lava and die... why did you think you could walk on lava?" << endl;
            isAlive = false;
        }
        else
        {
            foundLava = true;
        }
    }
    else if(map[y][x] == "Ø" && y == 14 && x == 16)
    {
        info = "You found a large stone door! I wander how to open it?";
        foundEntrance = true;
        if (hasTrident == true && hasHook == true && hasShoes == true) {
            info += "You notice that the three items you found, the trident, the shoes, and the hook, all start to glow.\nYou place the items down at the base of the door and the door starts to hum.\nMagically, the large stone door seems to turn to fog, and slowly vanishes into the thin air.";
            map[y][x] = mapCopy[y][x] = filledMap[y][x] = filledMapCopy[y][x] = ".";
            isAlive = true;
        }
    }
    else if (map[y][x] == "x" && y == 10 && x == 10)
    {
        cout << "As you traverse up the volcano it starts to shake. \n Jack says that he spots something shiny ahead \n\n You quickly climb up the final peak of the volcano and then you see it... \n \n A rocket ship docked into a convienent holder and it appears that it is full of rocket fuel. \n\n As you near the rocket the volcano decides that it will erupt to increase dramatic effect. \n \n You get to the door and go inside. The rocket is controlled by some type of AI system. All the lights turn on and the latch closes behind you. A sexy man robot voice tells you to quickly sit down as you will be launching in 10 seconds.\n\n The countdown begins as you take your seat \n 10..\n9..\n8..\n7..\n6..\n5..\n4..\n3..\n2..\n1.. The rocket roars to life as you feel all the G's push you back in your seat.\n\n The AI voice ahead tells you to stay calm, your first level has been completed but many more await you! \n\n\n\nWelcome aboard captain!\n\n\n\n\n" << endl; cout << "To be continued...\n\n\n\n" << endl;
        
        levelComplete = true;
        isAlive = false;
    }
    else if(map[y][x] == "†" && y == 19 && x == 1)
    {
        if(hasCipher == false)
        info = "You found an encrypted stone! It reads ƒø¨® Ω´®ø"; //40
        else info = "You found an encrypted stone! It reads 40";
        hasStone1 = true;
        map[y][x] = mapCopy[y][x] = filledMap[y][x] = filledMapCopy[y][x] = ".";
    }
    else if(map[y][x] == "†" && y == 1 && x == 1)
    {
        if(hasCipher == false)
        info = "You found an encrypted stone! It reads ƒø¨® ø˜´"; //41
        else info = "You found an encrypted stone! It reads 41";
        hasStone2 = true;
        map[y][x] = mapCopy[y][x] = filledMap[y][x] = filledMapCopy[y][x] = ".";
    }
    else if(map[y][x] == "†" && y == 10 && x == 19)
    {
        if(hasCipher == false)
        info = "You found an encrypted stone! It reads ƒø¨® †∑ø"; //42
        else info = "You found an encrypted stone! It reads 42";
        hasStone3 = true;
        map[y][x] = mapCopy[y][x] = filledMap[y][x] = filledMapCopy[y][x] = ".";
    }

    else if(map[y][x] == "∫")
    {
        info = "You have found a grappling hook!";
        hasHook = true;
        map[y][x] = mapCopy[y][x] = filledMap[y][x] = filledMapCopy[y][x] = ".";
    }
    else if(map[y][x] == "√")
    {
        info = "You found the tough shoes!";
        hasShoes = true;
        map[y][x] = mapCopy[y][x] = filledMap[y][x] = filledMapCopy[y][x] = ".";
    }
    else if(map[y][x] == "Ω")
    {
        info = "OH NOOOO! It's a monster!";
        foundMonster = true;
        if (hasSword == true)
        {
            info += "The monster charges at you, you pull out the sword you found earlier and strike the beast down.";
            isAlive = true;
            map[y][x] = mapCopy[y][x] = filledMap[y][x] = filledMapCopy[y][x] = ".";
        }else if (hasSword == false)
        {
            cout << "The monster charges at you, you realize you dont have anything to protect yourself\n Jack squacks well it sucks to be you...\n The monster has killed you!" << endl;
            isAlive = false;
        }else if (hasTrident == true)
        {
            cout << "The monster charges at you, Jack says to pull out the trident you found earlier, you use pull it out as the beast runs right through it, it shatters without even penetrating its flesh\n Well that sucks. The beast kills you!" << endl;
            isAlive = false;
        }else if (hasShoes == true)
        {
            cout << "The monster charges at you, you remember that you picked up those tough shoes earlier. You put them on real quick. \n Jack proclaims you are an idiot and something about a cracker... The monster makes a snarling laugh sound, and then kills you." << endl;
            isAlive = false;
        }
    }
    else if(map[y][x] == "O" && y == 2 && x == 6) //41
    {
        if (hasCipher == false) {
            info = "You found a stone location! It has an engraving on the rock. It reads\n\n ˙ø∑ µå˜¥ µø¨˜†åˆ˜ß å®´ †˙´®´ ø˜ †˙ˆß ˆß¬å˜∂÷";
        } else {
            info = "You found a stone location! It has an engraving on the rock. It reads\n\n How many mountains are on this island?";
        }
        if(hasStone1 || hasStone2 || hasStone3)
        {
            sa = placeStone(x, y);
            if(sa == 0)
            {
                info = "The stone glows on the stone spot. Yippee?";
                correctStones++;
                if(correctStones == 3)
                {
                    map[11][10] = mapCopy[11][10] = filledMap[11][10] = filledMapCopy[11][10] = ".";
                }
            }
            else if (sa == 1)
            {
                cout << "The stone starts to shake. Then you notice the whole island starts to shake.\nBOOM!!!\nThe island blew up.";
                isAlive = false;
            }
        }
    }
    else if(map[y][x] == "O" && y == 5 && x == 10) //40 ////////////////////////////////////////////////////////////////////////////////////////////////////////
    {
        if (hasCipher == false) {
            info = "You found a stone location! It has an engraving on the rock. It reads\n\n ˙ø∑ µå˜¥ ç®´∑ µå†´ß ∂ˆ∂ ¥ø¨ ˙å√´÷";
        } else {
            info = "You found a stone location! It has an engraving on the rock. It reads\n\n How many crew mates did you have?";
        }
        if(hasStone1 || hasStone2 || hasStone3)
        {
            sa = placeStone(x, y);
            if(sa == 0)
            {
                info = "The stone glows on the stone spot. Yippee?";
                correctStones++;
                if(correctStones == 3)
                {
                    map[11][10] = mapCopy[11][10] = filledMap[11][10] = filledMapCopy[11][10] = ".";
                }
            }
            else if (sa == 1)
            {
                cout << "The stone starts to shake. Then you notice the whole island starts to shake.\nBOOM!!!\nThe island blew up.";
                isAlive = false;
            }
        }
    }
    else if(map[y][x] == "O" && y == 2 && x == 14) //42
    {
        if(hasCipher == false){
        info = "You found a stone location! It has an engraving on the rock. It reads\n\n ∑˙å† ˆß †˙´ å©´ øƒ ∆åç˚÷";
        }else{
            info = "You found a stone location! It has an engraving on the rock. It reads\n\n What is the age of Jack?";
        }
        if(hasStone1 || hasStone2 || hasStone3)
        {
            sa = placeStone(x, y);
            if(sa == 0)
            {
                info = "The stone glows on the stone spot. Yippee?";
                correctStones++;
                if(correctStones == 3)
                {
                    map[11][10] = mapCopy[11][10] = filledMap[11][10] = filledMapCopy[11][10] = ".";
                }
            }
            else if (sa == 1)
            {
                cout << "The stone starts to shake. Then you notice the whole island starts to shake.\nBOOM!!!\nThe island blew up.";
                isAlive = false;
            }
        }
    }
    else if(map[y][x] == "≈")
    {
        info = "You found a sword!";
        info += "You know, if you ever see your old crew again, this would be a nice sword to pay them back!\nAlso, I find it interesting to note that there was just as many crewmates that sailed with you as years you lived on the seas. Funny how you were born on that ship...";
        hasSword = true;
        map[y][x] = mapCopy[y][x] = filledMap[y][x] = filledMapCopy[y][x] = ".";
    }
}
void Player::cipher()
{
    
}
void Player::getStone1()
{
    hasStone1 = true;
}

void Player::getStone2()
{
    hasStone2 = true;
}

void Player::getStone3()
{
    hasStone3 = true;
}

void Player::goLeft()  // allows for players to go left
{
    mapReset();
    xPos -= 1;
    map[yPos][xPos] = '@';
    filledMap[yPos][xPos] = "@";
}
void Player::goRight()   // allows for player to go right
{
    mapReset();
    xPos += 1;
    map[yPos][xPos] = '@';
    filledMap[yPos][xPos] = "@";
}
void Player::goUp()   // allows for players to go up
{
    mapReset();
    yPos -= 1;
    map[yPos][xPos] = '@';
    filledMap[yPos][xPos] = "@";
}
void Player::goDown()  // allows for players to go down
{
    mapReset();
    yPos += 1;
    map[yPos][xPos] = '@';
    filledMap[yPos][xPos] = "@";
}

void Player::introStory()    // this is the main story
{
    cout << "\n\n\n          You have been marooned on an uncharted island for mutiny. Your crewmates make you walk the plank about ½ miles away from shore.\n          They have taken all that you own and allowed you to keep your clothes and boots. You swim to the island shortly have your\n          immediate departure away from your ex-crewmates.[enter]" << endl;
    cin.get();
    
    cout << "          While swimming to shore you notice the captains parrot flying to shore slightly ahead. That damn bird always seemed to like you\n          and seems to have sided with your fate.[enter]" << endl;
    cin.get();
    
    cout << "          You and your parrot Jack both make it to shore… As you look around you tell jack to scout ahead. You spot in the distance a giant\n          volcano. You decide that this is your heading so you can get a better vantage point of the island. As you walk to the tree line\n          from the shore you trip over something.[enter]" << endl;
    cin.get();
    
    cout << "          You pick yourself up and look down to see what you have tripped on. It’s a skull, jack has flown back already and says “You should\n          pick it up”. You now realize that the bird is your survival guide to the island and you should listen to him. He is your elder, after all! You pick up the skull\n          and notice a key and a large piece of paper… it’s a MAP![enter]" << endl;
    cin.get();
    
    cout << "          You look closer at the map and see there is an X on the volcano. This could only mean one thing, a treasure map, and since you are\n          a pirate, we all know that you can’t resist possible treasure[enter].\n\n" << endl;
    cin.get();
}

void Player::stone1Location()
{
    cout << "          You see a shiny object on the other side of the ravine!\n          You lean over it seems to go really far down...\n  Bet you won't do a flip says Jack!\n        How are you going to get over it?\n"<< endl;
    
}

void Player::foundSecretStone1()
{
    cout << "          You find a stone with a message chiseled into it.\n          You take a closer look...\n" << endl;
    cout << "          ß∂ƒ∆´˙∂˚≈˜˜∂˚¬åø∑ˆ´ \n          ∂∆∂˜ç∆∂˚å¬∂∆∑ˆ´¨\n          ˚ˆ∑¥∑ª•∆ç ß∫˙∂¥¶§\n\n" << endl;
    cout << "          What does this even mean?\n\n" << endl;
}
void Player::stone2Location()
{
    cout << "          You see a shiny object on the other side of the lava!\n          You Try blowing at the lava but it doesn't cool down...\n     Meh, just trying doing a running jump says Jack.\n     How are you going to get over it?\n"<< endl;
    
}

void Player::foundSecretStone2()
{
    cout << "          You find a stone with a message chiseled into it.\n          You take a closer look...\n" << endl;
    cout << "          ß∂ƒ∆´˙∂˚≈˜˜∂˚¬åø∑ˆ´ \n          ∂∆∂˜ç∆∂˚å¬∂∆∑ˆ´¨\n          ˚ˆ∑¥∑ª•∆ç ß∫˙∂¥¶§\n\n" << endl;
    cout << "          What does this even mean?\n\n" << endl;
}

void Player::stone3Location()
{
    cout << "          You see a shiny object on the other side of the spikes!\n          You lightly touch one of the spikes and it cuts your finger...\n   Yeah, that's just a flesh wound says Jack.\n       How are you going to get over it?\n"<< endl;
    
}

void Player::foundSecretStone3()
{
    cout << "          You find a stone with a message chiseled into it.\n          You take a closer look...\n" << endl;
    cout << "          ß∂ƒ∆´˙∂˚≈˜˜∂˚¬åø∑ˆ´ \n          ∂∆∂˜ç∆∂˚å¬∂∆∑ˆ´¨\n          ˚ˆ∑¥∑ª•∆ç ß∫˙∂¥¶§\n\n" << endl;
    cout << "          What does this even mean?\n\n" << endl;
}

void Player::directions()
{
    while(true)
    {
        switch (getChoice()) {
            case 'A':
            case 'a':
                if(checkBounds(xPos - 1, yPos))
                {
                    info = "";
                    goLeft();
                    return;
                }
                else
                {
                    hitObject(xPos - 1, yPos);
                    if(isAlive == false)
                    {
                        return;
                    }
                    else
                    {
                        printMap();
                    }
                }
                break;
            case 'D':
            case 'd':
                if(checkBounds(xPos + 1, yPos))
                {
                    info = "";
                    goRight();
                    return;
                }
                else
                {
                    hitObject(xPos + 1, yPos);
                    if(isAlive == false)
                    {
                        return;
                    }
                    else
                    {
                        printMap();
                    }
                }
                break;
            case 'W':
            case 'w':
                if(checkBounds(xPos, yPos - 1))
                {
                    info = "";
                    goUp();
                    return;
                }
                else
                {
                    hitObject(xPos, yPos - 1);
                    if(isAlive == false)
                    {
                        return;
                    }
                    else
                    {
                        printMap();
                    }
                }
                break;
            case 'S':
            case 's':
                if(checkBounds(xPos, yPos + 1))
                {
                    info = "";
                    goDown();
                    return;
                }
                else
                {
                    hitObject(xPos, yPos + 1);
                    if(isAlive == false)
                    {
                        return;
                    }
                    else
                    {
                        printMap();
                    }
                }
                break;
            case 'K':
            case 'k':
                isAlive = false;
                return;
            default:
                backToMap = true;
                break;
        }
    }
}

int main()  // printing all the functions that allows for the game to run.
{
    Player player;
    while(true)
    {
        player.introStory();
    
        do{
            player.printMap();
            player.directions();
            if(player.getAlive() == true)
            {
                system("clear");
            }
        }while(player.getAlive() == true && player.isComplete() == false);
        cout << "\n\n\n\n                                         Game Over!!\n\n\n\n\n\n\n" << endl;
        cin.get();
        player.resetGame();
    }
}
