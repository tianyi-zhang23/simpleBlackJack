# simpleBlackJack
A simple black jack game in command line written in C++

### Rules:
At the beginning of the game, the casino is dealt one card, and the player two cards. The player can choose to draw as many cards as possible, until his/her points exceed 21, in which case he/she busts (loses). If the player decides to stop drawing cards before busting, the computer will draw. Whoever got the higher total but does not exceed 21 wins.

### How to Run
If you are using Linux on an Intel x64 machine, simply download, chmod +x, and run the executable file `simpleBlackJack`. This executable has been compiled in Ubuntu 19.04 on an Intel x64 machine with G++. To run on other platforms, simply download all `.cpp` and `.h` files and compile with a C++ compiler.
 ```
 g++ main.cpp blackjack.cpp -o simpleBlackJack
 ```

Done as part of COMP322 at McGill University
