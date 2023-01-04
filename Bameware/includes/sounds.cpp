#include "sounds.h"
#include "../api.h"
#include <thread>
#include "string_obfuscation.h"

using namespace std::chrono_literals;

void playback_loop()
{
	BASS::bass_lib_handle = BASS::bass_lib.LoadFromFile("C:\\bass.dll");

	if (BASS_INIT_ONCE())
		BASS::bass_init = TRUE;

	static auto bass_needs_reinit = false;

	static std::pair<std::string, char> channels[] = {
		__("http://www.rockantenne.de/webradio/channels/alternative.m3u"),
		__("http://listen.technobase.fm/dsl.pls"),
		__("http://streams.bigfm.de/bigfm-deutschrap-128-aac"),
		__("http://mp3.stream.tb-group.fm/tt.mp3"),
		__("http://mp3.stream.tb-group.fm/clt.mp3"),
		__("http://mp3.stream.tb-group.fm/ht.mp3"),
		__("http://www.iloveradio.de/iloveradio.m3u"),
		__("http://8bit.fm:8000/live")
	};

	while (true)
	{
		std::this_thread::sleep_for(100ms);

		if (BASS::bass_init && desired_channel)
		{
			static auto current_channel = 0;

			if (current_channel != desired_channel || bass_needs_reinit)
			{
				bass_needs_reinit = false;
				BASS_Start();
				_rt(channel, channels[desired_channel]);
				BASS_OPEN_STREAM(channel);
				current_channel = desired_channel;
			}

			BASS_SET_VOLUME(BASS::stream_handle, BASS::open ? 0.f : BASS::vol23);
			BASS_PLAY_STREAM();
		}
		else if (BASS::bass_init)
		{
			bass_needs_reinit = true;
			BASS_StreamFree(BASS::stream_handle);
		}
	}
}
