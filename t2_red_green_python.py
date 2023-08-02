import cv2
import numpy as np

def calculate_color_area(lower_color_range, upper_color_range):
    cap = cv2.VideoCapture(0)


    ret, frame = cap.read()
    frame = cv2.resize(frame, (640, 480))
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(hsv, lower_color_range, upper_color_range)
    _, mask1 = cv2.threshold(mask, 254, 255, cv2.THRESH_BINARY)
    cnts, _ = cv2.findContours(mask1, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

    color_area = 0
    for c in cnts:
        x = 600
        if cv2.contourArea(c) > x:
            x, y, w, h = cv2.boundingRect(c)
            cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
            cv2.putText(frame, "DETECT", (10, 60), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 255), 2)

            # حساب مساحة اللون المحدد
            color_area += cv2.countNonZero(mask[y:y+h, x:x+w])

    cv2.imshow("FRAME", frame)

    cap.release()
    cv2.destroyAllWindows()
    return color_area

# if __name__ == "__main__":
#     # تعريف نطاق اللون الأحمر
#     lower_red = np.array([9, 197, 139])
#     upper_red = np.array([178, 255, 192])

#     # تعريف نطاق اللون الأخضر
#     lower_green = np.array([62, 101, 87])
#     upper_green = np.array([100, 253, 227])

#     # حساب مساحة اللون الأحمر والأخضر
#     red_area = calculate_color_area(lower_red, upper_red)
#     green_area = calculate_color_area(lower_green, upper_green)

#     if red_area > green_area:
#         print("مساحة اللون الأحمر أكبر من الأخضر.")
#         print("مساحة اللون الأحمر:", red_area, "بكسل")
#     elif green_area > red_area:
#         print("مساحة اللون الأخضر أكبر من الأحمر.")
#         print("مساحة اللون الأخضر:", green_area, "بكسل")
#     else:
#         print("مساحة اللون الأحمر والأخضر متساوية.")
