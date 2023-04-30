

#include "string.h"

#include "swtimer.h"


#define SWTMR_AMOUNT	5


swtimer_t SwTimers[SWTMR_AMOUNT];


void SwTimer_Init(void)
{
	memset(SwTimers, 0xFF, sizeof(SwTimers));
}

void SwTimer_Create(swtimer_t **pDevTimer, const swtimer_st_t state, const uint32_t SetTime)
{
	uint8_t id = 0;



	while (id < SWTMR_AMOUNT)
	{
		id++;
		if (id >= SWTMR_AMOUNT)
		{
			// overflow sw_timers.
			break;
		}
		else if (SwTimers[id].state == 0xFF)
		{
			// create success.
			if (SetTime)
				SwTimers[id].endTime = SetTime;
			else
				SwTimers[id].endTime = 0xFFFFFFFF -1;


			SwTimers[id].currTime = 0;
			SwTimers[id].state = state;

			*pDevTimer = (swtimer_t *)&SwTimers[id];
			break;
		}
	}
}