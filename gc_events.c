#include <stdlib.h>
#include "definitions.h"                                                        // global defines
#include "gc_events.h"
//#include "Transceiver_events.h"
#include "cpu_endian_defs.h"
#include <stdint.h>

/* clips from my general library used here */
bool Quaternion_from_euler(float64_t roll, float64_t pitch, float64_t yaw, dquat *q);

/*-----------------------------------------------------------------------------
 *  Quaternion_from_euler: create a quaternion from Euler angles 
 *
 *  Parameters: float64_t roll, float64_t pitch, float64_t yaw, dquat *q
 *
 *  Return: bool
 *----------------------------------------------------------------------------*/
bool Quaternion_from_euler(float64_t roll, float64_t pitch, float64_t yaw, dquat *q)
{
    const float64_t cr2 = cos(roll*0.5f);
    const float64_t cp2 = cos(pitch*0.5f);
    const float64_t cy2 = cos(yaw*0.5f);
    const float64_t sr2 = sin(roll*0.5f);
    const float64_t sp2 = sin(pitch*0.5f);
    const float64_t sy2 = sin(yaw*0.5f);
    if (q==NULL) return false;
    q->x = cr2*cp2*cy2 + sr2*sp2*sy2;
    q->y = sr2*cp2*cy2 - cr2*sp2*sy2;
    q->z = cr2*sp2*cy2 + sr2*cp2*sy2;
    q->w = cr2*cp2*sy2 - sr2*sp2*cy2;
    return true;
}
