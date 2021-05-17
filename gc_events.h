/* general snippets used here */
#ifndef gc_events_H
#define gc_events_H
//    gc_events.h : General Event declarations
//
//
//    Version : @(#) 1.0
//    Copyright (C) 2020 A C P Avaiation Walkerburn Scotland
//
//

#ifdef __cplusplus
 extern "C" {
#endif

#include "Struts.h"
#include <stdint.h>
#include "definitions.h"

extern bool Quaternion_from_euler(float64_t roll, float64_t pitch, float64_t yaw, dquat *q);
   
#ifdef __cplusplus
}
#endif

#endif //Transceiver_events_H
