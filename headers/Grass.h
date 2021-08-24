#pragma once
#include "Root.h"

namespace godot {
	class Grass : public Node2D
	{
		// Godot structure
	private:
		GODOT_CLASS(Grass, Node2D)
	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _on_HurtBox_area_entered(Area2D * _area);
		Grass();
		~Grass();


		// Gameplay variables
	public:
		Ref<PackedScene> EffectsScene;
		

	private:


		// Gameplay methods
	public:
		void set_grassEffect();
	private:

	};
}
