#ifndef __HSM_H__
#define __HSM_H__

#define HSM_MODE
#include "config.h"
#include "qpc.h"

enum BlinkyButtonSignals {
    INIT_SIG = Q_USER_SIG,
    TIMEOUT_SIG,
    BUTTON_PRESSED_SIG,
    BUTTON_RELEASED_SIG
};


typedef struct {
    /* Protected */
    QActive super;
    /* Public */
    uint32_t blink_time;
    QTimeEvt te;
}BlinkyButton;


extern QHsm * const BlinkyButtonHSM; /* Pointer to State Machine */

void BlinkyButton_ctor(void);

#endif  /* __HSM_H__ */


