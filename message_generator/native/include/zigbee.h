#ifndef _ZIGBEE_H_
#define _ZIGBEE_H_
#pragma once

// user includes
#include <config.h>
#include <datalink.h>

namespace comnet {
   
class zigbee : public datalink {
public:
   zigbee(uint16_t port);
   zigbee(uint16_t port, char addr[16]);

   ~zigbee(void);
    
};
} // comnet namespace 

#endif /* _ZIGBEE_H_ */
