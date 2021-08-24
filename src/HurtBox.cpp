#include "HurtBox.h"

using namespace std;
using namespace godot;


void HurtBox::_register_methods() {
	register_method("_init", &HurtBox::_init);
	register_method("_ready", &HurtBox::_ready);
	register_method("_on_Timer_timeout", &HurtBox::_on_Timer_timeout);
	register_method("set_hitEffect", &HurtBox::set_hitEffect);
	register_method("start_invincibility", &HurtBox::start_invincibility);
	register_method("invincible_state", &HurtBox::invincible_state);
	register_method("set_invincible", &HurtBox::set_invincible);

	register_method("_on_HurtBox_invincibility_on", &HurtBox::_on_HurtBox_invincibility_on);
	register_method("_on_HurtBox_invincibility_off", &HurtBox::_on_HurtBox_invincibility_off);

	register_signal<HurtBox>("invincibility_on", Dictionary());
	register_signal<HurtBox>("invincibility_off", Dictionary());
	

}
void HurtBox::_init() {}
HurtBox::HurtBox() {}
HurtBox::~HurtBox() {}

void HurtBox::_ready() {
	collisionShape = (CollisionShape2D*)get_node(NodePath("CollisionShape2D"));
}
void HurtBox::set_hitEffect(Ref<PackedScene> EffectsScene, CustomAudio* customAudio) {

	if (EffectsScene.is_valid()) {
		Node* effect = EffectsScene->instance();
		Node* world = get_tree()->get_current_scene();
		effect->set("TYPE_EFFECT", 2);
		effect->set("offset", Vector2(0, -8));
		effect->set("centered", true);
		effect->set("global_position", get_global_position());
		world->add_child(effect);
		world->add_child(customAudio);
	}
		
	
}
void HurtBox::invincible_state() {
	if (invincible) emit_signal("invincibility_on");
	else emit_signal("invincibility_off");
}
void HurtBox::set_invincible(bool boolean) {
	invincible = boolean;
	invincible_state();
}
void HurtBox::start_invincibility(real_t duration, Timer* timer) {
	set_invincible(true);
	timer->start(duration);
	
}
void HurtBox::_on_Timer_timeout() {
	set_invincible(false);
}
void HurtBox::_on_HurtBox_invincibility_on() {
	collisionShape->set_deferred("disabled", true);
}
void HurtBox::_on_HurtBox_invincibility_off() {
	collisionShape->set_deferred("disabled", false);
}


