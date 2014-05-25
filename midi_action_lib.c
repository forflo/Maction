#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <alsa/asoundlib.h>

struct mac_midi_device {
    int port;
    int client;
    bool connected;
	snd_seq_t *sequencer;
};

struct mac_note {
	int value;
	char *name;
};

static struct mac_note mapping[] = 
	{{0, "c"}, {1, "c#"}, {2, "d"}, {3, "d#"},
	 {4, "e"}, {5,  "f"}, {6, "f#"}, {7, "g"},
	 {8, "g#"}, {9, "a"}, {10,"a#"}, {11,"b"}};

static snd_seq_t *new_seq(char *name);

struct mac_midi_device *mac_init_midi_dev(int client, int port, char *name);

int mac_connect(struct mac_midi_device *mdev);

int mac_reg_on_note(int note, int octave, struct mac_midi_device *dev, 
                    void *(*callback[2])(void *param), void *params[2]);

int mac_reg_on_note_c(char *note, int octave, struct mac_midi_device *dev, 
                    void *(*callback[2])(void *aram), void *params[2]);

struct midi_device *init_midi_dev(int client, int port){
    if(client < 0 || port < 0)
        return NULL;

    return NULL;
}

int register_on_note(int note, int octave, struct mac_midi_device *dev, 
                    void *(*callback[2])(void *aram), void *params[2]){
    if(note < 0 || dev == NULL || callback == NULL || params == NULL)
        return -1;

    if(callback[0] == NULL || callback[1] == NULL)
        return -1;

    if(params[0] == NULL || params [1] == NULL)
        return -1;



    return 0;
}

int register_on_note_c(char *note, int octave, struct mac_midi_device *dev, 
                        void *(*callback[2])(void *aram), void *params[2]){
    int i;

    if(note == NULL || dev == NULL || callback == NULL || params == NULL)
        return -1;


    return 0;
}

struct mac_midi_device *mac_init_midi_dev(int client, int port, char *name){
	if (client < 0 || port < 0)
		return NULL;

	struct mac_midi_device *temp = (struct mac_midi_device *)
			malloc(sizeof(struct mac_midi_device));
	if(temp == NULL)
		return NULL;

	temp->port = port;
	temp->client = client;
	temp->connected = false;
	temp->sequencer = new_seq(name);
	if(temp->sequencer == NULL)
		return NULL;

	return temp;
}

int mac_connect(struct mac_midi_device *mdev){
	if(snd_seq_connect_from(mdev->sequencer, 0, mdev->client, mdev->port) <0)
		return -1;
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
    if((portid = snd_seq_create_simple_port(temp, "name",
                    SND_SEQ_PORT_CAP_WRITE | SND_SEQ_PORT_CAP_SUBS_WRITE,
                    SND_SEQ_PORT_TYPE_APPLICATION)) <0)
        return NULL;

    return temp;
}
