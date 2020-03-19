#include <ubinos.h>

#if (INCLUDE__APP__myrtc == 1)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>

#include <nrf.h>
#include <nrf_gpio.h>
#include <nrf_drv_rtc.h>
#include <nrf_drv_clock.h>
#include <boards.h>
#include <app_error.h>

static void myrtc_isr(void);
static void helloworld_mt_task1func(void *arg);
static void helloworld_mt_task2func(void *arg);

#define RTC NRF_RTC0
#define RTC_IRQ_NO RTC0_IRQn

int appmain(int argc, char *argv[]) {
	int r;
#if (UBINOS__UBIK__TICK_TYPE == UBINOS__UBIK__TICK_TYPE__RTC)
#else
	ret_code_t err_code;
#endif

	//
	printf("\n\n\r\n");
	printf("================================================================================\r\n");
	printf("myrtc (build time: %s %s)\r\n", __TIME__, __DATE__);
	printf("================================================================================\r\n");
	printf("\r\n");
#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
	r = heap_printheapinfo(NULL);
	if (0 == r) {
		printf("\r\n");
		printf("================================================================================\r\n");
		printf("\r\n");
	}
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */

	//
	bsp_board_init(BSP_INIT_LEDS);

	//
#if (UBINOS__UBIK__TICK_TYPE == UBINOS__UBIK__TICK_TYPE__RTC)
#else
	err_code = nrf_drv_clock_init();
	APP_ERROR_CHECK(err_code);

	nrf_drv_clock_lfclk_request(NULL);
#endif

	//
	nrf_rtc_prescaler_set(RTC, 4095);
	nrf_rtc_int_enable(RTC, RTC_INTENSET_TICK_Msk);
	nrf_rtc_task_trigger(RTC, NRF_RTC_TASK_CLEAR);
	nrf_rtc_task_trigger(RTC, NRF_RTC_TASK_START);

	intr_connectisr(RTC_IRQ_NO, myrtc_isr, intr_getlowestpriority(), 0);
	intr_enable(RTC_IRQ_NO);

	srand(time(NULL));

	r = task_create(NULL, helloworld_mt_task1func, NULL, task_getmiddlepriority(), 0, "task1");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	r = task_create(NULL, helloworld_mt_task2func, NULL, task_getmiddlepriority(), 0, "task2");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	ubik_comp_start();

	return 0;
}

static void myrtc_isr(void) {
	nrf_gpio_pin_toggle(BSP_LED_0);
	nrf_rtc_event_clear(RTC, NRF_RTC_EVENT_TICK);
}

static void helloworld_mt_task1func(void *arg) {
	unsigned int delayms;

	task_sleepms(1000);

	for (unsigned int i = 0;; i++) {
		delayms = (rand() % 10 + 1) * 200;
		printf("1: hello world ! (%u) (delay = %4d ms)\r\n", i, delayms);
		task_sleepms(delayms);
	}
}

static void helloworld_mt_task2func(void *arg) {
	unsigned int delayms;

	task_sleepms(1000);

	for (unsigned int i = 0;; i++) {
		delayms = (rand() % 10 + 1) * 200;
		printf("2: hello world ! (%u) (delay = %4d ms)\r\n", i, delayms);
		task_sleepms(delayms);
	}
}

#endif /* (INCLUDE__APP__myrtc == 1) */

