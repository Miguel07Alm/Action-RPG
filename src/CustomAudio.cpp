#include "CustomAudio.h"

using namespace std;
using namespace godot;


void CustomAudio::_register_methods() {
	register_method("_init", &CustomAudio::_init);
	register_method("_ready", &CustomAudio::_ready);
	register_method("_on_CustomAudio_finished", &CustomAudio::_on_CustomAudio_finished);
	register_property<CustomAudio, String>("audio_name", &CustomAudio::audio_name, "");
}
CustomAudio::CustomAudio() {
	audio_name = "";
	loader = NULL;
}

CustomAudio::~CustomAudio() {}
void CustomAudio::_init() {}
void CustomAudio::_ready() {
	if (audio_name != "Null" && audio_name.length() > 0) {
		connect("finished", this, "_on_CustomAudio_finished");

		loader = ResourceLoader::get_singleton();
		String target_path = "res://resources/Music_and_Sounds/";
	
		audioStream = loader->load(target_path + audio_name + ".wav", "AudioStream");
		set_stream(audioStream);
		play();
	}
}
void CustomAudio::_on_CustomAudio_finished() {
	queue_free();
}
