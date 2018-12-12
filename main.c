#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <jack/jack.h>
#include <jack/midiport.h>

#define DEFAULT_NTRIALS 1000
#define MIDI_NOTE_ON_CHAN1 144

jack_client_t *jackClient;
jack_port_t *jackPortIn;

struct timespec *times;
int idx = 0;
int ntrials;

static int _jack_callback(jack_nframes_t nframes, void *arg) {

    void *portBuf; // cannot be cached! see jack.h
    portBuf = jack_port_get_buffer(jackPortIn, nframes);

    jack_nframes_t eventCount = jack_midi_get_event_count(portBuf);

    struct timespec t;

    jack_midi_event_t ev;
    for (int i=0; i<eventCount; i++) {

        jack_midi_event_get(&ev, portBuf, i);

        if (ev.buffer[0] == MIDI_NOTE_ON_CHAN1) { // only record note-on events
            clock_gettime(CLOCK_MONOTONIC, &t);
            times[idx] = t;
            idx++;
        }

        if (idx == ntrials) { // we're done: output the log, clean up and exit
            for (idx=0; idx<ntrials; idx++) {
                t = times[idx];
                printf("%.8f\n", t.tv_sec + t.tv_nsec/1e9);
            }
            free(times);
            exit(0);
        }

    }

    return 0;

}

int main(int argc, char **argv) {

    if (argc > 1) {
        ntrials = atoi(argv[1]);
    } else {
        ntrials = DEFAULT_NTRIALS;
    }

    times = (struct timespec*) malloc(ntrials*sizeof(struct timespec));

    jackClient = jack_client_open("rxTiming", JackNullOption, NULL);

	jack_set_process_callback(jackClient, _jack_callback, NULL);

    jackPortIn = jack_port_register(jackClient, "in1", JACK_DEFAULT_MIDI_TYPE,
                                            JackPortIsInput, 0);
    if (jackPortIn == NULL) {
        fprintf (stderr, "could not register jack port\n");
    }

	if (jack_activate(jackClient)) {
		fprintf (stderr, "cannot activate client");
	}

    while(1) {
        usleep(1000);
    }

    free(times);
    return 0;

}

