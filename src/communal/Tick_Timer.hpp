#ifndef TICK_TIMER_HPP
#define TICK_TIMER_HPP

class Tick_Timer{
private:
	int current=0;
	int max=0;
	bool paused=false;
public:
	Tick_Timer(){}
	Tick_Timer(int max_p){max=max_p;current=max;}

	void create(int max_p){max=max_p;current=max_p;}

	void restart(){
		current=max;
		paused=false;
	}
	void pause(bool b_p){paused=b_p;}
	void set(int i_p){current=i_p;}
	void set_max(int i_p){max=i_p;}
	bool do_timer_once(){
		if(!paused){
			if(current==0){
				return true;
			}else{
				current--;
			}
		}
		return false;
	}
	bool do_timer_loop(){
		if(!paused){
			if(current==0){
				current=max;
				return true;
			}else{
				current--;
			}
		}
		return false;
	}
};

#endif