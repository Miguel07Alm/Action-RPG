#pragma once
#include "Root.h"
namespace godot {
	class WanderControl : public Node2D
	{
		// Godot structure
	private:
		GODOT_CLASS(WanderControl, Area2D)
	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _on_Timer_timeout();
		

		WanderControl();
		~WanderControl();


		// Gameplay variables
	public:
		Vector2 r0;
		Vector2 r;
		int distance;

	private:




		// Gameplay methods
	public:
		void update_target_position();
		real_t get_timer_left(Timer* timer);
		void start_wander_time(Timer* timer, real_t duration);
		int rand_range(int start, int stop);

	private:

	};
}
