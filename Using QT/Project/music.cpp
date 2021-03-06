#include "listheaders.h"
#include "global.h"


Music::Music()
{
    song = new QSound("://Images/Sound/song3.wav");
    music.push_back(new QSound("://Images/Sound/cheese.wav"));
    music.push_back(new QSound("://Images/Sound/end.wav"));
    music.push_back(new QSound("://Images/Sound/win.wav"));
}

Music::~Music() //music destructor
{
    delete (song);
    for (int i = 0; i < sound_effects_counter; i++)
    {
        delete (music[i]);
    }
}

void Music::start_song() //function that makes the music start
{
    song->play();
    song->setLoops(QSound::Infinite);
}

void Music::stop_song() //function that makes the music stop
{
    song->stop();
}

void Music::play_sound_effect(Sound_effects sound_effect) //function that makes the good sound effect play
{
    music[sound_effect]->play();
}



