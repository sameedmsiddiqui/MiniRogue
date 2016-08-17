# MiniRogue

Emulation of UNIX's text-based Rogue game. This game can be compiled with gcc on a Unix-based system or on Visual Studio on Windows. 

* **(Note that the most interesting files to read in the project are 'Goblin.cpp', 'Dungeon.cpp', 'Game.cpp', and 'Player.cpp'. A pre-compiled file 'Minirogue Compiled.exe' is available for Windows systems)**




The player (represented by an '@' sign) is displayed in some position in a randomly-generated dungeon map. The player works his or her way through the maze, battling monsters, finding treasures, and descendind down staircases to descend lower into the dungeon. When the player reaches the bottom of the dungeon, he or she can scavenge for the golden idol. The player wins the game instantly when the golden idol is picked up.

Different monsters are shown are: 
* Bogeymen (shown on screen as a B)
* Dragons (shown on screen as a D)
* Goblins (shown on screen as a G)
* Snakewomen (shown on screen as an S)

Each monster has its own abilities and different behaviors.

In addition to monsters, there are:
* imprentatable walls (shown on screen as #)
* Stairways down to the next level (shown on screen as >)
* The golden idol (shown on screen as &)
* Weapons (all weapons are shown on screen as a ) character)
  * Maces
  * Short swords
  * Long swords
  * Magic fangs of sleep (that put an opponent to sleep)
  * Magic axes (that hit an opponent more often than regular weapons)
* Scrolls (all scrolls are shown on screen as ?)
  * A scroll of teleportation (when read, randomly moves the player)
  * A scroll of improve armor (when read, makes it harder for monsters to hit the player)
  * A scroll of raise strength (when read, makes a player's blows more effective)
  * A scroll of enhance health (when read, raises maximum hit points)
  * A scroll of enhance dexterity (when read, makes it more likely the player will hit an opponent )


To control the player in the game, you issue commands from the keyboard. 

* Move one space using the arrow keys or the classic Rogue movement letters:
  * h to move left
  * l to move right
  * k to move up
  * j to move down
* Attack a monster next to you by moving in its direction.
* Pick up an object by standing on it and typing g.
* Wield a weapon by typing w and then selecting a weapon from your inventory.
* Read a scroll by typing r and then selecting a scroll from your inventory.
* See an inventory of your items by typing i.
* When standing on a stairway, descend deeper into the dungeon by typing >.
* Quit the game by typing q.
* Cheat by typing c. This command sets the player's characteristics to make defeating monsters easy, to better explore the program

