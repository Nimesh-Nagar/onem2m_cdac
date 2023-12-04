import requests
import json
import random

# CSE Parameters
''' 
HOST = "127.0.0.1"
PORT = 8080
CSE_ID = "CSE_S_ID"
CSE_NAME = "server"
ADMIN_ID = "CAdmin"
'''
# ask user to enter CSE details to which it wants to communicateo
HOST = input("Enter host CSE ip address : ")
PORT = int(input("Enter host CSE port number : "))
CSE_NAME = input("Enter CSE Base Name : ")
CSE_ID = input("Enter unique CSE ID : ")
ADMIN_ID = input("Enter CSE Admin id : ")

AE_NAME = "Test_ae"
SENSOR_ID = "S_ID"

CNT_NAME = "TEST"


#------------------------------------------------ 1. GET Data from CSE Test  -------------------------------------------------------

def get_data_test():
    url = f"http://{HOST}:{PORT}/{CSE_NAME}"
    header = {
        "X-M2M-Origin": ADMIN_ID,
        "X-M2M-RI" : "123",
        "X-M2M-RVI" : "3",
        "Content-Type": "application/json"

    } 
    response = requests.get(url, headers=header)
    print("[STATUS CODE] ",response.status_code)
    # print("[RESPONSE] ",json.loads(response.content))
    status = response.status_code
    if status == 200:
        print("Connecting Device Test Pass ")
    else:
        print(f"Test Failed with code {status}")


#------------------------------------------------ 2. Create AE Test  ----------------------------------------------------------------

def create_ae_test():
    url = f"http://{HOST}:{PORT}/{CSE_NAME}"
    header = {
        "X-M2M-Origin": SENSOR_ID, 
        "X-M2M-RI" : "123",
        "X-M2M-RVI" : "3",
        "Content-Type": "application/json;ty=2"
    }

    payload =  {
        "m2m:ae": {
            "rn": "ROOM_02", #user input required
            "api": "N01.com.room.sensor01",
            "rr": True,
            "srv": ["2a","3","4"],
            "poa" : [f"http://{HOST}:{PORT}/ROOM_02"] #user input required
        }
    }
    response = requests.post(url, json=payload, headers=header)
    print("[STATUS CODE] ",response.status_code)
    status = response.status_code
    if status == 201:
        print("AE Creation Test Passed ")
    else: 
        print(f"Test Failed with code {status}")

#------------------------------------------------ 3. Container Creation under AE Test  -----------------------------------------------

def create_cnt_test():
    url = f"http://{HOST}:{PORT}/{CSE_NAME}/ROOM_02"
    header = {
        "X-M2M-Origin": SENSOR_ID,
        "X-M2M-RI" : "123",
        "X-M2M-RVI" : "3",
        "Content-Type": "application/json;ty=3"
    }
    payload = {
        "m2m:cnt": {
            "rn": f"{CNT_NAME}"       
        }
    }
    response = requests.post(url, json=payload, headers=header)
    print("[STATUS CODE] ",response.status_code)
    status = response.status_code
    if status == 201:
        print("Container Creation Test Passed ")
    else: 
        print(f"Test Failed with code {status}")

#------------------------------------------------ 4. Content Instance Test -----------------------------------------------------------
def content_inst_test():
    url = f"http://{HOST}:{PORT}/{CSE_NAME}/ROOM_02/TEMPERATURE"
    header = {
        "X-M2M-Origin": SENSOR_ID,
        "X-M2M-RI" : "123",
        "X-M2M-RVI" : "3",
        "Content-Type": "application/json;ty=4"
    }
    temp = round(random.uniform(20.00,35.00),2) # sensor values
    payload = {
        "m2m:cin": {
            "cnf" : "text/plain:0",
            "con" : f"{temp}"       
        }
    }
    response = requests.post(url, json=payload, headers=header)
    print("[STATUS CODE] ",response.status_code)
    status = response.status_code
    if status == 201:
        print("ContantInstance Creation Test Passed ")
    else: 
        print(f"Test Failed with code {status}")

######################################################################################################################################
    
while(True):
    while(True):
        print(" ")
        print("---------------------- ONEM2M TESTING ENVIORNMENT ----------------------")
        print("1. GET Data from CSE ")
        print("2. Create AE Test ")
        print("3. Create Container Test ")
        print("4. Create ContentInstance Test ")


        print("9. Exit ")
        
        ch = int(input("Choose any option : "))
        if ch == 1:
            get_data_test()
            break
        elif ch == 2:
            create_ae_test()
            break
        elif ch == 3:
            create_cnt_test()
            break
        elif ch == 4:
            content_inst_test()
            break

        elif ch == 9:
            break

        else:
            print("Choose appropriate Options ")



    """
    Abbrivations :
    RI  : Request Identifier
    RVI : REquest Version Indicatior

    rn  : Resource Name
    api : unique identifier for an Application Entity (AE).
    ty  : resource type


    """