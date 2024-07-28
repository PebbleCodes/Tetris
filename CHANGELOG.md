# Changelog (v1.2)
## 7/28/24 - Fixes for MacOS and Updated Documentation  (v1.2)
- Moved files around to be more organized
- Moved documentation to proper README.md and CHANGELOG.md files
- Added documentation for compiling the project on MacOS
- Fixed code to compile properly on MacOS

## 3/2/19 - Minor Fixes (v1.1)
- Made the score reset once the game ends, fixing an issue where
if you click "Play Again" the previous score will remain
- Made the held Tetrimino get deleted once the game ends, fixing 
an issue where if you click "Play Again" the held Tetrimino
from the last game remained in the next game.

## 2/26/19 - Initial Release (v1.0)

Features in this current release are as follows:

- Move the Tetrimino left, right, and down using the arrow keys
- Drop the Tetrimino as far down as it will go using the spacebar
- Hold the Tetrimino to the side if you do not want to use it 
		at that moment using the right shift key. Once you want 
		to use it, press the right shift key again to bring it 
		back. There can only be one swap per Tetrimino dropped,
		so you can not continuously swap to get a "redo" and
		bring the Tetrimino in play back up to the top of the
		well.
- Levels - There are currently 15 levels in the game. As you
		go up a level, the game will get a little harder, as
		the Tetriminos will begin to fall faster. The level
		is shown at the top left of the screen.
- Score - The score is displayed on the bottom left of the screen. 
  - Score is calculated as follows:
    - Normal Calculation = `currentLevel * 10 * rowsCleared`
    - Four Rows in One Calculation = `4 * (currentLevel * 10 * rowsCleared)`

## Upcoming Features:

Planned features for upcoming releases

- High score list
- Store + Coins
- Ability to pick different textures for the blocks