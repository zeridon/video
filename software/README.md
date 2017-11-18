# Software Architecture

The software hierarchy is dictated by 2 main goals: _recording_ and _streaming_
of the video streams encoded inside the box.

## Video boxes

The video boxes are the boxes we deploy to each room. These will run ffmpeg to
grab the output from the H.264 encoders and send that to our voctocore servers.

We are currently using a "vanilla" Bananian Linux 16.04 as our base system.
Additional software is distributed and installed via Ansible.

Ultimately, we would like to move to Debian, but for the time being this will
do.

## Faking a stream from a videobox
If you want to realisticly fake the streaming output of a video box, that is
easy! Use a recent version of `youtube-dl`:
<pre>
youtube-dl -f 22 https://www.youtube.com/watch?v=DLzxrzFCyOs -o 720p.mp4
ffmpeg -re -i 720p.mp4 -c copy -f mpegts udp://227.0.0.2:9000
</pre>

Testing your stream is easy. Use either mpv:
<pre>
apt-get install mpv
mpv udp://227.0.0.2:9000
</pre>
...or ffplay (from the ffmpeg package)
<pre>
ffplay udp://227.0.0.2:9000
</pre>

## Streaming

## Addressing plan

Our dear networking team has assigned us 185.175.218.0/24. We will be using
static DHCP bindings for the boxes and vocto containers.

We will not use separate networks, but it never hurts to have some logic in your
addressing plan.

* Servers, control hosts etc. are in 185.175.218.0/26
* Vocto laptops are in 185.175.218.64/26
* Videoboxes are in 185.175.218.128/26

### Control hosts

| MAC | hostname | IP |
|-----|----------|----|
| `00:00:00:00:00:00` | streamdump0 | 185.175.218.10 |
| `00:00:00:00:00:00` | streamdump1 | 185.175.218.11 |

### Vocto laptops (a.k.a. vocotops)

| MAC | hostname | IP | Multicast |
|-----|----------|----|-----------|
| `3c:97:0e:9a:b9:d3` | vocto-aw1120 | 185.175.218.64 | 227.0.0.3 |
| `3c:97:0e:6a:08:7d` | vocto-aw1121 | 185.175.218.65 | 227.0.1.3 |
| `3c:97:0e:9a:17:5c` | vocto-ud2119 | 185.175.218.66 | 227.0.2.3 |
| `3c:97:0e:c3:9f:6c` | vocto-aw1125 | 185.175.218.67 | 227.0.3.3 |
| `3c:97:0e:9a:b9:e4` | vocto-aw1126 | 185.175.218.68 | 227.0.4.3 |
| `3c:97:0e:33:0e:26` | vocto-h1301 | 185.175.218.69 | 227.1.0.3 |
| `3c:97:0e:9a:17:6b` | vocto-h1302 | 185.175.218.70 | 227.1.1.3 |
| `3c:97:0e:b3:79:da` | vocto-h1308 | 185.175.218.71 | 227.1.2.3 |
| `3c:97:0e:9a:13:67` | vocto-h1309 | 185.175.218.72 | 227.1.3.3 |
| `3c:97:0e:9a:19:4a` | vocto-h2213 | 185.175.218.73 | 227.1.4.3 |
| `3c:97:0e:9a:1a:d6` | vocto-h2214 | 185.175.218.74 | 227.1.5.3 |
| `3c:97:0e:75:23:3e` | vocto-h2215 | 185.175.218.75 | 227.1.6.3 |
| `3c:97:0e:9a:b9:e0` | vocto-janson | 185.175.218.76 | 227.2.0.3 |
| `3c:97:0e:95:93:3f` | vocto-k1105 | 185.175.218.77 | 227.3.0.3 |
| `3c:97:0e:ae:c3:e5` | vocto-k3201 | 185.175.218.78 | 227.3.1.3 |
| `3c:97:0e:9a:0f:a2` | vocto-k3401 | 185.175.218.79 | 227.3.2.3 |
| `3c:97:0e:a6:59:8a` | vocto-k4201 | 185.175.218.80 | 227.3.3.3 |
| `3c:97:0e:97:31:c1` | vocto-k4401 | 185.175.218.81 | 227.3.4.3 |
| `3c:97:0e:b1:a1:58` | vocto-k4601 | 185.175.218.82 | 227.3.5.3 |
| `3c:97:0e:32:92:dc` | vocto-ua2114 | 185.175.218.83 | 227.4.0.3 |
| `3c:97:0e:7d:24:9e` | vocto-ua2220 | 185.175.218.84 | 227.4.1.3 |
| `3c:97:0e:ae:c6:4b` | vocto-ub2252a | 185.175.218.85 | 227.4.2.3 |
| `3c:97:0e:33:0e:5f` | vocto-ud2120 | 185.175.218.86 | 227.4.3.3 |
| `3c:97:0e:9a:bd:68` | vocto-ud2218a | 185.175.218.87 | 227.4.4.3 |
| `3c:97:0e:9a:0f:94` | vocto-spare0 |
| `3c:97:0e:95:93:28` | vocto-spare1 |
| `3c:97:0e:9a:0f:ad` | vocto-spare2 |

### Video boxes

| MAC | hostname | IP | Multicast | Remarks |
|-----|----------|----|-----------|---------|
| `02:8e:06:02:95:26` | aw1120-slides | 185.175.218.128 | 227.0.0.1 | ok |
| `02:88:09:40:dc:5a` | aw1120-cam | 185.175.218.129 | 227.0.0.2 | ok |
| `02:4e:0a:41:53:d5` | aw1121-slides | 185.175.218.130 | 227.0.1.1 | ok |
| `02:02:0a:82:05:40` | aw1121-cam | 185.175.218.131 | 227.0.1.2 |
| `02:c3:08:81:00:17` | ud2119-slides | 185.175.218.132 | 227.0.2.1 | ok |
| `02:8e:0a:02:61:82` | ud2119-cam | 185.175.218.133 | 227.0.2.2 | ok |
| `02:d7:0a:42:1d:b3` | aw1125-slides | 185.175.218.134 | 227.0.3.1 |
| `02:49:08:81:6a:b5` | aw1125-cam | 185.175.218.135 | 227.0.3.2 | ok |
| `02:07:05:42:9e:60` | aw1126-slides | 185.175.218.136 | 227.0.4.1 |
| `02:08:06:02:09:b4` | aw1126-cam | 185.175.218.137 | 227.0.4.2 | ok |
| `02:d9:08:42:05:87` | h1301-slides | 185.175.218.138 | 227.1.0.1 |
| `02:0e:0a:02:02:40` | h1301-cam | 185.175.218.139 | 227.1.0.2 | ok |
| `02:ce:09:c2:31:f3` | h1302-slides | 185.175.218.140 | 227.1.1.1 | ok |
| `02:52:04:41:91:a9` | h1302-cam | 185.175.218.141 | 227.1.1.2 | ok |
| `02:86:05:83:34:62` | h1308-slides | 185.175.218.142 | 227.1.2.1 |
| `02:46:07:c2:47:6d` | h1308-cam | 185.175.218.143 | 227.1.2.2 | ok |
| `02:43:03:02:0d:e9` | h1309-slides | 185.175.218.144 | 227.1.3.1 | ok |
| `02:12:09:03:27:08` | h1309-cam | 185.175.218.145 | 227.1.3.2 | ok |
| `02:0c:02:02:6d:74` | h2213-slides | 185.175.218.146 | 227.1.4.1 | ok |
| `02:01:0a:81:22:f4` | h2213-cam | 185.175.218.147 | 227.1.4.2 | ok |
| `02:09:03:c2:f0:64` | h2214-slides | 185.175.218.148 | 227.1.5.1 | |
| `02:86:07:41:62:7e` | h2214-cam | 185.175.218.149 | 227.1.5.2 | ok |
| `02:c3:08:43:5b:43` | h2215-slides | 185.175.218.150 | 227.1.6.1 | lcd color off, bad contact? |
| `02:07:0a:82:66:3c` | h2215-cam | 185.175.218.151 | 227.1.6.2 | ok |
| `02:c8:08:42:75:07` | janson-slides | 185.175.218.152 | 227.2.0.1 |
| `02:48:06:c1:1c:a1` | janson-cam | 185.175.218.153 | 227.2.0.2 |
| `02:43:08:01:5f:81` | k1105-slides | 185.175.218.154 | 227.3.0.1 | ok |
| `02:06:06:41:82:58` | k1105-cam | 185.175.218.155 | 227.3.0.2 | ok |
| `02:09:07:82:a4:ec` | k3201-slides | 185.175.218.156 | 227.3.1.1 |
| `02:47:02:c2:33:95` | k3201-cam | 185.175.218.157 | 227.3.1.2 | ok |
| `02:c8:06:c2:a8:37` | k3401-slides | 185.175.218.158 | 227.3.2.1 | |
| `02:08:07:81:3b:a4` | k3401-cam | 185.175.218.159 | 227.3.2.2 | ok |
| `02:92:08:81:8f:0e` | k4201-slides | 185.175.218.160 | 227.3.3.1 | ok |
| `02:07:03:42:41:d4` | k4201-cam | 185.175.218.161 | 227.3.3.2 | ok |
| `02:0a:07:c2:77:08` | k4401-slides | 185.175.218.162 | 227.3.4.1 |
| `02:c9:04:81:73:97` | k4401-cam | 185.175.218.163 | 227.3.4.2 | ok |
| `02:01:05:82:32:30` | k4601-slides | 185.175.218.164 | 227.3.5.1 |
| `02:43:06:c2:9c:85` | k4601-cam | 185.175.218.165 | 227.3.5.2 | ok |
| `02:14:04:82:f6:fc` | ua2114-slides | 185.175.218.166 | 227.4.0.1 |
| `02:57:08:c3:27:d1` | ua2114-cam | 185.175.218.167 | 227.4.0.2 | ok |
| `02:56:06:01:09:b9` | ua2220-slides | 185.175.218.168 | 227.4.1.1 |
| `02:12:0a:c2:05:60` | ua2220-cam | 185.175.218.169 | 227.4.1.2 | ok |
| `02:56:03:42:ba:91` | ub2252a-slides | 185.175.218.170 | 227.4.2.1 | ok |
| `02:c2:04:81:0a:97` | ub2252a-cam | 185.175.218.171 | 227.4.2.2 | ok |
| `02:83:09:03:4b:46` | ud2120-slides | 185.175.218.172 | 227.4.3.1 |
| `02:0e:07:01:d9:0c` | ud2120-cam | 185.175.218.173 | 227.4.3.2 | ok |
| `02:09:0b:82:98:04` | ud2218a-slides | 185.175.218.174 | 227.4.4.1 |  |
| `02:c3:09:01:6f:4f` | ud2218a-cam | 185.175.218.175 | 227.4.4.2 | ok |

#### Spares

| MAC | hostname | IP | Multicast | Remarks |
|-----|----------|----|-----------|---------|
| `02:c7:05:c1:ff:df` | temp0-slides | | | ok |
| `02:43:06:c2:4d:41` | temp1-slides | | | ok |
| `02:54:04:83:26:c1` | spare0-slides | | | tested and working, except for one network port |
| `02:02:0a:82:05:40` | spare0-cam | | | ok |
| `02:55:0b:42:3e:91` | temp1-cam | | | ok |
| `02:06:08:c0:ec:64` | temp2-cam | | | ok |
| `02:14:06:02:09:1c` | temp3-cam | | | ok |
| `02:17:0b:02:cb:fc` | temp4-cam | | | ok |


#### Staff laptops

| MAC | hostname | IP | Multicast | Remarks |
|-----|----------|----|-----------|---------|
| `3c:97:0e:15:9c:65`| dragast | | | |
| `f0:de:f1:c4:7a:b4`| looksaus | | | |
| `f0:de:f1:fe:42:09` | glottis | | | |
| `f0:de:f1:bb:1d:45` | cerberus | | | |
| `f0:de:f1:ca:b6:bc` | neter | | | |
