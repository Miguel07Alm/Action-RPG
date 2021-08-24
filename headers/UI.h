#pragma once
#include "Root.h"
namespace godot {
	class UI : public Control
	{
		// Godot structure
	private:
		GODOT_CLASS(UI, Control)
	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _on_Player_health_changed();
		

		UI();
		~UI();


		// Gameplay variables
	public:
		TextureRect* heartUIEmpty;
		TextureRect* heartUIFull;
		Node* player;
		int lifes;
		int MAX_LIFES;
	private:
		real_t heart_width = 15, heart_height = 11;



		// Gameplay methods
	public:
		void set_rect_size();
		String player_path();
		
	private:

	};
}