import serial
import pyttsx3

ser = serial.Serial('COM5', 9600, timeout=1)  # Set the correct COM port
tts = pyttsx3.init()

def speak(text):
    tts.say(text)
    tts.runAndWait()

while True:
    if ser.in_waiting:
        line = ser.readline().decode('utf-8', errors='ignore').strip()
        
        if "obstacle detected" in line.lower():
            print("Obstacle detected")
            speak("Obstacle detected")
