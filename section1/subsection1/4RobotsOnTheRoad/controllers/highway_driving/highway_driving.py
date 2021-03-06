"""Sample Webots controller for highway driving benchmark."""

from vehicle import Driver

# name of the available distance sensors
sensorsNames = [
    'front',
    'front right 0',
    'front right 1',
    'front right 2',
    'front left 0',
    'front left 1',
    'front left 2',
    'rear',
    'rear left',
    'rear right',
    'right',
    'left']
sensors = {}

maxSpeed = 100
driver = Driver()
driver.setSteeringAngle(0.0)  # go straight



# get and enable the distance sensors
for name in sensorsNames:
    sensors[name] = driver.getDistanceSensor('distance sensor ' + name)
    sensors[name].enable(10)

# get and enable the GPS
gps = driver.getGPS('gps')
gps.enable(10)

# get the camera
camera = driver.getCamera('camera')
# uncomment those lines to enable the camera
camera.enable(50)
camera.recognitionEnable(50)
dest =0
prevpos = -2
counter=0
rightb=5.8
leftb =2
average = 0
dest = 2
changelane=0
minx=1000
miny=1000
nextcar = 0
desty = 800
lim = 7250
lim2 = 7550
lim3 = 7890
lim4 = 7980
lim5 = 8161
lim6 = 8350
lim7 = 8518
lim8 = 8800
while driver.step() != -1:
    # adjust the speed according to the value returned by the front distance sensor
    print(counter)
    x=gps.getValues()
    counter= counter + 1
    if((counter > 7045)):#and(counter<8200)):
        
        frontDistance = sensors['front'].getValue() 
        frontRange = sensors['front'].getMaxValue()
        speed = maxSpeed * frontDistance / frontRange
        driver.setCruisingSpeed(speed)
        speedDiff = driver.getCurrentSpeed() - speed
        maxSpeed= 200
        pos = x[0]
        if(counter < lim):
            driver.setSteeringAngle(  -(1.2)*0.01) 
            #maxSpeed= 100
        if(counter >= lim):
            
            driver.setSteeringAngle(  (-0.9)*0.01) 
            maxSpeed= 120
            #maxSpeed= 50
            #if(counter > 7990):
            #    driver.setSteeringAngle(  (-1)*0.01)   
            #    maxspeed = 120
        if(counter >= lim2):          
            driver.setSteeringAngle(  (-1.4)*0.01) 
            maxSpeed= 100
            #maxSpeed= 50
            
        if(counter >= lim3):   
            maxSpeed= 80       
            driver.setSteeringAngle(  (-3)*0.01) 
        prevpos = pos
        if(counter >= lim4):
           driver.setSteeringAngle(  (2.6)*0.01) 
        if(counter >= lim5):
           maxSpeed= 100
           driver.setSteeringAngle(  (-0.8)*0.01) 
        if(counter >= lim6):
           maxSpeed= 90
           driver.setSteeringAngle(  (-0.89)*0.01)
          
        if(counter >= lim7):
           maxSpeed= 90
           driver.setSteeringAngle(  (3.35)*0.01)
        if(counter >= lim8):
           maxSpeed= 100
           driver.setSteeringAngle(  (-1.8)*0.01)
           
        if ((speedDiff > 0)):
            driver.setBrakeIntensity(0.5)
        else:
            driver.setBrakeIntensity(0)
        
    elif((counter>6700)):
        
        if(counter > 8200):
            maxSpeed = 50
        
        if(counter == 4800):
            maxSpeed= 200
        frontDistance = min(sensors['front'].getValue() ,sensors['front left 0'].getValue() , sensors['front right 0'].getValue() )
        frontRange = sensors['front'].getMaxValue()
        speed = maxSpeed * frontDistance / frontRange
        driver.setCruisingSpeed(speed)
        # brake if we need to reduce the speed
        speedDiff = driver.getCurrentSpeed() - speed
        
        maxSpeed = 100
        pos = -x[0] 
        objects=camera.getRecognitionObjects()
        if(nextcar == 0):
            #print("Normal Mode Following")
            for obj in objects:
                if(obj.get_id()>2000):
                    obj_pos=obj.get_position()
                    dest = obj_pos[0] 
                    if((abs(dest)<0.5)):
                        break
                      
            driver.setSteeringAngle(1*(prevpos - pos)*0.02 + (dest)*0.02)
        else:
            for obj in objects:
                if(obj.get_id()==id):
                    #print(obj.get_id())
                    obj_pos=obj.get_position()
                    dest = obj_pos[0] 
                    desty =obj_pos[2]  
                    break
            driver.setSteeringAngle(10*(prevpos - pos)*0.04 + (dest/10)*0.04)    
            #print(dest)          
        if ((speedDiff > 0)):
            driver.setBrakeIntensity(1)
        if ((speedDiff > 0)and(nextcar == 0)):
            driver.setBrakeIntensity(1) 
            if((abs(dest)<0.1)):
                if (sensors['left'].getValue()>3)and(sensors['front left 2'].getValue()>8):
                    for obj in objects:
                        if(obj.get_id()>2000):
                            obj_pos=obj.get_position()
                            destx = obj_pos[0]
                            if destx>0:
                                continue 
                            desty = abs(obj_pos[2])
                            if((desty < miny)and(abs(destx) > 0.5)and(abs(destx) < 9)):
                                miny = desty
                                dest = destx
                                nextcar = -1
                                id=obj.get_id()
                                #print("New car found:at x_axis: %f, y_axis: %f",destx,desty)
                elif((sensors['right'].getValue()>3)and(sensors['front right 2'].getValue()>8)and(not(sensors['right'].getValue()<7))): #you can turn right
                    for obj in objects:
                        if(obj.get_id()>2000):
                            obj_pos=obj.get_position()
                            destx = obj_pos[0]
                            if destx<0:
                                continue 
                            desty = abs(obj_pos[2])
                            if((desty < miny)and(abs(destx) > 0.5)and(abs(destx) < 9)):
                                miny = desty
                                dest = destx 
                                nextcar = 1 
                                id=obj.get_id()
                                #print(id) 
                                #print("New car found:at x_axis: %f, y_axis: %f",destx,desty)     
        else:
            driver.setBrakeIntensity(0)     
        if(abs(desty) < 13):
            nextcar = 0
            miny = 1000
        #prevpos = dest
        prevpos = -x[0]    
    else:
        frontDistance = sensors['front'].getValue() 
        frontRange = sensors['front'].getMaxValue()
        speed = maxSpeed * frontDistance / frontRange
        driver.setCruisingSpeed(speed)
        speedDiff = driver.getCurrentSpeed() - speed
        if(counter > 6040): 
            dest = 1
        if(dest == 2):#1.3
            #if(x[0]<1.3): #then turn left
            driver.setSteeringAngle(60*(x[0] - prevpos)*0.05 + (x[0]-1.3)*0.04) #TUNNING!!
            #if(x[0]>1.3): #then turn right
            #    driver.setSteeringAngle(1*0.1)
    
            #continue
        if(dest == 1):# 5.2
           #if(x[0]<1.3): #then turn left
           driver.setSteeringAngle(60*(x[0] - prevpos)*0.05 + (x[0]-5.2)*0.04)
           #if(x[0]>1.3): #then turn right
           #    driver.setSteeringAngle(1*0.1)
     
           #continue   
        if(dest == 3):# -2
           #if(x[0]<1.3): #then turn left
           driver.setSteeringAngle(60*(x[0] - prevpos)*0.05 + (x[0]+2)*0.04)
           #if(x[0]>1.3): #then turn right
           #    driver.setSteeringAngle(1*0.1)
           prevpos = x[0]
           #continue    
        prevpos = x[0] 
        counter=counter +1
        if ((speedDiff > 0)):
            #print(counter)
            if((sensors['right'].getValue()>3)and(sensors['front right 2'].getValue()>8)and(not(sensors['right'].getValue()<7))): #you can turn right
                 #print("trying right")
                 if((x[0]<5.25)and(x[0]>5.15)): #means you are left, go middle
                     dest = 2 #middle
                 if((x[0]<1.5)and(x[0]>1)):  #1.3, you are middle,go right
                     dest = 3 #right
            elif((sensors['left'].getValue()>3)and(sensors['front left 2'].getValue()>8)and(sensors['front left 1'].getValue()>14)): #You can steer left  
                #driver.setSteeringAngle(-speedDiff*0.1)
                #print("trying left")
                if((x[0]<-1.5)and(x[0]>-2.5)): #-2, you are in the right row, go left
                    dest = 2 #middle
                if((x[0]<1.5)and(x[0]>1)):  #1.3, you are middle,go left
                    dest = 1 #left
            else:    
                driver.setBrakeIntensity(1)
        else:
            driver.setBrakeIntensity(0)
            maxSpeed = 120    