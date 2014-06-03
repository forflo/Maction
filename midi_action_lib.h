#define POLL_TIMEOUT 100000

struct mac_midi_device {
    int port;
    int client;
    bool connected;
	snd_seq_t *sequencer;
};

struct mac_func_note_mapping {
	int note;
	void *(**callback)(void *param);
	void **params;
};

struct mac_action_env {
	pthread_t *event_loop;
	pthread_mutex_t *mutex;
	struct slist *actions;
	struct mac_midi_device *mdev;
};

struct mac_note {
	int value;
	char *name;
};

static struct mac_note mapping[] = 
	{{0, "c"}, {1, "c#"}, {2, "d"}, {3, "d#"},
	 {4, "e"}, {5,  "f"}, {6, "f#"}, {7, "g"},
	 {8, "g#"}, {9, "a"}, {10,"a#"}, {11,"b"}};

/* helper function */
static snd_seq_t *new_seq(char *name);

/* Polling for new events. The actions list in env
 	is traversed if a new event occures */
static void mac_event_loop(struct mac_action_env *env);

/* Creates a new mac_midi_device object which represents
 	a midi keyboard for example. */
struct mac_midi_device *mac_init_midi_dev(int client, int port, char *name);

int mac_connect(struct mac_midi_device *mdev);

int mac_reg_on_note(int note, int octave, struct mac_action_env *env, 
                    void *(*callback[2])(void *param), void *params[2]);

int mac_reg_on_note_c(char *note, int octave, struct mac_action_env *env, 
                    void *(*callback[2])(void *aram), void *params[2]);


/* Creates a new mac_action environment with an empty list and no
	started thread */
struct mac_action_env *mac_init_env(struct mac_midi_device *mdev);

/* Starts an event loop in a new thread and saves the thread inside
 	the action environment */
int mac_start_event_loop(struct mac_action_env *env);
