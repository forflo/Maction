#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct midi_device {
    int port;
    int source;
    bool connected;
};

struct midi_device *init_midi_dev(int client, int port);

int register_on_note(int note, int octave, struct midi_device *dev, 
                    void *(*callback[2])(void *param), void *params[2]);

int register_on_note_c(char *note, int octave, struct midi_device *dev, 
                    void *(*callback[2])(void *aram), void *params[2]);

struct midi_device *init_midi_dev(int client, int port){
    if(client < 0 || port < 0)
        return NULL;

    return NULL;
}

int register_on_note(int note, int octave, struct midi_device *dev, 
                    void *(*callback[2])(void *aram), void *params[2]){
    if(note < 0 || dev == NULL || callback == NULL || params == NULL)
        return -1;

    if(callback[0] == NULL || callback[1] == NULL)
        return -1;

    if(params[0] == NULL || params [1] == NULL)
        return -1;



    return 0;
}

int register_on_note_c(char *note, int octave, struct midi_device *dev, 
                        void *(*callback[2])(void *aram), void *params[2]){
    int i;
    char *notes[] = {"a",   "a#",   "b",    "c", 
                     "c#",  "d",    "d#",   "e", 
                     "f",   "f#",   "g",    "g#"};

    if(note == NULL || dev == NULL || callback == NULL || params == NULL)
        return -1;

    for(i=0; i<sizeof(notes); i++){
        if(notes[i][0] != note[0])
            return -1;
        if(tolower(notes[i][0]) != note[0])
            return -1;
    }

    return 0;
}

static snd_seq_t *new_seq(char *name){
    snd_seq_t *temp;
    int portid;

    if(name == NULL)
        return NULL;

    if(snd_seq_open(&temp, "default", SND_SEQ_OPEN_INPUT, 0) < 0)
        return NULL; 

    snd_seq_set_client_name(temp, name);
    if((portid = snd_seq_create_simple_port(handle, "name",
                    SND_SEQ_PORT_CAP_WRITE | SND_SEQ_PORT_CAP_SUBS_WRITE,
                    SND_SEQ_PORT_TYPE_APPLICATION)) <0)
        return NULL;

    return temp;
}
