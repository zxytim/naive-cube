
#ifndef __LIBS_CUBE_TIME__
#define __LIBS_CUBE_TIME__

typedef long long Time_t;

#define TIME_UNIT_S				0x00
#define TIME_UNIT_MS			0x01
#define TIME_UNIT_US			0x02

// 
Time_t timeGetTime(int unit = TIME_UNIT_US);
void timeStart();
Time_t timeEnd(int unit = TIME_UNIT_US);

#endif // __LIBS_CUBE_TIME__

