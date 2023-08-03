import cv2
import serial
import time
import numpy as np

ser = serial.Serial("COM5", 9600, timeout=1.0)
time.sleep(3)
ser.reset_input_buffer()
print("Serial OK")

lower_red = np.array([9, 197, 139])
upper_red = np.array([178, 255, 192])

lower_green = np.array([62, 101, 87])
upper_green = np.array([100, 253, 227])

try:
    cap = cv2.VideoCapture(0)
    while True:
        ret, frame = cap.read()
        frame = cv2.resize(frame, (640, 480))
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        mask_red = cv2.inRange(hsv, lower_red, upper_red)
        _, mask1 = cv2.threshold(mask_red, 254, 255, cv2.THRESH_BINARY)
        cnts, _ = cv2.findContours(mask1, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

        color_red_area = 0
        for c in cnts:
            x = 600
            if cv2.contourArea(c) > x:
                x, y, w, h = cv2.boundingRect(c)
                cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
                cv2.putText(frame, "DETECT", (10, 60), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 255), 2)
                color_red_area += cv2.countNonZero(mask_red[y:y+h, x:x+w])

        mask_green = cv2.inRange(hsv, lower_green, upper_green)
        _, mask2 = cv2.threshold(mask_green, 254, 255, cv2.THRESH_BINARY)
        cnts1, _ = cv2.findContours(mask2, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

        color_green_area = 0
        for c in cnts1:
            x = 600
            if cv2.contourArea(c) > x:
                x, y, w, h = cv2.boundingRect(c)
                cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
                cv2.putText(frame, "DETECT", (10, 60), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 255), 2)
                color_green_area += cv2.countNonZero(mask_green[y:y+h, x:x+w])

        cv2.imshow("FRAME", frame)

        if color_red_area > color_green_area:
            ser.write("red".encode('utf-8'))
            print("read")
        elif color_green_area > color_red_area:
            ser.write("green".encode('utf-8'))
            print("green")

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
        

    cap.release()
    cv2.destroyAllWindows()

except KeyboardInterrupt:
    print("Serial closed communication")
    ser.close()

    









