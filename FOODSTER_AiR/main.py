import cv2, time


def faceBox(faceNet,frame):
    frameHeight=frame.shape[0]
    frameWidth=frame.shape[1]
    blob=cv2.dnn.blobFromImage(frame, 1.0, (300,300), [104,117,123], swapRB=False)
    faceNet.setInput(blob)
    detection=faceNet.forward()
    bboxs=[]
    for i in range(detection.shape[2]):
        confidence=detection[0,0,i,2]
        if confidence>0.7:
            x1=int(detection[0,0,i,3]*frameWidth)
            y1=int(detection[0,0,i,4]*frameHeight)
            x2=int(detection[0,0,i,5]*frameWidth)
            y2=int(detection[0,0,i,6]*frameHeight)
            bboxs.append([x1,y1,x2,y2])
            cv2.rectangle(frame, (x1,y1),(x2,y2),(0,255,0), 1)
    return frame, bboxs


faceProto = "opencv_face_detector.pbtxt"
faceModel = "opencv_face_detector_uint8.pb"

ageProto = "age_deploy.prototxt"
ageModel = "age_net.caffemodel"

genderProto = "gender_deploy.prototxt"
genderModel = "gender_net.caffemodel"



faceNet=cv2.dnn.readNet(faceModel, faceProto)
ageNet=cv2.dnn.readNet(ageModel,ageProto)
genderNet=cv2.dnn.readNet(genderModel,genderProto)

MODEL_MEAN_VALUES = (78.4263377603, 87.7689143744, 114.895847746)
ageList = ['(0-2)', '(4-6)', '(8-12)', '(15-20)', '(25-32)', '(38-43)', '(48-53)', '(60-100)']
genderList = ['Male', 'Female']


video=cv2.VideoCapture(0)
img_counter = 10

padding=20

while True:
    ret,frame=video.read()
    frame = cv2.rotate(frame, cv2.ROTATE_180)  
    frame,bboxs=faceBox(faceNet,frame)
    for bbox in bboxs:
        # face=frame[bbox[1]:bbox[3], bbox[0]:bbox[2]]
        face = frame[max(0,bbox[1]-padding):min(bbox[3]+padding,frame.shape[0]-1),max(0,bbox[0]-padding):min(bbox[2]+padding, frame.shape[1]-1)]
        blob=cv2.dnn.blobFromImage(face, 1.0, (227,227), MODEL_MEAN_VALUES, swapRB=False)
        genderNet.setInput(blob)
        genderPred=genderNet.forward()
        gender=genderList[genderPred[0].argmax()]


        ageNet.setInput(blob)
        agePred=ageNet.forward()
        age=ageList[agePred[0].argmax()]
        

        label="{},{}".format(gender,age)
        #print (gender)
        #gender = "Male"
        gender1 = "Male"
        #accuracyM= 1
        if gender == gender1:
            print("Hello Handsome")
            import Sound3
            #for accuracyM in range (3)
            #accuracyM +=1 
        else:
            print("Hello Lady")
            import Sound4
        cv2.rectangle(frame,(bbox[0], bbox[1]-30), (bbox[2], bbox[1]), (0,255,0),-1) 
        cv2.putText(frame, label, (bbox[0], bbox[1]-10), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (255,255,255), 2,cv2.LINE_AA)
    cv2.imshow("Age-Gender",frame)
    import Sound2
    k=cv2.waitKey(1)
    #time.sleep(7000)
    #if k==ord('q'):
    if k%256 == 27:
        # ESC pressed
        print("Escape hit, closing...")
        break
    elif k%256 == 32:
        # SPACE pressed
        img_name = "/home/pi/Desktop/Cust_Pic/opencv_frame_{}.png".format(img_counter)
        cv2.imwrite(img_name, frame)
        print("opencv_frame_{}.png written!".format(img_counter))
        #print("{} written!".format(img_name))
        import pyrebase

        config = {
          "apiKey": "AIzaSyBz3V4VrzTI3xv9VnTPAYEYkjrkWT2pCVw",
          "authDomain": "old-customer.firebaseapp.com",
          "projectId": "old-customer",
          "storageBucket": "old-customer.appspot.com",
          "messagingSenderId": "334020035043",
          "appId": "1:334020035043:web:676c13baf55699672060d6",
          "measurementId": "G-8PGWSVQL5E",
          "databaseURL":"emptystring"
        }

        firebase = pyrebase.initialize_app(config)
        storage = firebase.storage()

        path_on_cloud = "People_Image/Customer{}".format(img_counter)
        path_local = "/home/pi/Desktop/Cust_Pic/opencv_frame_{}.png".format(img_counter)
        storage.child(path_on_cloud).put(path_local)

        
        img_counter += 1

video.release()
cv2.destroyAllWindows()
#print(img_counter)
latestNum = img_counter

print("Updated value: ", latestNum)
# Read in the file
with open('main.py', 'r') as file :
  filedata = file.read()

# Replace the target string
n = 'img_counter = '+ str(latestNum)
filedata = filedata.replace('img_counter = 10', n)

# Write the file out again
with open('main.py', 'w') as file:
  file.write(filedata)
#import b

#"opencv_frame_{}.png".format(img_counter)

#import CamTakePicUpload.py
import Sound5