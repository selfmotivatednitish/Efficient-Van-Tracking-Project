# include library
import serial
import time

COM = 'COM19'
baud = 115200

connected = False

fileName = "dataFile.csv"
file = open(fileName, "a")
print("Created file")

try:
    arduino = serial.Serial(COM,baud)
    connected = True
    print("Arduino is connected")
except:
    print("Check COM port")


while connected:
    try:
        ser_bytes = arduino.readline()
        decoded_bytes = str(ser_bytes[0:len(ser_bytes) - 3])
        print(decoded_bytes[2:-1])
        file = open(fileName, "a")
        file.write(decoded_bytes[2:-1] + "\n")
    except:
        print("Arduino is disconnected")
        print("Data Collection complete!")
        file.close()
        break