#Libraries required for the execution of the program
import serial,time,pymysql

#Connection to database - Credential entry
miConexion = pymysql.connect(host='localhost',user="admin",passwd="admin", db="dbIrrigationPlant" )
cur = miConexion.cursor()

#Setting of the port where the Arduino Uno is connected
arduino=serial.Serial("/dev/ttyACM0",9600)

while True:
    time.sleep(0)
    #Data reading from serial monitor sent from arduino Uno
    data = arduino.readline()
    #Separation of data in a list
    dato = data.split()
    #We check the first element of the list to know to which database.
    #data must be sent
    if str(dato[0].decode("utf-8")) == "tblSensores":
        #Data type transformation
        humHig = float(dato[1].decode("utf-8"))
        humDht = float(dato[2].decode("utf-8"))
        tempDht = float(dato[3].decode("utf-8"))
        vol = float(dato[4].decode("utf-8"))
        light = int(dato[5].decode("utf-8"))
        #Creation of the SQL command for data entry into the given table
        query = "INSERT INTO tblSensores(SenseDate,humedadHigro,humedadDHT11,temperaturaDHT11,volWater,luzVal) VALUES (now(),%s,%s,%s,%s,%d)"%(humHig, humDht, tempDht, vol,light)
        print(query)
        cur.execute(query)
        miConexion.commit()
        
    elif str(dato[0].decode("utf-8")) =="tblAlarmaWater":
        msgSys = str(dato[1].decode("utf-8")).replace("_", " ")
        volW = float(dato[2].decode("utf-8"))
        #Creation of the SQL command for data entry into the given table
        query = "INSERT INTO tblAlarmaWater(dateAlert,mensajeSystem,volWater) VALUES (now(),'%s',%.2f)"%(msgSys, volW)
        print(query)
        cur.execute(query)
        miConexion.commit()
    
    elif str(dato[0].decode("utf-8")) =="tblBombaAguaData":
        #Data type transformation
        msgSys = str(dato[1].decode("utf-8"))
        msgSys = msgSys.replace("_", " ")
        tDHT = float(dato[2].decode("utf-8"))
        humH = float(dato[3].decode("utf-8"))
        volW = float(dato[4].decode("utf-8"))
        light = int(dato[5].decode("utf-8"))
        #Creation of the SQL command for data entry into the given table
        query = "INSERT INTO tblBombaAguaData(dateActivacion,msgActivacion,tempDHT11,humedadHigro,volWater,luzVal) VALUES (now(),'%s',%.2f,%.2f,%.2f,%d)"%(msgSys, tDHT, humH,volW,light)
        print(query)
        cur.execute(query)
        miConexion.commit()

#Closing of connections
miConexion.close()
arduino.close()
