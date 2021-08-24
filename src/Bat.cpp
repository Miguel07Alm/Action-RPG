#include "Bat.h"

using namespace std;
using namespace godot;

void Bat::_register_methods() {
	register_method("_init", &Bat::_init);
	register_method("_ready", &Bat::_ready);
	register_method("_physics_process", &Bat::_physics_process);
	register_method("_on_HurtBox_area_entered", &Bat::_on_HurtBox_area_entered);
	register_method("set_deathEffect", &Bat::set_deathEffect);
	register_method("idle_state", &Bat::idle_state);
	register_method("wander_state", &Bat::wander_state);
	register_method("chase_state", &Bat::chase_state);
	register_method("move", &Bat::move);
	register_method("seek_player", &Bat::seek_player);
	register_method("set_random_state", &Bat::set_random_state);
	register_method("wander_function", &Bat::wander_function);
	register_method("move_toward", &Bat::move_toward);
	register_method("rand_range", &Bat::rand_range);
	register_method("_on_BatHurtBox_invincibility_on", &Bat::_on_BatHurtBox_invincibility_on);
	register_method("_on_BatHurtBox_invincibility_off", &Bat::_on_BatHurtBox_invincibility_off);
	register_property<Bat, real_t>("MAX_VELOCITY", &Bat::MAX_SPEED, 50);
	register_property<Bat, real_t>("ACCELERATION", &Bat::ACCELERATION, 300);
	register_property<Bat, real_t>("FRICTION", &Bat::FRICTION, 120);

}

void Bat::_init(){}
Bat::Bat() {
	
	velocity = Vector2().ZERO;
	knockback = Vector2().ZERO;
	MAX_SPEED = 50;
	ACCELERATION = 300;
	FRICTION = 120;
	playerDetection = NULL;
	animatedSprite = NULL;
	hurtBox = NULL;
	softCollision = NULL;
	playerAnimationTree = NULL;
	timer = NULL;
	wanderController = NULL;
	customAudio = NULL;
	blinkAnimation = NULL;
	hurtBoxtimer = NULL;
}

Bat::~Bat() {}

void Bat::_ready() {
	
	auto loader = ResourceLoader::get_singleton();
	EffectsScene = loader->load("res://resources/Effects/Effects.tscn", "PackedScene");
	playerDetection = (HitBox*)get_node(NodePath("PlayerDetectionZone"));
	animatedSprite = get_node(NodePath("AnimatedSprite"));
	hurtBox = (HurtBox*)get_node(NodePath("BatHurtBox"));
	new_bat_Scene = loader->load("res://resources/Enemies/Bat.tscn", "PackedScene");
	audioScene = loader->load("res://resources/Music_and_Sounds/AudioStreamPlayer.tscn", "PackedScene");
	r0 = get_global_position();
	playerAnimationTree = (AnimationTree*)get_node(NodePath("/root/World/Characters/Player/AnimationTree"));
	softCollision = (HitBox*)get_node(NodePath("SoftCollision"));
	wanderController = (WanderControl*)get_node(NodePath("WanderControl"));
	timer = (Timer*)wanderController->get_node(NodePath("Timer"));
	blinkAnimation = (AnimationPlayer*)get_node(NodePath("BlinkAnimation"));
	hurtBoxtimer = (Timer*)hurtBox->get_node(NodePath("Timer"));
	animatedSprite->set("frame", rand_range(0,4));
	set_random_state();
}

void Bat::_physics_process(float delta) {
	srand((unsigned)time(NULL));
	knockback = knockback.move_toward(Vector2().ZERO, delta * FRICTION);
	knockback = move_and_slide(knockback);
	switch (state)
	{
		case IDLE:
			idle_state(delta);
			break;
		case WANDER:
			wander_state(delta);
			break;
		case CHASE:
			chase_state(delta);
			break;
		default:
			break;
	}
	velocity += softCollision->get_push_vector() * delta * 400;
	move();
	animatedSprite->set("flip_h", velocity.x < 0);
}
void Bat::set_deathEffect() {
	if (EffectsScene.is_valid()) {
		Node* deathEffect = EffectsScene->instance();
		deathEffect->set("TYPE_EFFECT", 1);
		deathEffect->set("centered", true);
		deathEffect->set("offset", (Vector2)deathEffect->get("offset") + Vector2(8,8));
		deathEffect->set("global_position", get_global_position());		
		get_parent()->add_child(deathEffect);
	}
}


void Bat::chase_state(float delta) {
	
	
	Node* player = playerDetection->get("player");
	if (player != NULL) {
		move_toward((Vector2)player->get("global_position"), delta);
	}
	else state = IDLE;
	
	
}
void Bat::idle_state(float delta) {
	velocity = velocity.move_toward(Vector2().ZERO, delta * FRICTION);
	wander_function();

}
void Bat::wander_function() {
	seek_player();
	if (wanderController->get_timer_left(timer) == 0) {
		set_random_state();
		wanderController->start_wander_time(timer, (real_t)rand_range(1, 3));
	}
}
void Bat::move_toward(Vector2 p_to, float delta) {
	Vector2 direction = get_global_position().direction_to(p_to);
	velocity = velocity.move_toward(direction * MAX_SPEED, ACCELERATION * delta);
}
void Bat::wander_state(float delta){
	wander_function();
	move_toward((Vector2)wanderController->get("r"), delta);
	if (get_global_position().distance_to((Vector2)wanderController->get("r")) <= MAX_SPEED * delta) {
		set_random_state();
		wanderController->start_wander_time(timer, (real_t)rand_range(1,3));
	}
}
void Bat::move() {
	velocity = move_and_slide(velocity);
}
void Bat::set_random_state() {
	Array states;
	states.append(IDLE);
	states.append(WANDER);
	states.shuffle();
	state = states[0];
}
void Bat::seek_player() {
	Node* player = playerDetection->get("player");
	if (player != NULL) state = CHASE;
}
int Bat::rand_range(int start, int stop) {
	return start + rand() % (abs(start - stop) + 1);
}
void Bat::_on_HurtBox_area_entered(Area2D* area) {
	if (health == 0) {
		set_deathEffect();
		queue_free();
		if (new_bat_Scene.is_valid()) {
			Node* parent = get_parent();
			Node* new_bat = new_bat_Scene->instance();
			new_bat->set("global_position", r0);
			parent->call_deferred("add_child", new_bat);
		}
	}
	Vector2 blend_position = (Vector2)(playerAnimationTree->get("parameters/Run/blend_position"));

	if (area->get_name() == "SwordHitBox") {
		health -= (int)(area->get("damage"));
		hurtBox->start_invincibility((real_t)0.4, hurtBoxtimer);
		customAudio = (CustomAudio*)audioScene->instance();
		customAudio->set("audio_name", "Hurt");
		hurtBox->set_hitEffect(EffectsScene, customAudio);
		knockback = blend_position * FRICTION;
	}
	else if (area->get_name() == "RunHitBox") knockback = blend_position * FRICTION / 2;

}
void Bat::_on_BatHurtBox_invincibility_off() {
	blinkAnimation->play("stop");

}
void Bat::_on_BatHurtBox_invincibility_on() {
	blinkAnimation->play("start");
}