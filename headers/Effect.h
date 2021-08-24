#pragma once
#include "Root.h"
namespace godot {
	class Effect : public AnimatedSprite
	{
		// Godot structure
	private:
		GODOT_CLASS(Effect, AnimatedSprite)
	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _process(float delta);
		void _on_Effects_animation_finished();
		Effect();
		~Effect();


		// Gameplay variables
	public:
		Ref<PackedScene> audioStreamScene;
		Ref<AudioStream> audioStream;
		ResourceLoader * loader;
		AudioStreamPlayer* audioEffect;
	private:
		int TYPE_EFFECT;
		enum {
			GRASS_EFFECT,
			BAT_DEATH_EFFECT,
			HIT_EFFECT
		};
		Dictionary effect_types;
		
		// Gameplay methods
	public:
		
	private:

	};
}
