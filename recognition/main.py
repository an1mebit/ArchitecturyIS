import cv2

def captch_ex(frame):
    img = frame

    img2gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    ret, mask = cv2.threshold(img2gray, 180, 255, cv2.THRESH_BINARY)
    image_final = cv2.bitwise_and(img2gray, img2gray, mask=mask)
    ret, new_img = cv2.threshold(image_final, 180, 255, cv2.THRESH_BINARY)

    kernel = cv2.getStructuringElement(cv2.MORPH_CROSS, (3,3))
    dilated = cv2.dilate(new_img, kernel, iterations=9) 

    _, contours, hierarchy = cv2.findContours(dilated, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

    return contours

def show():
    cam = cv2.VideoCapture(0)
    cv2.namedWindow("test")
    
    while True:
        ret, frame = cam.read()
        if not ret:
            print("failed to grab frame")
            break
        cv2.imshow("test", frame)
        
        
        for contour in captch_ex(frame):
            [x, y, w, h] = cv2.boundingRect(contour)

            if w < 35 and h < 35:
                continue

            cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 255), 2)
        
        k = cv2.waitKey(1)
        if k%256 == 27:
            # ESC pressed
            print("Escape hit, closing...")
            break
    cam.release()
    cv2.destroyAllWindows()
    
if __name__ == "__main__":
    show()