ALboolean LoadALData()
{
	// Variables to load into.

	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop;

	// Load wav data into buffers.

	alGenBuffers(NUM_BUFFERS, Buffers);

	if(alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	alutLoadWAVFile("sound/hit.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[hit], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

//	alutLoadWAVFile("wavdata/Gun1.wav", &format, &data, &size, &freq, &loop);
//	alBufferData(Buffers[GUN1], format, data, size, freq);
//	alutUnloadWAV(format, data, size, freq);

//	alutLoadWAVFile("wavdata/Gun2.wav", &format, &data, &size, &freq, &loop);
//	alBufferData(Buffers[GUN2], format, data, size, freq);
//	alutUnloadWAV(format, data, size, freq);
	
	//alutLoadWAVFile("sound/dung.wav", &format, &data, &size, &freq, &loop);
	//alBufferData(Buffers[dung], format, data, size, freq);
	//alutUnloadWAV(format, data, size, freq);

	// Bind buffers into audio sources.

	alGenSources(NUM_SOURCES, Sources);

	if(alGetError() != AL_NO_ERROR)
		return AL_FALSE;



	//alSourcei (Sources[dung], AL_BUFFER,   Buffers[dung]   );
	//alSourcef (Sources[dung], AL_PITCH,    1.0f              );
	//alSourcef (Sources[dung], AL_GAIN,     1.0f              );
	//alSourcefv(Sources[dung], AL_POSITION, SourcesPos[dung]);
	//alSourcefv(Sources[dung], AL_VELOCITY, SourcesVel[dung]);
	//alSourcei (Sources[dung], AL_LOOPING,  AL_TRUE           );


	alSourcei (Sources[hit], AL_BUFFER,   Buffers[hit]   );
	alSourcef (Sources[hit], AL_PITCH,    1.0f              );
	alSourcef (Sources[hit], AL_GAIN,     1.0f              );
	alSourcefv(Sources[hit], AL_POSITION, SourcesPos[hit]);
	alSourcefv(Sources[hit], AL_VELOCITY, SourcesVel[hit]);
	alSourcei (Sources[hit], AL_LOOPING,  AL_FALSE           );
/*
	alSourcei (Sources[GUN1], AL_BUFFER,   Buffers[GUN1]   );
	alSourcef (Sources[GUN1], AL_PITCH,    1.0f            );
	alSourcef (Sources[GUN1], AL_GAIN,     1.0f            );
	alSourcefv(Sources[GUN1], AL_POSITION, SourcesPos[GUN1]);
	alSourcefv(Sources[GUN1], AL_VELOCITY, SourcesVel[GUN1]);
	alSourcei (Sources[GUN1], AL_LOOPING,  AL_FALSE        );

	alSourcei (Sources[GUN2], AL_BUFFER,   Buffers[GUN2]   );
	alSourcef (Sources[GUN2], AL_PITCH,    1.0f            );
	alSourcef (Sources[GUN2], AL_GAIN,     1.0f            );
	alSourcefv(Sources[GUN2], AL_POSITION, SourcesPos[GUN2]);
	alSourcefv(Sources[GUN2], AL_VELOCITY, SourcesVel[GUN2]);
	alSourcei (Sources[GUN2], AL_LOOPING,  AL_FALSE        );
*/
	// Do another error check and return.

	if(alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	return AL_TRUE;
}

void SetListenerValues()
{
	alListenerfv(AL_POSITION,    ListenerPos);
	alListenerfv(AL_VELOCITY,    ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
}
