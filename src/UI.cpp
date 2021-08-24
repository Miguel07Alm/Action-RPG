#include "UI.h"


using namespace std;
using namespace godot;


void UI::_register_methods() {
	register_method("_init", &UI::_init);
	register_method("_ready", &UI::_ready);
	register_method("player_path", &UI::player_path);
	register_method("set_rect_size", &UI::set_rect_size);
	register_method("_on_Player_health_changed", &UI::_on_Player_health_changed);

}
void UI::_init() {}
UI::UI() {
	MAX_LIFES = 0;
	lifes = 0;
	heartUIEmpty = NULL;
	heartUIFull = NULL;
	player = NULL;

}
UI::~UI() {}
String UI::player_path() {
	String target = "Player";
	String path;
	Node* world = get_tree()->get_current_scene();
	Array world_children = world->get_children();
	for (int i = 0; i < world_children.size(); i++) {
		Array children = ((Node*)world_children[i])->get_children();
		for (int j = 0; j < children.size(); j++) {
			Node* node = children[j];
			if (node->get_name() == target) return String(((Node*)world_children[i])->get_name() + "/" + node->get_name());
		}
	}
	return String();

}
void UI::_ready() {
	heartUIEmpty = (TextureRect*)get_node("HeartUIEmpty");
	heartUIFull = (TextureRect*)get_node("HeartUIFull");
	player = (Node*)get_tree()->get_current_scene()->get_node(NodePath(player_path()));
	player->connect("health_changed",this,"_on_Player_health_changed");
	MAX_LIFES = (int)player->get("MAX_LIFES");
	lifes = MAX_LIFES;
	set_rect_size();
}
void UI::set_rect_size() {
	heartUIEmpty->set("rect_size", Vector2(heart_width * MAX_LIFES, heart_height));
	heartUIFull->set("rect_size", Vector2(heart_width * lifes, heart_height));
}
void UI::_on_Player_health_changed() {
	if (lifes >= 0) {
		MAX_LIFES = (int)player->get("MAX_LIFES");
		lifes = (int)player->get("lifes");
		set_rect_size();
	}
	if (lifes <= 0) 
		player->queue_free();
	
}
