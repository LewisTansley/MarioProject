#include "SoundEffect.h"


using namespace::std;

Mix_Chunk* mSound[2];
bool soundPlaying;

void PlaySound(string path, int looping) {

	if (!Mix_Playing(0)) {
		mSound[0] = Mix_LoadWAV(path.c_str());
		Mix_PlayChannel(0, mSound[0], looping);
	}
	else if (!Mix_Playing(1)) {
		mSound[1] = Mix_LoadWAV(path.c_str());
		Mix_PlayChannel(1, mSound[1], looping);
	}
	else if (!Mix_Playing(2)) {
		mSound[2] = Mix_LoadWAV(path.c_str());
		Mix_PlayChannel(2, mSound[2], looping);

	}

}