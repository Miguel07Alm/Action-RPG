#include "HitBox.h"

using namespace std;
using namespace godot;


void HitBox::_register_methods() {
	register_method("_init", &HitBox::_init);
	register_method("is_colliding", &HitBox::is_colliding);
	register_method("get_push_vector", &HitBox::get_push_vector);
	register_method("get_player", &HitBox::get_player);
	register_method("_on_PlayerDetectionZone_body_exited", &HitBox::_on_PlayerDetectionZone_body_exited);
	register_method("_on_PlayerDetectionZone_body_entered", &HitBox::_on_PlayerDetectionZone_body_entered);
	register_property<HitBox, int>("damage", &HitBox::damage, 1);
	register_property<HitBox, Node*>("player", &HitBox::player, NULL);

}
HitBox::HitBox() {
	damage = 1;
	player = NULL;
	
}
HitBox::~HitBox() {}
void HitBox::_init() {}

//DETECTION OF PLAYER
void HitBox::_on_PlayerDetectionZone_body_entered(Node* body) {
	player = body;
}
void HitBox::_on_PlayerDetectionZone_body_exited(Node* body) {
	player = NULL;
}
//SOFT COLLISIONS
bool HitBox::is_colliding() {
	Array areas = get_overlapping_areas();
	return areas.size() > 0;
}
Vector2 HitBox::get_push_vector() {
	Array areas = get_overlapping_areas();
	Vector2 push_vector = Vector2().ZERO;
	if (is_colliding()) {
		Area2D * area= (Area2D*)areas[0];
		push_vector = area->get_global_position().direction_to(get_global_position());
	}
	return push_vector;
}
Node* HitBox::get_player() {
	return player;
}
