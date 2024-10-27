# Pacman Maze Game 🟡

A classic **Pacman-style** game built in **C** using **graphics.h**. Navigate the maze, eat all the pellets, and avoid hitting walls! Each pellet you eat increases your score, but trying to cross a wall will deduct points. The game ends when you eat all the pellets or your score drops to zero.

---

## 🎮 Gameplay

- **Objective**: Guide Pacman through the maze to eat all the pellets while avoiding walls.
- **Points**: Gain points by eating pellets. Avoid crossing walls to prevent losing points.

<p align="center">
  <img src="img/pc1" alt="Pacman Game Demo" width="400"/>
</p>

---

## 🔧 Setup

### Requirements

- **Turbo C** or **Borland C** with `graphics.h` and `conio.h` libraries.

### Installation and Compilation

1. Clone this repository:

   ```bash
   git clone https://github.com/your-username/pacman-maze-game.git
   
2. Open the project in Turbo C or Borland C.

3. Ensure the ```BGI``` path is correctly set in the ```initgraph()``` function in the code:
```bash 
initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
```

4. Compile and Run the project.
   
---

## 🎮 Controls

| Key        | Action           |
|------------|-------------------|
| ⬆️ `UP`    | Move Up          |
| ⬇️ `DOWN`  | Move Down        |
| ⬅️ `LEFT`  | Move Left        |
| ➡️ `RIGHT` | Move Right       |
| `ESC`      | Exit Game        |

---

## 📊 Scoring

- **+10 Points** for each pellet eaten.
- **-5 Points** for each attempt to cross a wall.

---

## 🔍 Code Overview

### 1. **Maze Layout**

   - The maze is stored as a **2D array**, where `1` represents walls and `0` represents open spaces. The `drawMaze()` function reads this array and renders the walls in the game.

### 2. **Collision Detection**

   - **Wall Collision**: Prevents Pacman from crossing walls and deducts points for each attempt.
   - **Pellet Collision**: When Pacman’s position overlaps with a pellet, it “eats” the pellet, increasing the score.

### 3. **Game Over Condition**

   - The game ends when Pacman eats all pellets or when the score reaches zero.

---

## 🖼️ Visuals

<p align="center">
  <img src="https://user-images.githubusercontent.com/example/pacman-maze.png" alt="Pacman Maze Screenshot" width="500"/>
</p>

---

## 👩‍💻 Contributing

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/YourFeature`).
3. Commit your changes (`git commit -am 'Add YourFeature'`).
4. Push to the branch (`git push origin feature/YourFeature`).
5. Open a Pull Request.

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## 📧 Contact

For any questions or feedback, reach out at **radhikaa.godambe@gmail.com**.


