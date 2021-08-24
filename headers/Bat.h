#pragma once
#include "Root.h"
#include "Player.h"
#include "WanderControl.h"
#include "CustomAudio.h"
#include "HitBox.h"
#include "HurtBox.h"
namespace godot {
	class Bat : public KinematicBody2D
	{

		// Godot structure
	private:
		GODOT_CLASS(Bat, KinematicBody2D)
	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _physics_process(float delta);
		void set_deathEffect();
		void _on_HurtBox_area_entered(Area2D * area);
		void _on_BatHurtBox_invincibility_off();
		void _on_BatHurtBox_invincibility_on();
		
		Bat();
		~Bat();


		// Gameplay variables
	public:
		Vector2 knockback;
		Vector2 velocity;
		Vector2 r0;
		int health = 2;
		int state = CHASE;
		Ref<PackedScene> EffectsScene;
		HitBox* playerDetection;
		Node* animatedSprite;
		HurtBox* hurtBox;
		HitBox* softCollision;
		Ref<PackedScene> new_bat_Scene;
		AnimationTree * playerAnimationTree;
		Timer* timer;
		WanderControl* wanderController;
		Ref<PackedScene> audioScene;
		CustomAudio* customAudio;
		AnimationPlayer* blinkAnimation;
		Timer* hurtBoxtimer;
		

	private:
		enum {
			IDLE, //Reposo
			WANDER, //Deambular
			CHASE //Perseguir
		};
		real_t MAX_SPEED;
		real_t ACCELERATION;
		real_t FRICTION;

		// Gameplay methods
	public:
		void idle_state(float delta);
		void wander_state(float delta);
		void wander_function();
		void chase_state(float delta);
		void move();
		void seek_player();
		void set_random_state();
		void move_toward(Vector2 p_to, float delta);
		int rand_range(int start, int stop);
		
	private:

	};
}
