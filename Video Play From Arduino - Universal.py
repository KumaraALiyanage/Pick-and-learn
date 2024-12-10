import subprocess
import logging
import serial
import json
import os
import platform
import sys
import configparser

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s - %(levelname)s - %(message)s",
    handlers=[logging.FileHandler("video_log.txt"), logging.StreamHandler(sys.stdout)],
)

config = configparser.ConfigParser()
config.read("settings.ini")

if "Paths" not in config:
    config["Paths"] = {}
if "video_folder" not in config["Paths"]:
    default_video_folder = "D:/Ragu Anna/Video-Play-From-Arduino-main/Video-Play-From-Arduino-main/Content"
    video_folder = input(
        f"Enter the path to the video folder (default: {default_video_folder}): "
    )
    video_folder = video_folder.strip() or default_video_folder
    config["Paths"]["video_folder"] = video_folder

if "Serial" not in config:
    config["Serial"] = {}
if "serial_port" not in config["Serial"]:
    serial_port = input("Enter the Arduino Serial Port: ")
    config["Serial"]["serial_port"] = serial_port

if "baudrate" not in config["Serial"]:
    baudrate = input("Enter the baud rate: ")
    baudrate = int(baudrate) if baudrate.isdigit() else 9600
    config["Serial"]["baudrate"] = str(baudrate)

if "Paths" not in config or "media_player_path" not in config["Paths"]:
    media_player_path = input("Enter the path to the media player executable file: ")
    config["Paths"]["media_player_path"] = media_player_path

if "Stop" not in config:
    config["Stop"] = {}
if "stop_number" not in config["Stop"]:
    stop_number = input("Enter the desired number to use to stop the program: ")
    config["Stop"]["stop_number"] = stop_number

with open("settings.ini", "w") as configfile:
    config.write(configfile)

video_folder = config.get("Paths", "video_folder")
serial_port = config.get("Serial", "serial_port")
baudrate = config.getint("Serial", "baudrate")
media_player_path = config.get("Paths", "media_player_path")
stop_number = config.get("Stop", "stop_number")

video_mapping = {}
for root, dirs, files in os.walk(video_folder):
    for index, file in enumerate(files, start=1):
        number = str(index)
        video_mapping[number] = os.path.join(root, file)

with open("video_mapping.json", "w") as file:
    json.dump(video_mapping, file)

current_process = None

serial_port_value = config.get("Serial", "serial_port")

while True:
    try:
        serial_port = serial.Serial(serial_port_value, baudrate)
        break
    except serial.SerialException as e:
        logging.error(f"Error opening serial port: {e}")
        if serial_port_value:
            serial_port_value = input("Enter the Arduino Serial Port (e.g., COM3): ")
        else:
            break

if serial_port is None:
    serial_port_value = input("Enter the Arduino Serial Port (e.g., COM3): ")
    serial_port = serial.Serial(serial_port_value, baudrate)

while True:
    try:
        line = serial_port.read().decode().strip()
    except Exception as e:
        logging.error(f"Error reading from serial port: {e}")
        serial_port.close()
        serial_port_value = config.get("Serial", "serial_port")
        while True:
            try:
                serial_port = serial.Serial(serial_port_value, baudrate)
                break
            except serial.SerialException as e:
                logging.error(f"Error opening serial port: {e}")
                if serial_port_value:
                    serial_port_value = input(
                        "Enter the Arduino Serial Port (e.g., COM3): "
                    )
                else:
                    break
        continue

    try:
        number = int(line)
    except ValueError:
        logging.error(f"Received non-integer value: {line}")
        continue

    number = str(number)

    # Stop the current video if one is playing
    if current_process is not None:
        current_process.terminate()
        current_process.wait()

    # Get the video file for the current number
    current_video = video_mapping.get(number)
    if current_video:
        logging.info(f"Number: {number} - Playing video: {current_video}")
        try:
            current_process = subprocess.Popen(
                [media_player_path, "--fullscreen", current_video]
            )
        except Exception as e:
            logging.error(f"Error playing video: {e}")
    else:
        logging.info(f"No video found for the number: {number}")

# Close the serial port connection
serial_port.close()
