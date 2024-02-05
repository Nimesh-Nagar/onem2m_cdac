#include <WiFi.h>
#include <HTTPClient.h>
#define ONBOARD_LED 2
//Debugging levels 0-3
#define DEBUG_PRINT 3
//DEBUG MACROS
#if DEBUG_PRINT == 0
#define DBG(...)
#define DBGln(...)
#define DBG_RES(...)
#define DBG_RESln(...)
#define DBG_ERR(...)
#define DBG_ERRln(...)

#elif DEBUG_PRINT == 1
#define DBG(...) Serial.print(__VA_ARGS__)
#define DBGln(...) Serial.println(__VA_ARGS__)
#define DBG_ERR(...)
#define DBG_ERRln(...)
#define DBG_RES(...)
#define DBG_RESln(...)

#elif DEBUG_PRINT == 2
#define DBG(...)  Serial.print(__VA_ARGS__)
#define DBGln(...)  Serial.println(__VA_ARGS__)
#define DBG_RES(...)  Serial.print(__VA_ARGS__)
#define DBG_RESln(...)  Serial.println(__VA_ARGS__)
#define DBG_ERR(...)
#define DBG_ERRln(...)

#elif DEBUG_PRINT == 3
#define DBG(...)  Serial.print(__VA_ARGS__)
#define DBGln(...)  Serial.println(__VA_ARGS__)
#define DBG_RES(...)  Serial.println(__VA_ARGS__)
#define DBG_RESln(...)  Serial.println(__VA_ARGS__)
#define DBG_ERR(...)  Serial.print(__VA_ARGS__)
#define DBG_ERRln(...)  Serial.println(__VA_ARGS__)
#endif

byte mac[6];
const char* ssid = "TLS-TEST"; //Enter your SSID
const char* password = "12345678"; //Enter your SSID Password

// String CSE_IP = "127.0.0.1"; //Enter your IP of server where CSE is running
String CSE_IP = "10.182.2.233"; //Enter your IP of server where CSE is running
String CSE_PORT = "8080"; //Enter your Port to which CSE is Listening

String SERVER_NAME = "server"; // Enter your CSE name
String MY_AE = "cdac_ae"; // Enter AE name to be created
String MY_Origin = "onem2m_esp32"; // Enter Originator name who creates AE
//This is your URL for CSE Server
String url = "http://" + CSE_IP + ":" + CSE_PORT + "/" + SERVER_NAME;
// String url = "http://" + CSE_IP + ":" + CSE_PORT + "/" ;


/*Function CreateAE to create Application Entity
 * @params
 * String httpUrl = url of cse eg: 192.168.0.1:8080/CSENAME
 * String Cae_Name = Originator name who creates AE
 * String AE_Name =  AE name to be created
 * String api = application identifier

 * @return
 * returns the Http response number
 */
int CreateAE(String httpUrl, String Cae_Name, String AE_Name, String api) {
  WiFiClient client;
  HTTPClient http;
  DBGln(httpUrl);
  http.begin(client, httpUrl);
  http.addHeader("X-M2M-ORIGIN", Cae_Name);
  http.addHeader("Content-Type", "application/json;ty=2");
  http.addHeader("Accept", "application/json");
  http.addHeader("X-M2M-RI", String(random()));
  http.addHeader("X-M2M-RVI", "3");
  String httpReqData = "{\"m2m:ae\": {\"rn\": \"" + AE_Name + "\", \"srv\":[\"2a\",\"3\",\"4\"], \"rr\": false, \"api\": \"N" + api + "\" }}";
  DBGln(httpReqData);
  int httpResponseCode = http.POST(httpReqData);
  if (httpResponseCode > 0) {
    DBG_ERR("HTTP response Code: ");
    DBG_ERRln(httpResponseCode);
    String payload = http.getString();
    DBG_RES("");
    DBG_RES(payload);
    http.end();
  }
  else {
    DBG_ERR("Error code: ");
    DBG_ERRln(httpResponseCode);
    DBG_ERRln(":-(");
  }
  return httpResponseCode;
}

/*Function CreateCNT to Create Container inside Application Entity
 * @params
 * String httpUrl = url of cse eg: 192.168.0.1:8080/CSENAME
 * String Cae_Name = Originator name who creates AE
 * String AE_Name =  AE name where Container has to be created
 * String cnt_Name = Container name to be created
 * int max_data = Max number if values to be stored
 * @return
 * returns the Http response number
 */
int CreateCNT(String httpUrl, String Cae_Name, String AE_name, String cnt_Name, int max_data) {
  WiFiClient client;
  HTTPClient http;
  httpUrl = httpUrl + "/" + AE_name ;
  DBGln(httpUrl);
  http.begin(client, httpUrl);
  http.addHeader("X-M2M-ORIGIN", Cae_Name);
  http.addHeader("Content-Type", "application/json;ty=3");
  http.addHeader("Accept", "application/json");
  http.addHeader("X-M2M-RI", String(random()));
  http.addHeader("X-M2M-RVI", "3");
  String httpReqData = "{\"m2m:cnt\": {\"rn\": \"" + cnt_Name + "\", \"mni\": " + max_data + " }}";
  DBGln(httpReqData);
  int httpResponseCode = http.POST(httpReqData);
  if (httpResponseCode > 0) {
    DBG_ERR("HTTP Response code: ");
    DBG_ERRln(httpResponseCode);
    String payload = http.getString();
    DBG_RESln("");
    DBG_RESln(payload);
    http.end();
  }
  else {
    DBG_ERR("Error code: ");
    DBG_ERRln(httpResponseCode);
    DBG_ERRln(":-(");
  }
  return httpResponseCode;
}

/*Function CreateCNT to Create Container inside Application Entity
 * @params
 * String httpUrl = url of cse eg: 192.168.0.1:8080/CSENAME
 * String Cae_Name = Originator name who creates AE
 * String AE_Name =  AE name in which conatiner is residing
 * String cnt_Name = Container in which Container Instance to be Created
 * String Data = Data/Content to be sent/Stored
 * @return
 * returns the Http response number
 */
int CreateCIN(String httpUrl, String Cae_Name, String AE_name, String CNT_Name, String Data)
{
  WiFiClient client;
  HTTPClient http;
  httpUrl = httpUrl + "/" + AE_name + "/" + CNT_Name;
  DBGln(httpUrl);
  http.begin(client, httpUrl);
  http.addHeader("X-M2M-ORIGIN", Cae_Name);
  http.addHeader("Content-Type", "application/json;ty=4");
  http.addHeader("Accept", "application/json");
  http.addHeader("X-M2M-RI", String(random()));
  http.addHeader("X-M2M-RVI", "3");
  //String httpReqData = "{\"m2m:cin\": {\"rn\": \"" + CIN_Name + "\", \"cnf\": \"application/json\" , \"con\": \" " + Data + " \" }}";
  String httpReqData = "{\"m2m:cin\": {\"cnf\": \"text/plains:0\" , \"con\": \"" + Data + "\" }}";
  DBGln(httpReqData);
  int httpResponseCode = http.POST(httpReqData);
  if (httpResponseCode > 0) {
    digitalWrite(ONBOARD_LED, HIGH);
    delay(100);
    digitalWrite(ONBOARD_LED, LOW);
    DBG_ERR("HTTP Response code: ");
    DBG_ERRln(httpResponseCode);
    String payload = http.getString();
    DBG_RESln("");
    DBG_RESln(payload);
    http.end();
  }
  else {
    DBG_ERR("Error code: ");
    DBG_ERRln(httpResponseCode);
    DBG_ERRln(":-(");
  }
  return httpResponseCode;
}

/*Function CreateCNT to Create Container inside Application Entity
 * @params
 * String httpUrl = url of cse eg: 192.168.0.1:8080/CSENAME
 * String Cae_Name = Originator name who creates AE
 * String AE_Name =  AE name to be Deleted
 * @return
 * returns the Http response number
 */
int DeleteAE(String httpUrl, String Cae_Name, String AE_name)
{
  WiFiClient client;
  HTTPClient http;
  httpUrl = httpUrl + "/" + AE_name;
  DBGln(httpUrl);
  http.begin(client, httpUrl);
  http.addHeader("X-M2M-ORIGIN", Cae_Name);
  http.addHeader("Content-Type", "application/json;ty=2");
  http.addHeader("Accept", "application/json");
  http.addHeader("X-M2M-RI", String(random()));
  http.addHeader("X-M2M-RVI", "3");
  //String httpReqData = "{\"m2m:cin\": {\"cnf\": \"text/plains:0\" , \"con\": \"" + Data + "\" }}";
  //DBGln(httpReqData);
  //int httpResponseCode = http.DELETE();
  int httpResponseCode = http.sendRequest("DELETE");
  if (httpResponseCode > 0) {
    digitalWrite(ONBOARD_LED, HIGH);
    delay(100);
    digitalWrite(ONBOARD_LED, LOW);
    DBG_ERR("HTTP Response code: ");
    DBG_ERRln(httpResponseCode);
    String payload = http.getString();
    DBG_RESln("");
    DBG_RESln(payload);
    http.end();
    DBG("AE :");
    DBG(MY_AE);
    DBGln(" Deleted");
  }
  else {
    DBG_ERR("Error code: ");
    DBG_ERRln(httpResponseCode);
    DBG_ERRln(":-(");
  }
  return httpResponseCode;
}

void Connect_to_CSE() {
part1:
  int resp = CreateAE(url, MY_Origin, MY_AE , "test.comapny.org");
  if (resp == -1)
  {
    DBGln("unable to connect to CSE") ;
    delay(2000);
    goto part1;

  }
  else if (resp == 403)
  {
    DBGln("Originator already exists") ;
    DBG("Deleting the AE named :") ;
    DBG(MY_AE) ;
    DBG(" & Originator named :") ;
    DBGln(MY_Origin) ;
    DeleteAE(url, MY_Origin, MY_AE);
    delay(1000);
    goto part1;
  }
  else if (resp == 201 || resp == 409 )
  {
    DBGln("AE created") ;
part2:
    int resp1 = CreateCNT(url, MY_Origin, MY_AE, "temp", 5);
    if (resp1 == 404) {
      DBGln("Parent resource not found") ;
      delay(2000);
      goto part1;
    }
    else if (resp1 == 201 || resp1 == 409 ) {
      DBGln("Container created") ;
    }
    else {
      DBGln(resp1) ;
      DBGln("Container creation Error") ;
      delay(2000);
      goto part2;
    }
  }
  else {
    DBGln("Container creation Error") ;
    delay(2000);
    goto part1;
  }
}
/*Runs At the initilization time*/
void setup() {
  Serial.begin(115200);
  pinMode(ONBOARD_LED, OUTPUT);
  digitalWrite(ONBOARD_LED, LOW);
  WiFi.begin(ssid, password);
  DBG("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    DBG(".");
  }
  DBGln("");
  DBG("OK! IP=");
  DBGln(WiFi.localIP());
  WiFi.macAddress(mac);
  DBG("MAC: ");
  DBG(mac[5], HEX);
  DBG(":");
  DBG(mac[4], HEX);
  DBG(":");
  DBG(mac[3], HEX);
  DBG(":");
  DBG(mac[2], HEX);
  DBG(":");
  DBG(mac[1], HEX);
  DBG(":");
  DBGln(mac[0], HEX);
  if (WiFi.status() == WL_CONNECTED) {

    DBGln("Fetching " + url + "... ");
    Connect_to_CSE();
  }
  else {
    DBGln("Wifi Disconnected");
  }
}
/*Main loop which runs forever*/
void loop() {
  push();
  delay(5000);
  
}

//Function to push data into Container instace
void push() {
  int sensorValue = random(350);
  String Cin_name = "Data_" + String(random(random(), random()));
  DBG("sensorValue: ");
  DBGln(sensorValue);
  int resp2 = CreateCIN(url, MY_Origin , MY_AE, "temp", String(sensorValue));
  if (resp2 != 201)
  {
    DBGln("container is unavailable");
    Connect_to_CSE();
  }
}
