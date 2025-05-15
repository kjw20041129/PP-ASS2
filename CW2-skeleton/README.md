```markdown
# Maze Game Player's Guide

Welcome to the Maze Game! Navigate through the maze from the start (`S`) to the end (`E`). This guide will help you get started and enjoy the game.

---

## Table of Contents
- [Game Objective](#game-objective)
- [How to Run the Game](#how-to-run-the-game)
- [Prepare a Maze File](#prepare-a-maze-file)
- [Compile the Game](#compile-the-game)
- [Start the Game](#start-the-game)
- [Gameplay](#gameplay)
- [Example](#example)
- [Important Notes](#important-notes)
- [Enjoy the Game!](#enjoy-the-game)

---

## Game Objective
- **Start (`S`)**: Your starting point.
- **End (`E`)**: Your goal.
- **Walls (`#`)**: Cannot pass through.
- **Paths (` `)**: Open spaces where you can move.

---

## How to Run the Game

### Prepare a Maze File
The game requires a maze file to load the map. You can either:
1. **Manually create a maze file** (see format below), or  
2. **Generate one** using the provided tool.

---

### Manually Create a Maze File
1. Use a text editor to create a maze file.
2. Follow this format:
   ```plaintext
   ##########
   #S       #
   # # ######
   # #      #
   # ###### #
   #       E#
   ##########
   ```
3. **Requirements**:
   - Must contain **one `S` (start)** and **one `E` (end)**.
   - Dimensions (width/height) must be **between 5 and 100**.
   - Valid characters: `#` (walls), ` ` (empty spaces), `S`, `E`.

---

### Generate a Maze File
1. Compile the maze generator:
   ```bash
   gcc -o mazegen mazegen.c -I.
   ```
2. Generate a maze:
   ```bash
   ./mazegen <filename> <width> <height>
   ```
   - Replace `<filename>` with your maze file name.
   - Set `<width>` and `<height>` to values **between 5 and 100**.

---

### Compile the Game
1. Open a terminal.
2. Navigate to the game project directory.
3. Compile the game:
   ```bash
   gcc -o maze main.c game.c maze.c -I.
   ```

---

### Start the Game
Run the game with your maze file:
```bash
./maze <maze_file>
```
- Replace `<maze_file>` with the path to your maze file.

---

## Gameplay
- **Movement Controls**:
  - `W`: Move up
  - `A`: Move left
  - `S`: Move down
  - `D`: Move right
  - `M`: Display maze
  - `Q`: Quit game
- **Objective**: Reach the endpoint (`E`) to win.

---

## Example
1. For a maze file `example.maze`:
   ```plaintext
   ##########
   #S       #
   # # ######
   # #      #
   # ###### #
   #       E#
   ##########
   ```
2. Start the game:
   ```bash
   ./maze example.maze
   ```

---

## Important Notes
- Ensure your maze file is **correctly formatted**.
- The generator will discard mazes with **no valid path**.
- Missing `S` or `E` will trigger an error and prevent the game from starting.

---

## Enjoy the Game!
Have fun exploring the maze! For issues or suggestions, feel free to reach out. 🎮
``` 

This README uses proper Markdown formatting with:
- Clear section headers (`##`, `###`)
- Code blocks for commands and examples
- Bulleted/numbered lists for steps and rules
- Emphasis on key terms (**bold**)
- Anchors for table of contents links
- Consistent spacing and indentation
- Emoji in the final section for flair 😊