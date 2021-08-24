#include "Grass.h"

using namespace std;
using namespace godot;

void print(String message) {
	Godot::print(message);
}

void Grass::_register_methods() {
	register_method("_ready", &Grass::_ready);
	register_method("_init", &Grass::_ready);
	register_method("_on_HurtBox_area_entered", &Grass::_on_HurtBox_area_entered);
}
void Grass::_init(){}
void Grass::_ready() {}
Grass::Grass() {
	auto loader = ResourceLoader::get_singleton();
	EffectsScene = loader->load("res://resources/Effects/Effects.tscn", "PackedScene");
	
}

Grass::~Grass() {}

void Grass::set_grassEffect() {
	if (EffectsScene.is_valid()) {
		Node * grassEffect = EffectsScene->instance();
		grassEffect->set("TYPE_EFFECT", 0);
		grassEffect->set("global_position", get_global_position());
		get_parent()->add_child(grassEffect);
	}
}
void Grass::_on_HurtBox_area_entered(Area2D* _area) {
	set_grassEffect();
	queue_free();
}