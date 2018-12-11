# jack-midi-timestamp
a simple timing log for JACK MIDI events

## Build Instructions

First, install dependencies:
```
sudo apt-get install libjack-jackd2-dev
```

Then, compile with:

```
make
```

## Usage

First, start JACK. Then, run the executable:

```
./jack-midi-timestamp <ntrials>
```

Finally, connect a client with JACK MIDI out to the input of jack-midi-timestamp (in e.g. qjackctl).
The program will log ntrials events, and then print their time (in seconds) to stdout.
You may redirect output to a file for analysis:

```
./jack-midi-timestamp 1000 > log.txt
```

