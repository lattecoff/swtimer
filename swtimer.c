/**
 *@file sw_timer.c
 *@brief Управление программными таймерами.
 *@author lattecoff.
 */

#include "stddef.h"
#include "stdbool.h"
#include "sw_timer.h"
 
#define SW_TIMERS_AMOUNTS	40

swtmr_t *pSwTimers[SW_TIMERS_AMOUNTS] = {NULL};

/**
 * @param[in] *pTIMER - указатель на требуемый программный таймер.
 * @param[in] MODE - режим.
 * @param[in] SET_TIME - устанавливаемое время, через которое сработает таймер.
 * @note SET_TIME = 0 устанавливает таймер в максимальное значение.
 */	
void SwTimer_Create(swtmr_t *const pTIMER, const swtmr_md_t MODE, const uint32_t SET_TIME)
{
	volatile uint8_t id = 0;
	volatile bool isErr = false;
	
	
	while ((pSwTimers[id] != NULL) && (pSwTimers[id] != pTIMER))
	{
		if(id < SW_TIMERS_AMOUNTS)
		{
			id++;
		}
		else
		{
			isErr = true;
			break;
		}
	}
	
	if (!isErr)
	{
		pSwTimers[id] = pTIMER;
		pTIMER->endTime = SET_TIME != 0UL ? SET_TIME : (0xFFFFFFFFUL -1);
		pTIMER->currTime = 0;
		pTIMER->isTimer = MODE;
	}
	else
	{
		/* do not created swtimer. */
	}
}

/**
 * @param[in] *pTimer - указатель на требуемый программный таймер.
 */
void SwTimer_Delete(swtmr_t *pTimer)
{
	volatile uint8_t id = 0;
	volatile bool isErr = false;
	
	
	while (pSwTimers[id] != pTimer)
	{
		if(id < SW_TIMERS_AMOUNTS)
		{
			id++;
		}
		else
		{
			isErr = true;
			break;
		}
	}

	if (!isErr)
	{
		pSwTimers[id]->isTimer = SWTMR_IDLE;
		pSwTimers[id]->endTime = 0;
		pSwTimers[id]->currTime = 0;
		pSwTimers[id] = NULL;
	}
	else
	{
		/* do not deleted swtimer. */
	}
}

/**
 * @param[in] *pTIMER - указатель на требуемый программный таймер.
 * @param[in] MODE - режим.
 * @param[in] SET_TIME - устанавливаемое время, через которое сработает таймер.
 * @note SET_TIME = 0 устанавливает таймер в максимальное значение.
 */
void SwTimer_Set(swtmr_t *const pTIMER, const swtmr_md_t MODE, const uint32_t SET_TIME)
{
	volatile uint8_t id = 0;
	volatile bool isErr = false;
	
	while (pSwTimers[id] != pTIMER)
	{
		if(id < SW_TIMERS_AMOUNTS)
		{
			id++;
		}
		else
		{
			isErr = true;
			break;
		}
	}
	
	if (!isErr)
	{
		pTIMER->endTime = SET_TIME != 0UL ? SET_TIME : (0xFFFFFFFFUL -1);
		pTIMER->currTime = 0;
		pTIMER->isTimer = MODE;
	}
	else
	{
		/* do not set swtimer. */
	}
}

/**
 * @param[in] *pTIMER - указатель на требуемый программный таймер.
 * @retval SWTMR_IDLE.
 * @retval SWTMR_RUN.
 * @retval SWTMR_DONE.
 */
swtmr_md_t SwTimer_Get_Status(swtmr_t * const pTIMER)
{
	return pTIMER->isTimer;
}

/**
 * @param[in] *pTIMER - указатель на требуемый программный таймер.
 * @return Текущее значение таймера.
 */
uint32_t SwTimer_Get_Time(swtmr_t * const pTIMER)
{
	return pTIMER->currTime;
}

/**
 * @param[in] *pTIMER - указатель на требуемый программный таймер.
 * @return Остаток времени.
 */
uint32_t SwTimer_Get_Rest_Time(swtmr_t *const pTIMER)
{
	return pTIMER->endTime - pTIMER->currTime;
}

/**

 */
inline void SwTimer_Scan(void)
{
	static uint8_t numCalls = 0;
	volatile uint8_t id = 0;


	if ((++numCalls) >= 100)
	{
		numCalls = 0;

		while (id < SW_TIMERS_AMOUNTS)
		{
			if (pSwTimers[id] != NULL)
			{
				if (pSwTimers[id]->isTimer == SWTMR_RUN)
				{
					#if (REF_CONF_RELEASE)
					(pSwTimers[id]->currTime)++;
					
					if ((pSwTimers[id]->currTime) >= (pSwTimers[id]->endTime))
					{
						pSwTimers[id]->isTimer = SWTMR_DONE;
					}
				}
			}

			id++;
		}
	}
}

/* end of file. */
