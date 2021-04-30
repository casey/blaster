# blaster

This repository an audio-reactive visuals generator. You can see samples of its output [here](https://rodarmor.com/blaster/).

It is written in C++, using a half-baked creative coding framework called `rmr`, which is terse and weird.

Check out the [justfile](justfile), which you can run with [just](https://github.com/casey/just), for how to build and run it. In short:

```
tup init
tup
./tmp/main --resolution=1080p --route=blaster
```
