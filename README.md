# Dino-project
Creating a Dino project using Atmega32 and LCD 
# ATmega32 Chrome Dino Game 🦖

A lightweight, fully functional recreation of the classic Chrome Dinosaur Game, running on an ATmega32 microcontroller and a 16x2 character LCD. 

This project was built from scratch using custom-written drivers (Bare-metal C) for the AVR peripherals, focusing on clean hardware interfacing and optimized performance.

## 🚀 Features
* **Smooth Animations:** Utilizes LCD Custom Characters (CGRAM) to render the running dinosaur, moving cactus, and flying birds.
* **Dynamic Physics:** The game accelerates progressively, and the jump duration adjusts automatically to match the game's current speed.
* **Sound Effects:** A passive buzzer provides real-time feedback for jumping, scoring points (every 100 points), and game-over states.
* **Optimized Resources:** Uses a modular layered architecture and operates the LCD in 4-bit mode to save MCU pins.

## 🔌 Hardware Setup & Wiring
**Engineering Note:** To ensure stability and avoid hardware conflicts with the ATmega32's default JTAG interface (which reserves pins `PC2` to `PC5`), the LCD Enable pin was explicitly routed to `PC7`.

| Component | ATmega32 Pin | Connection Note |
| :--- | :--- | :--- |
| **LCD RS** | `PC0` | Control Pin |
| **LCD RW** | `PC1` | Control Pin |
| **LCD Enable** | `PC7` | *Bypassed JTAG conflict* |
| **LCD D4 - D7** | `PD4 - PD7` | 4-Bit Data Mode |
| **Push Button** | `PA0` | Jump trigger (Active High) |
| **Buzzer** | `PA1` | Sound output |

## 📁 Project Structure
The codebase follows a standard embedded systems layered architecture:
* **MCAL:** Custom `DIO` (Digital Input/Output) driver.
* **HAL:** Custom `LCD` driver configured for 4-bit operation.
* **APP:** Main game logic, state machines, and timer handling (`main.c`).

## 🎮 How to Run (Simulation)
You can easily test the game without hardware using Proteus:
1. Clone or download this repository.
2. Open the `DINO_GAME_PROJECT.pdsprj` file using **Proteus**.
3. The microcontroller is already linked to the provided `lab1.hex` file.
4. Hit **Play** and use the interactive push button to jump!
