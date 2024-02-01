//pin
#define servo 13
// #define oneWireBus 25
#define rPompaIn 32
#define rPompaOut 33
#define trig  18
#define echo  19
const int oneWireBus = 25;   

//Variable
long duration;
int distance;
int tinggi;
int nSuhuAir;
int nTinggiAir;
int notif;

//Blynk Firmware Config
#define BLYNK_TEMPLATE_ID "TMPL6GhEJZAnF"
#define BLYNK_TEMPLATE_NAME "GoldiTech"
#define BLYNK_AUTH_TOKEN "9sT1IBF4tVlNLQi0FaGCpZhX0sMQM8OM"
#define BLYNK_PRINT Serial

///Wifi ESP32 & NTP Config  
const char* ssid                  = "admin2";
const char* password              = "12345678";

const char* ntpServer             = "pool.ntp.org";
const long  gmtOffset_sec         = 6 * 3600;
const int   daylightOffset_sec    = 3600;

char auth[] = BLYNK_AUTH_TOKEN;