# FOSDEM audio mixer firmware

## Building

```shell-session
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

## Flashing

```shell-session
$ teensy_loader_cli -v -w --mcu=TEENSY41 teensy_audio.hex
```
