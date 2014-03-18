#ifndef FF_TEST_TERM_H_
#define FF_TEST_TERM_H_
#ifdef __cplusplus
 extern "C" {
#endif

#include <stm32f10x.h>

void ff_test_term_timerproc(void) __attribute__ ((section(".ramfunc")));
int ff_test_term(void);

#ifdef __cplusplus
 }
#endif
#endif

