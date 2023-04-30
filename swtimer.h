

#ifndef SWTIMER_H_
#define SWTIMER_H_

typedef enum {
	SWTMR_IDLE,
	SWTMR_RUN,
	SWTMR_DONE,
} swtimer_st_t;


typedef struct 
{
	uint32_t endTime;
	uint32_t currTime;
	swtimer_st_t state;
} swtimer_t;

void SwTimer_Init(void);
void SwTimer_Create(swtimer_t **pDevTimer, const swtimer_st_t state, const uint32_t SetTime);

extern swtimer_t SwTimers[];

#endif /* SWTIMER_H_ */