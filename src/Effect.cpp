#include "Effect.h"

using namespace std;
using namespace godot;


void Effect::_register_methods() {
	register_method("_init", &Effect::_init);
	register_method("_process", &Effect::_process);
	register_method("_ready", &Effect::_ready);
	register_method("_on_Effects_animation_finished", &Effect::_on_Effects_animation_finished);
	register_property<Effect, int>("TYPE_EFFECT", &Effect::TYPE_EFFECT, 0);
}
Effect::Effect() {
	TYPE_EFFECT = 0;
	loader = NULL;
	audioEffect = NULL;
}
void Effect::_init() {}
void Effect::_ready() {
	connect("animation_finished", this, "_on_Effects_animation_finished");
	effect_types[GRASS_EFFECT] = "GrassEffect";
	effect_types[BAT_DEATH_EFFECT] = "BatDeathEffect";
	effect_types[HIT_EFFECT] = "HitEffect";
	loader = ResourceLoader::get_singleton();
	audioStreamScene = loader->load("res://resources/Music_and_Sounds/AudioStreamPlayer.tscn", "PackedScene");
	String target_path = "res://resources/Music_and_Sounds/";
	if (TYPE_EFFECT > 0) {
		audioStream = loader->load(target_path + effect_types[TYPE_EFFECT] + ".wav", "AudioStream");
		audioEffect = (AudioStreamPlayer*)audioStreamScene->instance();

		audioEffect->set_stream(audioStream);
		add_child(audioEffect);
		audioEffect->play();
	}
}

Effect::~Effect() {}
void Effect::_process(float delta) {
	
	play(effect_types[TYPE_EFFECT]);
	

}
void Effect::_on_Effects_animation_finished() {
	queue_free();
}