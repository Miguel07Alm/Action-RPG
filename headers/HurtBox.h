#pragma once
#include "Root.h"
#include "CustomAudio.h"
namespace godot {
	class HurtBox : public Area2D
	{
		// Godot structure
	private:
		GODOT_CLASS(HurtBox, Area2D)
	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _on_Timer_timeout();
		void _on_HurtBox_invincibility_on();
		void _on_HurtBox_invincibility_off();
		
		HurtBox();
		~HurtBox();


		// Gameplay variables
	public:
		bool invincible = false;
		CollisionShape2D* collisionShape;
	private:




		// Gameplay methods
	public:
		
		void set_hitEffect(Ref<PackedScene> EffectsScene, CustomAudio* customAudio);
		void invincible_state();
		void set_invincible(bool boolean);
		void start_invincibility(real_t duration, Timer* timer);
	private:

	};
}