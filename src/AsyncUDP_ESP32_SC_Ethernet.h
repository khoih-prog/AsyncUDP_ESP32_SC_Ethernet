/****************************************************************************************************************************
  AsyncUDP_ESP32_SC_Ethernet.h

  AsyncUDP_ESP32_SC_Ethernet is a Async UDP library for the ESP32_SC_Ethernet (ESP32S2/S3/C3 + LwIP W5500 / ENC28J60)

  Based on and modified from ESPAsyncUDP Library (https://github.com/me-no-dev/ESPAsyncUDP)
  Built by Khoi Hoang https://github.com/khoih-prog/AsyncUDP_ESP32_SC_Ethernet
  Licensed under GPLv3 license

  Version: 2.1.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  2.0.0   K Hoang      18/12/2022 Initial coding for ESP32_S3 using LwIP W5500 / ENC28J60. Bump up version to v2.0.0
  2.1.0   K Hoang      21/12/2022 Add support to ESP32_S2/C3 using LwIP W5500 / ENC28J60 Ethernet
 *****************************************************************************************************************************/

#pragma once

#ifndef ASYNC_UDP_ESP32_SC_ETHERNET_H
#define ASYNC_UDP_ESP32_SC_ETHERNET_H

////////////////////////////////////////////////////

#if defined(USING_W5500)
  #if (_ASYNC_UDP_ESP32_SC_ETHERNET_LOGLEVEL_ > 3)
    #warning USING_W5500
  #endif

  #include <WebServer_ESP32_SC_W5500.h>     // https://github.com/khoih-prog/WebServer_ESP32_SC_W5500
#elif defined(USING_ENC28J60)
  #if (_ASYNC_UDP_ESP32_SC_ETHERNET_LOGLEVEL_ > 3)
    #warning USING_ENC28J60
  #endif

  #include <WebServer_ESP32_SC_ENC.h>       // https://github.com/khoih-prog/WebServer_ESP32_SC_ENC
#else
  #if (_ASYNC_UDP_ESP32_SC_ETHERNET_LOGLEVEL_ > 3)
    #warning Default to USING_W5500
  #endif

  #include <WebServer_ESP32_SC_W5500.h>     // https://github.com/khoih-prog/WebServer_ESP32_SC_W5500
#endif

////////////////////////////////////////////////

#include "AsyncUDP_ESP32_SC_Ethernet.hpp"
#include "AsyncUDP_ESP32_SC_Ethernet_Impl.h"

////////////////////////////////////////////////

#endif    //ASYNC_UDP_ESP32_SC_ETHERNET_H
