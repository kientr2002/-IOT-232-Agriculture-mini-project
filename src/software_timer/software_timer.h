#ifndef _INCLUDE_SOFTWARE_TIMER_H_
#define _INCLUDE_SOFTWARE_TIMER_H_

#define TICK_DURATION 1000

extern int timer1_flag;
extern int timer2_flag;

void set_timer_to_publish_sensor_data(int duration);
void set_timer_to_get_time(int duration);
void timerRun();


#endif // !_INCLUDE_SOFTWARE_TIMER_H_