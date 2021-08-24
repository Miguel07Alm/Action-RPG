#pragma once
#include "Root.h"
namespace godot {
	class HitBox : public Area2D
	{
		// Godot structure
	private:
		GODOT_CLASS(HitBox, Area2D)
	public:
		static void _register_methods();
		void _init();
		void _on_PlayerDetectionZone_body_exited(Node * body);
		void _on_PlayerDetectionZone_body_entered(Node* body);
		HitBox();
		~HitBox();


		// Gameplay variables
	public:
		Node* player;

	private:
		int damage;

		// Gameplay methods
	public:
		bool is_colliding();
		Vector2 get_push_vector();
		Node* get_player();
	private:

	};
}