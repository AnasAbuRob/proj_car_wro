import serial
import time
import red_green
import numpy as np
ser=serial.Serial("COM4",9600,timeout=1.0)
time.sleep(3)
ser.reset_input_buffer()
print("Serial OK")
try:
    while True:
        time.sleep(0.01)
        if ser.in_waiting>0:
            line=ser.readline().decode('utf-8')
              
            lower_red = np.array([9, 197, 139])
            upper_red = np.array([178, 255, 192])

        
            lower_green = np.array([62, 101, 87])
            upper_green = np.array([100, 253, 227])

            red_area = red_green.calculate_color_area(lower_red, upper_red)
            green_area = red_green.calculate_color_area(lower_green, upper_green)
            
            if red_area > green_area:
                ser.write("red".encode('utf-8'))
            elif green_area > red_area:
                ser.write("green".encode('utf-8'))
            else:
                continue
except KeyboardInterrupt:
    print("Serial closed communication")
    ser.close()
    









