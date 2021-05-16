import serial
import struct
ser = serial.Serial('/dev/ttyACM0', 9600, serial.EIGHTBITS, serial.PARITY_NONE, serial.STOPBITS_ONE, 1)

readBytes = bytearray([0, 0, 0, 0, 0, 0, 0, 0, 0])

def zero():
    ser.read(8)
    return "zero"

def one():
    readBytes = ser.read(1)
    ser.read(7)
    return struct.unpack('B', readBytes)[0]
 
def two():
    readBytes = ser.read(2)
    ser.read(6)
    return struct.unpack('H', readBytes)[0]
 
def three():
    readBytes = ser.read(4)
    ser.read(4)
    return struct.unpack('I', readBytes)[0]
 
def four():
    readBytes = ser.read(8)
    return struct.unpack('L', readBytes)[0]
 
def five():
    readBytes = ser.read(1)
    ser.read(7)
    return struct.unpack('b', readBytes)[0]
 
def six():
    readBytes = ser.read(2)
    ser.read(6)
    return struct.unpack('h', readBytes)[0]
 
def seven():
    readBytes = ser.read(4)
    ser.read(4)
    return struct.unpack('i', readBytes)[0]
 
def eight():
    readBytes = ser.read(8)
    return struct.unpack('l', readBytes)[0]
 
def nine():
    readBytes = ser.read(4)
    ser.read(4)
    return struct.unpack('f', readBytes)[0]
 
def ten():
    readBytes = ser.read(8)
    return struct.unpack('d', readBytes)[0]
 
def eleven():
    readBytes = ser.read(8)
    if readBytes[0] != 0 :
        return "True"
    return "False"
  
def thirteen():
    readBytes = ser.read(8)
    return hex(readBytes[0]) + " " + hex(readBytes[1]) + " " + hex(readBytes[2]) + " " + hex(readBytes[3]) + " " + hex(readBytes[4]) + " " + hex(readBytes[5]) + " " + hex(readBytes[6]) + " " + hex(readBytes[7])
 
def twelvefourteen():
    offset = int(input("Enter Offset: "))
    sendBytes = bytearray([offset, 0, 0, 0])
    ser.write(sendBytes)
    readBytes = ser.read(8)
    return hex(readBytes[0]) + " " + hex(readBytes[1]) + " " + hex(readBytes[2]) + " " + hex(readBytes[3]) + " " + hex(readBytes[4]) + " " + hex(readBytes[5]) + " " + hex(readBytes[6]) + " " + hex(readBytes[7])

while True:
    variableID = int(input("Enter id of variable to check: "))

    sendBytes = bytearray([variableID, 0, 0, 0])
    ser.write(sendBytes)
    readType = ser.read(1)
    if len(readType) > 0:
        switcher = {
            0: zero,
            1: one,
            2: two,
            3: three,
            4: four,
            5: five,
            6: six,
            7: seven,
            8: eight,
            9: nine,
            10: ten,
            11: eleven,
            12: twelvefourteen,
            13: thirteen,
            14: twelvefourteen
        }
        # Get the function from switcher dictionary
        func = switcher.get(readType[0], lambda: "Invalid Type")
        # Execute the function
        print(func())

ser.close()