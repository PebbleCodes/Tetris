# Tetris 2019
Originally a class project from 2019 where I was tasked to program a recreation of the classic game,
Tetris. Since we were learning C++ in the class, the language I had to write this recreation in was
C++. Nowadays, I mainly program in Java, so this project likely won't receive many more updates. In 
fact, I may rewrite this project in Java to continue some of the development I had planned for it.

### How to Play
Fill the well up with the Tetrimino blocks. If you do not like the current Tetrimino in play, you 
can hold (or store) that Tetrimino for later use. Once you want to use that Tetrimino again, press
the same key to switch it back. This action can only be done once per Tetrimino dropped, so you can 
not continuously swap the Tetrimino's to get yourself back up to the top. When you completely
fill a row with Tetrimino blocks, that line clears out and you get points. Clear four lines with one 
Tetrimino and you get 4x the amount of normal points! Try to survive as long as possible, as once the
Tetriminos reach the top, the game is over! Also be careful, as you clear more rows, the Tetrimino 
will begin to fall faster. Have fun!

#### Controls
| Key         | Action                 |
|-------------|------------------------|
| Left Arrow  | Move Left              |
| Right Arrow | Move Right             |
| Down Arrow  | Move Down              |
| Up Arrow    | Rotate Tetrimino       |
| Space Bar   | Drop Tetrimino         |
| Right Shift | Hold (Store) Tetrimino |

#### Scoring
Score is calculated as follows:
- Normal Calculation: 
  - `currentLevel * 10 * rowsCleared`
- Four Rows in One Calculation (Tetris): 
  - `4 * (currentLevel * 10 * rowsCleared)`
  - TODO: this should actually give a bonus. In fact, the scoring appears to need to be reworked in general: https://tetris.wiki/Scoring

### How to Compile the Project
#### MacOS
If SFML has not been installed yet, install SFML
```commandline
brew install sfml
```

To verify where SFML was installed, run
```commandline
brew info sfml
```

The below compilation and build command is based on the following output from this command
```commandline
Installed
/opt/homebrew/Cellar/sfml/2.6.1 (813 files, 12.7MB) *
```

Compile and Build Application (using the location where SFML was installed)
```commandline
g++ *.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include -o tetris \
-L/opt/homebrew/Cellar/sfml/2.6.1/lib \
-lsfml-graphics \
-lsfml-window \
-lsfml-audio \
-lsfml-system
```

Running the Application
```commandline
./tetris
```
You can start the application by running the above command in your terminal where the file was compiled
(**[directory where project was installed]**/Tetris/tetris).

#### Windows
*TBD* (might be the same commands for MacOS)