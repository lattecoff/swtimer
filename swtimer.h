/**
 *@file sw_timer.h
 *@brief
 *@author lattecoff.
 */

#include "r_cg_macrodriver.h"

#ifndef SW_TIMER_H
#define SW_TIMER_H

#ifdef REF_CONF_RELEASE
#define _SEC	*1U
#define _MIN	*60U
#define _HOUR	*60UL *60UL

#else
#define _SEC	*1U
#define _MIN	*60U /** *10U */
#define _HOUR	*60UL *60UL /** *10UL *10UL */

#endif

#define SWTMR_MAX_TIME	(0xFFFFFFFEUL)	// 0xFFFFFFFF -1.
#define SWTMR_MIN_TIME	(0U)

typedef enum {
	SWTMR_IDLE,	///< таймер остановлен.
	SWTMR_RUN,	///< таймер запущен.
	SWTMR_DONE	///< таймер выполнен.
} swtmr_md_t;

typedef struct swtmr_t {
	uint32_t endTime;
	uint32_t currTime;
	swtmr_md_t isTimer;
} swtmr_t;

void SwTimer_Create(swtmr_t *const pTIMER, const swtmr_md_t MODE, const uint32_t SET_TIME);

void SwTimer_Delete(swtmr_t *pTimer);
void SwTimer_Set(swtmr_t *const pTIMER, const swtmr_md_t MODE, const uint32_t SET_TIME);
swtmr_md_t SwTimer_Get_Status(swtmr_t *const pTIMER);
uint32_t SwTimer_Get_Rest_Time(swtmr_t *const pTIMER);
uint32_t SwTimer_Get_Time(swtmr_t *const pTIMER);
void SwTimer_Scan(void);

#endif /* SW_TIMER_H */ 

/* end of file. */
