#include "hsm/hsm.h"
#include "hsm/periph_util.h"


enum { INITIAL_BLINK_TIME = (OS_TICKS_PER_SEC / 4) };
static char_t const Q_this_module_[] = "QACTIVE_HSM_TEST";

static QState BlinkyButton_INITIAL(BlinkyButton * const me, void const * const par) ;
static QState BlinkyButton_DEFAULT(BlinkyButton * const me,  QEvt const * const e);
static QState BlinkyButton_ON(BlinkyButton * const me,  QEvt const * const e); 
static QState BlinkyButton_OFF(BlinkyButton * const me,  QEvt const * const e) ;

BlinkyButton l_blinkyButton;

QActive * const BlinkyButtonAO = &(l_blinkyButton.super);

void BlinkyButton_ctor(void)
{
    BlinkyButton *me = &(l_blinkyButton);
    me->blink_time = INITIAL_BLINK_TIME;
    QActive_ctor(&me->super,Q_ACTION_CAST(&BlinkyButton_INITIAL));
    QTimeEvt_ctorX(&me->te,&me->super,TIMEOUT_SIG,0);
    
}

/*  Protected State Transition Functions */
static QState BlinkyButton_INITIAL(BlinkyButton * const me, void const * const par) 
{
    (void)par;
   /*   Transition to initial state of LED1 OFF */

    return Q_TRAN(&BlinkyButton_DEFAULT);
}

static QState BlinkyButton_DEFAULT(BlinkyButton * const me,  QEvt const * const e)
{
    QState status_=0;
    switch(e->sig)
    {
        case INIT_SIG:
            QTimeEvt_armX(&me->te,me->blink_time,0);
            status_ = Q_TRAN(&BlinkyButton_OFF);
            break;
        case BUTTON_PRESSED_SIG:
            /* Turn LED2 ON  & reduce blinking time by factor of 2*/
            if(me->blink_time == 0)
            {
                me->blink_time = INITIAL_BLINK_TIME;
                QTimeEvt_armX(&me->te,me->blink_time,0);
            }
            else
            {
                me->blink_time >>= 2;
                QTimeEvt_rearm(&me->te,me->blink_time);
            }
            LED2_On();
            status_ = Q_HANDLED();
            break;
        case BUTTON_RELEASED_SIG:
            /* Turn LED2 OFF */
            LED2_Off();
            status_ = Q_HANDLED();
            break;
        
    }
    return status_;
} 

static QState BlinkyButton_ON(BlinkyButton * const me,  QEvt const * const e) 
{
    QState status_=0;
    switch(e->sig)
    {       
        case TIMEOUT_SIG:
            /* Transition to OFF State of LED1 */
            LED1_Off();
            /* Arm the timer again to stay OFF */
            QTimeEvt_armX(&me->te,me->blink_time,0);
            status_ = Q_TRAN(&BlinkyButton_OFF);
            break;
        default:
            status_ = Q_SUPER(&BlinkyButton_DEFAULT);
            break;
        
    }
    return status_;
}

static QState BlinkyButton_OFF(BlinkyButton * const me,  QEvt const * const e) 
{
    QState status_=0;
    switch(e->sig)
    {
        case TIMEOUT_SIG:
            /* Transition to ON State of LED1*/
            LED1_On();
            /* Arm the timer again to stay ON */
            QTimeEvt_armX(&me->te,me->blink_time,0);
            status_ = Q_TRAN(&BlinkyButton_ON);
            break;
        default:
            status_ = Q_SUPER(&BlinkyButton_DEFAULT);
            break;
        
    }
    return status_;
}

OS_STK stack_blinkyButton[100]; /* task stack */
static QEvt const *blinkyButton_queue[10];

void def_aoModelTest(); 

void def_aoModelTest()
{
    BlinkyButton_ctor();
    QF_init();
    BoardUtil_Init();


    QActive_setAttr(BlinkyButtonAO, OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR, 0);
    QACTIVE_START(BlinkyButtonAO,
                      1U,                /* QP priority */
                      blinkyButton_queue,      /* storage for the AO's queue */
                      Q_DIM(blinkyButton_queue), /* queue's length [entries] */
                      stack_blinkyButton,           /* stack storage */
                      sizeof(stack_blinkyButton),   /* sack size [bytes] */
                      (QEvt const *)0);      /* initialization event */

    QF_run();    /* Forever Loop */
}

