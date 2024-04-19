#include "software_timer.h"

int timer1_counter = 0;
int timer1_flag = 0;


int timer2_counter = 0;
int timer2_flag = 0;

void set_timer_to_publish_sensor_data(int duration){
	timer1_counter = duration * TICK_DURATION;
	timer1_flag = 0;
}


void set_timer_to_get_time(int duration){
	timer2_counter = duration * TICK_DURATION;
	timer2_flag = 0;
}

void timerRun(){
	if(timer1_counter > 0){
		timer1_counter--;
		if(timer1_counter <= 0){
			timer1_flag = 1;
		}
	}

	if(timer2_counter > 0){
		timer2_counter--;
		if(timer2_counter <= 0){
			timer2_flag = 1;
		}
	}
}