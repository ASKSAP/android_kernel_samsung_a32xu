#ifndef __UH_H__
#define __UH_H__

#ifndef __ASSEMBLY__

/* For uH Command */
#define	APP_INIT	0
#define	APP_SAMPLE	1
#define APP_RKP		2
#define APP_HDM		6

/*
 * #define UH_PREFIX  UL(0xc300c000)
 * #define UH_APPID(APP_ID)  ((UL(APP_ID) & UL(0xFF)) | UH_PREFIX)
 */
/* for test with H-Arx */
#define UH_PREFIX  UL(0x83000000)
#define UH_APPID(APP_ID)  (((UL(APP_ID) << 8) & UL(0xFF00)) | UH_PREFIX)

#define GZ_HVC_TEST    0x70
#define GZ_MM_MAP_TEST     0x71
#define GZ_MM_UNMAP_TEST     0x72
enum __UH_APP_ID {
	UH_APP_INIT     = UH_APPID(APP_INIT),
	UH_APP_SAMPLE   = UH_APPID(APP_SAMPLE),
	UH_APP_RKP      = UH_APPID(APP_RKP),
	UH_APP_HDM	= UH_APPID(APP_HDM)
};

struct uh_app_test_case {
	int (*fn)(void); //test case func
	char *describe;
};

#define UH_LOG_START	(0xD0100000)
#define UH_LOG_SIZE		(0x40000)

unsigned long _uh_call(u64 app_id, u64 command, u64 arg0, u64 arg1, u64 arg2, u64 arg3);
static inline void uh_call(u64 app_id, u64 command, u64 arg0, u64 arg1, u64 arg2, u64 arg3)
{
	_uh_call(app_id | command, arg0, arg1, arg2, arg3, 0);
}

#endif //__ASSEMBLY__
#endif //__UH_H__
