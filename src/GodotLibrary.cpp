#include "Player.h"
#include "Bat.h"
#include "Grass.h"
#include "Effect.h"
#include "HitBox.h"
#include "HurtBox.h"
#include "UI.h"
#include "WanderControl.h"
#include "CustomAudio.h"
using namespace godot;

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options * o) {
	Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options * o) {
	Godot::gdnative_terminate(o);
}
extern "C" void GDN_EXPORT godot_nativescript_init(void* handle) {
	Godot::nativescript_init(handle);
	register_class<Player>();
	register_class<Bat>();
	register_class<Grass>();
	register_class<Effect>();
	register_class<HitBox>();
	register_class<HurtBox>();
	register_class<UI>();
	register_class<WanderControl>();
	register_class<CustomAudio>();
}