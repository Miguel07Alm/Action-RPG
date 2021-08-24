#pragma once
#pragma once
#include "Root.h"
namespace godot {
	class CustomAudio : public AudioStreamPlayer
	{
		// Godot structure
	private:
		GODOT_CLASS(CustomAudio, AudioStreamPlayer)
	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _on_CustomAudio_finished();
		CustomAudio();
		~CustomAudio();


		// Gameplay variables
	public:
		Ref<AudioStream> audioStream;
		ResourceLoader* loader;
	private:
		String audio_name;

		// Gameplay methods
	public:

	private:

	};
}
