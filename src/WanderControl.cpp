#include "WanderControl.h"

using namespace std;
using namespace godot;


void WanderControl::_register_methods() {
	register_method("_init", &WanderControl::_init);
	register_method("_ready", &WanderControl::_ready);
	register_method("_on_Timer_timeout", &WanderControl::_on_Timer_timeout);
	register_method("update_target_position", &WanderControl::update_target_position);
	register_method("get_timer_left", &WanderControl::get_timer_left);
	register_method("start_wander_time", &WanderControl::start_wander_time);
	register_method("rand_range", &WanderControl::rand_range);
	register_property<WanderControl, Vector2>("r", &WanderControl::r,Vector2().ZERO);

}
void WanderControl::_init() {}
WanderControl::WanderControl() {
	
	r0 = Vector2().ZERO;
	r = Vector2().ZERO;
	distance = 32 + 1;
}
WanderControl::~WanderControl() {}

void WanderControl::_ready() {
	r0 = get_global_position();
	r = get_global_position();
	update_target_position();

}
void WanderControl::update_target_position() {
	srand((unsigned)time(NULL));
	Vector2 targetv = Vector2((real_t)rand_range(-distance, distance),(real_t)rand_range(-distance, distance));
	r = r0 + targetv;
}
real_t WanderControl::get_timer_left(Timer* timer) {
	return timer->get_time_left();
}
void WanderControl::start_wander_time(Timer* timer, real_t duration) {
	timer->start(duration);
}
void WanderControl::_on_Timer_timeout() {
	update_target_position();
}
int WanderControl::rand_range(int start, int stop) {
	return start + rand() % (abs(start - stop) + 1);
}
