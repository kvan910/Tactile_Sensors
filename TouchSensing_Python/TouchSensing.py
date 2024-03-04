#Touch Sensor Reading
import serial   
import time
import matplotlib.pyplot as plt

BAUDRATE = 921600

def main():
    #setting up serial line
    ser = serial.Serial('COM5', BAUDRATE)
    reader = ReadLine(ser)
    time.sleep(2)
    Startup = True
    # Read and record the data
    data =[]                                # empty list to store the data
    while(Startup):
            b = reader.readline()           # Reads a byte string
            string_n = b.decode()           # decode byte string into Unicode  
            string = string_n.rstrip()      # remove \n and \r
            if(string.startswith("Begin")): # identifies the end of the startup sequence
                Startup = False
            print(string)
    #start of sensor values
    while(True):
            b = reader.readline()           # Reads a byte string
            string_n = b.decode()           # decode byte string into Unicode
            string = string_n.rstrip()      # remove \n and \r
            string = string.split()         # splits the string into individual sensor values    
            #print(string)
            Fingertip_val_1 = eval(string[0])
            Fingertip_val_2 = eval(string[1])
            print(Fingertip_val_1 ,Fingertip_val_2)
        

class ReadLine:
    def __init__(self, s):
        self.buf = bytearray()
        self.s = s
    
    def readline(self):
        i = self.buf.find(b"\n")
        if i >= 0:
            r = self.buf[:i+1]
            self.buf = self.buf[i+1:]
            return r
        while True:
            i = max(1, min(2048, self.s.in_waiting))
            data = self.s.read(i)
            i = data.find(b"\n")
            if i >= 0:
                r = self.buf + data[:i+1]
                self.buf[0:] = data[i+1:]
                return r
            else:
                self.buf.extend(data)

if __name__ == '__main__':
    main()