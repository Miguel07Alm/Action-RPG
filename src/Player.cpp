#include "Player.h"

using namespace std;
using namespace godot;

void Player::_register_methods() {
	register_method("_init", &Player::_init);
	register_method("_physics_process", &Player::_physics_process);
	register_method("_ready", &Player::_ready);
	register_method("move_state", &Player::move_state);
	register_method("move", &Player::move);
	register_method("attack_state", &Player::attack_state);
	register_method("roll_state", &Player::roll_state);
	register_method("animation_finished", &Player::animation_finished);
	register_method("set_lifes", &Player::set_lifes);
	register_method("_on_PlayerHurtBox_area_entered", &Player::_on_PlayerHurtBox_area_entered);
	register_method("_on_PlayerHurtBox_invincibility_off", &Player::_on_PlayerHurtBox_invincibility_off);
	register_method("_on_PlayerHurtBox_invincibility_on", &Player::_on_PlayerHurtBox_invincibility_on);
	register_property<Player, real_t>("ACCELERATION", &Player::ACCELERATION, 500);
	register_property<Player, real_t>("MAX_SPEED", &Player::MAX_SPEED, 100);
	register_property<Player, real_t>("FRICTION", &Player::FRICTION, 500);
	register_property<Player, real_t>("ROLL_SPEED", &Player::ROLL_SPEED, 125);
	register_property<Player, int>("MAX_LIFES", &Player::MAX_LIFES, 3);
	register_property<Player, int>("lifes", &Player::lifes, 3);
	register_signal<Player>("health_changed", Dictionary());
}
void Player::_init(){}
Player::Player() {
	velocity = Vector2().ZERO;
	ACCELERATION = 500;
	MAX_SPEED = 100;
	FRICTION = 500;
	ROLL_SPEED = 125;
	MAX_LIFES = 3;
	lifes = 3;
	animationState = NULL;
	animationTree = NULL;
	hitBox = NULL;
	hurtBox = NULL;
	customAudio = NULL;
	timer = NULL;
	blinkAnimation = NULL;
}
void Player::_ready() {
	//Set a low db volume.
	AudioServer* audioServer = AudioServer::get_singleton();
	audioServer->set_bus_volume_db(audioServer->get_bus_index("Master"), (real_t)-30);
	//------------------------
	Node* node = get_node(NodePath("AnimationTree"));
	if (node != NULL) {
		animationTree = (AnimationTree*)(node);
		animationState = (AnimationNodeStateMachinePlayback*)(animationTree->get("parameters/playback"));
	}
	blinkAnimation = (AnimationPlayer*)get_node(NodePath("BlinkAnimation"));
	auto loader = ResourceLoader::get_singleton();
	EffectsScene = loader->load("res://resources/Effects/Effects.tscn", "PackedScene");
	hurtBox = (HurtBox*)get_node(NodePath("PlayerHurtBox"));
	timer = (Timer*)get_node(NodePath("PlayerHurtBox/Timer"));
	audioScene = loader->load("res://resources/Music_and_Sounds/AudioStreamPlayer.tscn", "PackedScene");
	set_lifes(MAX_LIFES);

}
Player::~Player() {}

void Player::_physics_process(float delta) {
	switch (state) {
		case MOVE:
			move_state(delta);
			break;
		case ATTACK:
			attack_state(delta);
			break;
		case ROLL:
			roll_state();
			break;
		default:
			break;
	}
}

void Player::move_state(float delta) {
	Input* i = Input::get_singleton();
	input_vector = Vector2().ZERO;
	input_vector.x = i->get_action_strength("ui_right") - i->get_action_strength("ui_left");
	input_vector.y = i->get_action_strength("ui_down") - i->get_action_strength("ui_up");
	input_vector = input_vector.normalized();
	if (input_vector.length() > 0) {
		animationTree->set("parameters/Idle/blend_position", input_vector);
		animationTree->set("parameters/Run/blend_position", input_vector);
		animationTree->set("parameters/Attack/blend_position", input_vector);
		animationTree->set("parameters/Roll/blend_position", input_vector);
		velocity = velocity.move_toward(input_vector * MAX_SPEED, ACCELERATION*delta);
		animationState->travel("Run");
	}
	else {
		animationState->travel("Idle");
		velocity = velocity.move_toward(Vector2().ZERO, FRICTION * delta);

	}
	
	if (i->is_key_pressed(GlobalConstants::KEY_ESCAPE)) get_tree()->quit();
	if (i->is_action_just_pressed("ui_attack")) {
		state = ATTACK;
	}
	if (i->is_action_just_pressed("ui_roll")){
		state = ROLL;
	
	}
	move();
}

void Player::move() {
	velocity = move_and_slide(velocity);
}
void Player::attack_state(float delta) {
	velocity = Vector2().ZERO;
	animationState->travel("Attack");

}

void Player::roll_state() {
	Vector2 rollVector = (Vector2)(animationTree->get("parameters/Roll/blend_position"));
	velocity = rollVector * ROLL_SPEED;
	animationState->travel("Roll");
	move();

}

void Player::animation_finished() {
	state = MOVE;
}

void Player::_on_PlayerHurtBox_area_entered(Area2D* area) {
	set_lifes(lifes - (int)area->get("damage"));
	hurtBox->start_invincibility(1, timer);
	customAudio = (CustomAudio*)audioScene->instance();
	customAudio->set("audio_name", "Hurt");
	hurtBox->set_hitEffect(EffectsScene, customAudio);
	

}
void Player::set_lifes(int new_lifes) {
	lifes = new_lifes;
	emit_signal("health_changed");
}
void Player::_on_PlayerHurtBox_invincibility_off() {
	blinkAnimation->play("stop");
}
void Player::_on_PlayerHurtBox_invincibility_on() {
	blinkAnimation->play("start");
}