/****************************************************************************************************************************
  AsyncUDPSendReceive.ino

  AsyncUDP_ESP32_SC_Ethernet is a Async UDP library for the ESP32_SC_Ethernet (ESP32S2/S3/C3 + LwIP W5500 / W6100 / ENC28J60)

  Based on and modified from ESPAsyncUDP Library (https://github.com/me-no-dev/ESPAsyncUDP)
  Built by Khoi Hoang https://github.com/khoih-prog/AsyncUDP_ESP32_SC_Ethernet
  Licensed under GPLv3 license
 *****************************************************************************************************************************/

#if !( defined(ESP32) )
  #error This code is designed for (ESP32S2/S3/C3 + LwIP W5500, W6100 or ENC28J60) to run on ESP32 platform! Please check your Tools->Board setting.
#endif

#include <Arduino.h>

#define USING_W5100           false
#define USING_W6100           false
#define USING_ENC28J60        true

#if !USING_W5500 && !USING_W6100 && !USING_ENC28J60
  #undef USING_W5500
  #define USING_W5500           true
#endif

#define ASYNC_UDP_ESP32_SC_ETHERNET_DEBUG_PORT      Serial

// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _ASYNC_UDP_ESP32_SC_ETHERNET_LOGLEVEL_      2

//////////////////////////////////////////////////////////

#if USING_W5500

  #define ESP32_Ethernet_onEvent            ESP32_W5500_onEvent
  #define ESP32_Ethernet_waitForConnect     ESP32_W5500_waitForConnect

  // For ESP32_S3
  // Optional values to override default settings
  // Don't change unless you know what you're doing
  //#define ETH_SPI_HOST        SPI3_HOST
  //#define SPI_CLOCK_MHZ       25
  
  // Must connect INT to GPIOxx or not working
  //#define INT_GPIO            4
  
  //#define MISO_GPIO           13
  //#define MOSI_GPIO           11
  //#define SCK_GPIO            12
  //#define CS_GPIO             10

  // For ESP32_C3
  // Optional values to override default settings
  // Don't change unless you know what you're doing
  //#define ETH_SPI_HOST        SPI2_HOST
  //#define SPI_CLOCK_MHZ       25
  
  // Must connect INT to GPIOxx or not working
  //#define INT_GPIO            10
  
  //#define MISO_GPIO           5
  //#define MOSI_GPIO           6
  //#define SCK_GPIO            4
  //#define CS_GPIO             7

  //////////////////////////////////////////////////////////

#elif USING_W6100

  #define ESP32_Ethernet_onEvent            ESP32_W6100_onEvent
  #define ESP32_Ethernet_waitForConnect     ESP32_W6100_waitForConnect

  // For ESP32_S3
  // Optional values to override default settings
  // Don't change unless you know what you're doing
  //#define ETH_SPI_HOST        SPI3_HOST
  //#define SPI_CLOCK_MHZ       25
  
  // Must connect INT to GPIOxx or not working
  //#define INT_GPIO            4
  
  //#define MISO_GPIO           13
  //#define MOSI_GPIO           11
  //#define SCK_GPIO            12
  //#define CS_GPIO             10

  // For ESP32_C3
  // Optional values to override default settings
  // Don't change unless you know what you're doing
  //#define ETH_SPI_HOST        SPI2_HOST
  //#define SPI_CLOCK_MHZ       25
  
  // Must connect INT to GPIOxx or not working
  //#define INT_GPIO            10
  
  //#define MISO_GPIO           5
  //#define MOSI_GPIO           6
  //#define SCK_GPIO            4
  //#define CS_GPIO             7

  //////////////////////////////////////////////////////////
  
#else   // #if USING_W5500

  //////////////////////////////////////////////////////////

  // For ENC28J60

  #define ESP32_Ethernet_onEvent            ESP32_ENC_onEvent
  #define ESP32_Ethernet_waitForConnect     ESP32_ENC_waitForConnect

  // Optional values to override default settings
  // Don't change unless you know what you're doing
  //#define ETH_SPI_HOST        SPI2_HOST
  //#define SPI_CLOCK_MHZ       8
  
  // Must connect INT to GPIOxx or not working
  //#define INT_GPIO            4
  
  //#define MISO_GPIO           13
  //#define MOSI_GPIO           11
  //#define SCK_GPIO            12
  //#define CS_GPIO             10

  //////////////////////////////////////////////////////////

#endif    // #if USING_W5500

//////////////////////////////////////////////////////////

#include <AsyncUDP_ESP32_SC_Ethernet.h>

/////////////////////////////////////////////

// Enter a MAC address and IP address for your controller below.
#define NUMBER_OF_MAC      20

byte mac[][NUMBER_OF_MAC] =
{
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x02 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x03 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x04 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x05 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x06 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x07 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x08 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x09 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0A },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0B },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0C },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0D },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0E },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0F },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x10 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x11 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x12 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x13 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x14 },
};

// Select the IP address according to your local network
IPAddress myIP(192, 168, 2, 232);
IPAddress myGW(192, 168, 2, 1);
IPAddress mySN(255, 255, 255, 0);

// Google DNS Server IP
IPAddress myDNS(8, 8, 8, 8);

/////////////////////////////////////////////

#include <time.h>

// 0.ca.pool.ntp.org
IPAddress timeServerIP = IPAddress(208, 81, 1, 244);
// time.nist.gov
//IPAddress timeServerIP = IPAddress(132, 163, 96, 1);

#define NTP_REQUEST_PORT      123

char ReplyBuffer[] = "ACK";      // a string to send back

char timeServer[]         = "time.nist.gov";  // NTP server

const int NTP_PACKET_SIZE = 48;       // NTP timestamp is in the first 48 bytes of the message

byte packetBuffer[NTP_PACKET_SIZE];   // buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
AsyncUDP Udp;

void sendACKPacket(void)
{
  Serial.println("============= sendACKPacket =============");

  // Send unicast ACK to the same remoteIP and remotePort we received the packet
  // The AsyncUDP_STM32 library will take care of the correct IP and port based on pcb
  Udp.write((uint8_t *) ReplyBuffer, sizeof(ReplyBuffer));
}

// send an NTP request to the time server at the given address
void createNTPpacket(void)
{
  Serial.println("============= createNTPpacket =============");

  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)

  packetBuffer[0]   = 0b11100011;   // LI, Version, Mode
  packetBuffer[1]   = 0;     // Stratum, or type of clock
  packetBuffer[2]   = 6;     // Polling Interval
  packetBuffer[3]   = 0xEC;  // Peer Clock Precision

  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
}

void sendNTPPacket(void)
{
  createNTPpacket();
  //Send unicast
  Udp.write(packetBuffer, sizeof(packetBuffer));
}

void parsePacket(AsyncUDPPacket packet)
{
  struct tm  ts;
  char       buf[80];

  memcpy(packetBuffer, packet.data(), sizeof(packetBuffer));

  Serial.print("Received UDP Packet Type: ");
  Serial.println(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
  Serial.print("From: ");
  Serial.print(packet.remoteIP());
  Serial.print(":");
  Serial.print(packet.remotePort());
  Serial.print(", To: ");
  Serial.print(packet.localIP());
  Serial.print(":");
  Serial.print(packet.localPort());
  Serial.print(", Length: ");
  Serial.print(packet.length());
  Serial.println();

  unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
  unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);

  // combine the four bytes (two words) into a long integer
  // this is NTP time (seconds since Jan 1 1900):
  unsigned long secsSince1900 = highWord << 16 | lowWord;

  Serial.print(F("Seconds since Jan 1 1900 = "));
  Serial.println(secsSince1900);

  // now convert NTP time into )everyday time:
  Serial.print(F("Epoch/Unix time = "));

  // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
  const unsigned long seventyYears = 2208988800UL;

  // subtract seventy years:
  unsigned long epoch = secsSince1900 - seventyYears;
  time_t epoch_t = epoch;   //secsSince1900 - seventyYears;

  // print Unix time:
  Serial.println(epoch);

  // print the hour, minute and second:
  Serial.print(F("The UTC/GMT time is "));       // UTC is the time at Greenwich Meridian (GMT)

  ts = *localtime(&epoch_t);
  strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
  Serial.println(buf);

  // send a reply, to the IP address and port that sent us the packet we received
  sendACKPacket();
}

void initEthernet()
{
  UDP_LOGWARN(F("Default SPI pinout:"));
  UDP_LOGWARN1(F("SPI_HOST:"), ETH_SPI_HOST);
  UDP_LOGWARN1(F("MOSI:"), MOSI_GPIO);
  UDP_LOGWARN1(F("MISO:"), MISO_GPIO);
  UDP_LOGWARN1(F("SCK:"),  SCK_GPIO);
  UDP_LOGWARN1(F("CS:"),   CS_GPIO);
  UDP_LOGWARN1(F("INT:"),  INT_GPIO);
  UDP_LOGWARN1(F("SPI Clock (MHz):"), SPI_CLOCK_MHZ);
  UDP_LOGWARN(F("========================="));

  ///////////////////////////////////

  // To be called before ETH.begin()
  ESP32_Ethernet_onEvent();

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  //bool begin(int MISO_GPIO, int MOSI_GPIO, int SCLK_GPIO, int CS_GPIO, int INT_GPIO, int SPI_CLOCK_MHZ,
  //           int SPI_HOST, uint8_t *W6100_Mac = W6100_Default_Mac);
  ETH.begin( MISO_GPIO, MOSI_GPIO, SCK_GPIO, CS_GPIO, INT_GPIO, SPI_CLOCK_MHZ, ETH_SPI_HOST );
  //ETH.begin( MISO_GPIO, MOSI_GPIO, SCK_GPIO, CS_GPIO, INT_GPIO, SPI_CLOCK_MHZ, ETH_SPI_HOST, mac[millis() % NUMBER_OF_MAC] );

  // Static IP, leave without this line to get IP via DHCP
  //bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = 0, IPAddress dns2 = 0);
  //ETH.config(myIP, myGW, mySN, myDNS);

  ESP32_Ethernet_waitForConnect();

  ///////////////////////////////////
}

////////////////////////////////////

void setup()
{
  Serial.begin(115200);

  while (!Serial && (millis() < 5000));

  delay(500);

  Serial.print(F("\nStart AsyncUDPSendReceive on "));
  Serial.print(ARDUINO_BOARD);
  Serial.print(F(" with "));
  Serial.println(SHIELD_TYPE);

#if USING_W5500
  Serial.println(WEBSERVER_ESP32_SC_W5500_VERSION);
#elif USING_W6100
  Serial.println(WEBSERVER_ESP32_SC_W6100_VERSION);  
#else
  Serial.println(WEBSERVER_ESP32_SC_ENC_VERSION);
#endif
  
  Serial.println(ASYNC_UDP_ESP32_SC_ETHERNET_VERSION);

  Serial.setDebugOutput(true);

  ///////////////////////////////////

  initEthernet();

  ///////////////////////////////////

  // Client address
  Serial.print("AsyncUDPSendReceive started @ IP address: ");
  Serial.println(ETH.localIP());

  Serial.println(F("\nStarting connection to server..."));

  //NTP requests are to port NTP_REQUEST_PORT = 123
  if (Udp.connect(timeServerIP, NTP_REQUEST_PORT))
  {
    Serial.println("UDP connected");

    Udp.onPacket([](AsyncUDPPacket packet)
    {
      parsePacket(packet);
    });
  }
}

void loop()
{
  sendNTPPacket();

  // wait 60 seconds before asking for the time again
  delay(60000);
}
