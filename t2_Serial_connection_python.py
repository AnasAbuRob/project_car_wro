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

        mask_green = cv2.inRange(hsv, lower_green, upper_green)
        _, mask2 = cv2.threshold(mask_green, 254, 255, cv2.THRESH_BINARY)
        cnts1, _ = cv2.findContours(mask2, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

        max_red_area = 0
        max_green_area = 0
        max_red_contour = None
        max_green_contour = None

        for c in cnts:
            area = cv2.contourArea(c)
            if area > max_red_area and area > 1000:  # تجاهل المساحات الصغيرة
                max_red_area = area
                max_red_contour = c

        for c in cnts1:
            area = cv2.contourArea(c)
            if area > max_green_area and area > 1000:  # تجاهل المساحات الصغيرة
                max_green_area = area
                max_green_contour = c

        # رسم مستطيل حول اللون الذي يمتلك أكبر مساحة
        if max_red_area > max_green_area:
            x, y, w, h = cv2.boundingRect(max_red_contour)
            cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
            ser.write("red".encode('utf-8'))
        elif max_green_area > max_red_area:
            x, y, w, h = cv2.boundingRect(max_green_contour)
            cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
            ser.write("green".encode('utf-8'))

        cv2.imshow("FRAME", frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
        time.sleep(2)


    cap.release()
    cv2.destroyAllWindows()

except KeyboardInterrupt:
    print("Serial closed communication")
    ser.close()
