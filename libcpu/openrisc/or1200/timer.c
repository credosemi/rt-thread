#include "spr-defs.h"
#include "support.h"
#include "timer.h"
#include "board.h"

/*======================[ CPU Tick timer functions ]============================= */

/* Enable tick timer and interrupt generation */
/* Set restart mode */
void timer_init(void){		
	/* clear timer interrupt */
	mtspr(SPR_TTMR, mfspr(SPR_TTMR) & ~(SPR_TTMR_IP));
	
	/* set OR1200 to accept exceptions */
	mtspr(SPR_SR, mfspr(SPR_SR) | SPR_SR_TEE);
	
	/* set initial value, and restart mode */
	mtspr(SPR_TTMR, SPR_TTMR_IE | SPR_TTMR_RT | ((SYS_CLK/TICKS_PER_SECOND) & SPR_TTMR_TP));
	
};

/* Disable tick timer and interrupt generation */
void timer_disable(void){
	/* disable timer: clear it all! */
	mtspr(SPR_SR, mfspr(SPR_SR) & ~SPR_SR_TEE);
	mtspr(SPR_TTMR, 0);

};

/* disable timer interrupt */
void timer_disable_interrupt(void){
	mtspr(SPR_TTMR, mfspr(SPR_TTMR) & ~(SPR_TTMR_IE));
};

/* clear tick interrupt */
void timer_clear_interrupt(void){
	mtspr(SPR_TTMR, mfspr(SPR_TTMR) & ~(SPR_TTMR_IP));
};

