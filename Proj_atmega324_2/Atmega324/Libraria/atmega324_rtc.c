#include "rtc.h"

static _RTC_Module iface;

_RTC_Module* RTC_enable(void) {
	iface.RTICR = (_RTICR_TypeDef*) 0x130;  // Example address, verify from datasheet
	iface.RTCCR = (_RTCCR_TypeDef*) 0x131;
	iface.RTCLR = (_RTCLR_TypeDef*) 0x132;
	iface.RTCCR1 = (_RTCCR1_TypeDef*) 0x133;

	return &iface;
}
