# Video Player with Arduino Serial Control

## Introduction

This code allows you to control a video player application using an Arduino board via serial communication. The code listens for commands from the Arduino and plays corresponding videos based on the received commands. It provides features such as video mapping, logging, and the ability to stop the program with a specified number.

## Prerequisites

To run this code, you need to have the following:

- Arduino board (e.g., Arduino Uno)
- Arduino IDE or compatible software
- MPV media player (or any other media player that can be launched with the specified command: `media_player_path --fullscreen current_video`
- Python (if running the Python code directly)
- Required Python libraries: `subprocess`, `logging`, `serial`, `json`, `os`, `platform`, `sys`
- (Optional) Configurable settings file: `settings.ini` (included)

## Files Included

1. Arduino Code (`Video_Control_Transmeter.ino`): This Arduino code is used for the demo. It sends commands over serial communication to control the video playback. You can modify this code according to your needs.

2. Python Code (`Video Play From Arduino - Universal.py`): This Python code interacts with the Arduino board over serial communication. It reads commands from the Arduino and plays corresponding videos using the specified media player. You can modify the code to customize the behavior and settings.

3. Executable File (`Video Play From Arduino - Universal.exe`): This is an executable file of the Python code, which means you don't need to install Python or its libraries separately. You can directly run this file to control the video playback with the Arduino.

## Usage

Here is a step-by-step guide on how to use the code:

1. Connect your Arduino board to the computer.
2. Upload the Arduino code (`Video_Control_Transmeter.ino`) to the Arduino board using the Arduino IDE or compatible software.
3. Make sure you have the MPV media player (or any other compatible media player) installed on your system.
4. (Optional) Modify the necessary settings in the code or the settings.ini file:
   - Specify the video folder path (`video_folder`) where your video files are located.
   - Specify the Arduino Serial Port (`serial_port`) to establish a serial connection.
   - Specify the desired baud rate (`baudrate`) for serial communication.
   - Specify the path to the media player executable file (`media_player_path`).
   - Specify the desired number to use to stop the program (`stop_number`).

5. Organize your video files in the video folder specified.
6. Run the code by either:
   - Running the Python code (`Video Play From Arduino - Universal.py`) using Python and the required libraries.
   - Running the executable file (`Video Play From Arduino - Universal.exe`) directly without needing to install Python.

7. The code will establish a serial port connection with the Arduino and listen for commands.
8. When a command is received from the Arduino, the code will check if it matches the stop number. If yes, the program will stop.

   - If the received command is a valid number, the code will play the corresponding video in fullscreen mode using the specified media player.
   - If the received command is not a valid number, it will be logged as an error.

9. You can stop the program by sending the stop number from the Arduino or entering it manually.

Note: Make sure you have the necessary dependencies installed and properly configured (Arduino board, Arduino code, media player, etc.) for the code to work correctly.

Feel free to modify the code according to your specific requirements. Enjoy controlling the video playback with Arduino!
