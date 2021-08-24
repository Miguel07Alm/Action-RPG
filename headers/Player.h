#pragma once

#include "Root.h"
#include "HitBox.h"
#include "HurtBox.h"
#include "CustomAudio.h"
namespace godot {
	class Player : public KinematicBody2D
	{

		// Godot structure
	private:
		GODOT_CLASS(Player, KinematicBody2D)
	public:
		static void _register_methods();
		void _init();
		void _physics_process(float delta);
		void _ready();
		void _on_PlayerHurtBox_area_entered(Area2D * area);
		void _on_PlayerHurtBox_invincibility_off();
		void _on_PlayerHurtBox_invincibility_on();
		
		
		Player();
		~Player();


		// Gameplay variables
	public:
		Vector2 velocity;
		Vector2 input_vector;
		AnimationTree * animationTree;
		AnimationPlayer* blinkAnimation;
		AnimationNodeStateMachinePlayback * animationState;
		Ref<PackedScene> EffectsScene;
		HitBox* hitBox;
		Timer* timer;
		HurtBox* hurtBox;
		Ref<PackedScene> audioScene;
		CustomAudio* customAudio;
		int state = MOVE;
		int lifes;
		int MAX_LIFES;

	private:
		enum {
			MOVE,
			ROLL,
			ATTACK
		};
		real_t ACCELERATION;
		real_t MAX_SPEED;
		real_t FRICTION;
		real_t ROLL_SPEED;
		

		// Gameplay methods
	public:
		void move_state(float delta);
		void move();
		void attack_state(float delta);
		void roll_state();
		void animation_finished();
		void set_lifes(int new_lifes);

	private:

	};
}
