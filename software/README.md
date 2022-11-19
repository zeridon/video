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
mpv tcp://aw1126-slides.local:8898/
</pre>
...or ffplay (from the ffmpeg package)
<pre>
ffplay tcp://aw1126-slides.local:8898/
</pre>

You can also use the IPs instead of the .local addresses.

## Waking up all voctops using the table in this README file

Quick and dirty:

    cat README.md | grep "| voctop" | sed -e 's/`//g' | sed -e 's/ //g' | cut -d'|' -f2 | while read mac; do wol $mac; done;

## Re-installing a videobox

The videoboxes will do PXE boot if they can not load an OS from the SD card.

To re-install a videobox, simply make sure it will not boot properly by nuking
the install on the SD card.

    dd if=/dev/zero of=/dev/mmcblk0 bs=512 count=1

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
| `68:f7:28:92:b7:ce` | streamdump0 | 185.175.218.10 |
| `70:85:c2:a2:d2:16` | control | 185.175.218.11 |
| `00:26:99:c4:a3:42` | voctop-sw | 185.175.218.12 |

### Voctops

| MAC | hostname | IP |
|-----|----------|----|
| `c8:5b:76:4b:fb:b8` | voctop0 | 185.175.218.64 |
| `c8:5b:76:fd:bb:72` | voctop1 | 185.175.218.65 |
| `54:e1:ad:b9:00:97` | voctop2 | 185.175.218.66 |
| `54:e1:ad:28:cf:41` | voctop3 | 185.175.218.67 |
| `54:e1:ad:e3:41:67` | voctop4 | 185.175.218.68 |
| `54:e1:ad:06:12:0c` | voctop5 | 185.175.218.69 |
| `c8:5b:76:ab:1c:0a` | voctop6 | 185.175.218.70 |
| `54:e1:ad:93:1a:0a` | voctop7 | 185.175.218.71 |
| `54:e1:ad:d6:3d:14` | voctop8 | 185.175.218.72 |
| `54:e1:ad:bd:0e:e0` | voctop9 | 185.175.218.73 |
| `54:e1:ad:b8:fc:89` | voctop10 | 185.175.218.74 |
| `54:e1:ad:f8:5b:f5` | voctop11 | 185.175.218.75 |
| `54:e1:ad:e8:33:86` | voctop12 | 185.175.218.76 |
| `54:e1:ad:f6:ac:21` | voctop13 | 185.175.218.77 |
| `54:e1:ad:e3:50:4d` | voctop14 | 185.175.218.78 |
| `54:e1:ad:e3:4c:ad` | voctop15 | 185.175.218.79 |
| `54:e1:ad:d2:7c:a2` | voctop16 | 185.175.218.80 |
| `c8:5b:76:dd:34:45` | voctop17 | 185.175.218.81 |
| `54:e1:ad:f6:aa:ff` | voctop18 | 185.175.218.82 |
| `c8:5b:76:ab:0a:49` | voctop19 | 185.175.218.83 |
| `54:e1:ad:05:70:80` | voctop20 | 185.175.218.84 |
| `c8:5b:76:19:06:0f` | voctop21 | 185.175.218.85 |
| `c8:5b:76:ab:16:5e` | voctop22 | 185.175.218.86 |
| `54:e1:ad:28:c9:a3` | voctop23 | 185.175.218.87 |
| `c8:5b:76:ab:14:3b` | voctop24 | 185.175.218.88 |
| `c8:5b:76:ab:0a:4a` | voctop25 | 185.175.218.89 |
| `c8:5b:76:ab:1f:2a` | voctop26 | 185.175.218.90 |

#### Spares

| MAC | hostname | IP |
|-----|----------|----|

### Video boxes

| MAC | hostname | new name | IP | Remarks |
|-----|----------|----------|----|---------|
| `02:88:09:40:dc:5a` | aw1120-cam | cam-14 | 185.175.218.128 | check |
| `02:8e:06:02:95:26` | aw1120-slides | slides-12 | 185.175.218.129 | check |
| `02:02:0a:82:05:40` | aw1121-cam | cam-13 | 185.175.218.130 | check |
| `02:4e:0a:41:53:d5` | aw1121-slides | slides-19 | 185.175.218.131 | check |
| `02:49:08:81:6a:b5` | aw1125-cam | cam-12 | 185.175.218.132 | check |
| `02:d7:0a:42:1d:b3` | aw1125-slides | slides-11 | 185.175.218.133 | check |
| `02:08:06:02:09:b4` | aw1126-cam | cam-11 | 185.175.218.134 | check |
| `02:07:05:42:9e:60` | aw1126-slides | slides-14 | 185.175.218.135 | check |
| `02:0e:0a:02:02:40` | h1301-cam | cam-2 | 185.175.218.136 | checked 20221119 |
| `02:d9:08:42:05:87` | h1301-slides | slides-2 | 185.175.218.137 | checked |
| `02:52:04:41:91:a9` | h1302-cam |  | 185.175.218.138 | check (vasil) |
| `02:ce:09:c2:31:f3` | h1302-slides |  | 185.175.218.139 | check (vasil) |
| `02:46:07:c2:47:6d` | h1308-cam | cam-18 | 185.175.218.140 | check (vasil) |
| `02:86:05:83:34:62` | h1308-slides | slides-17 | 185.175.218.141 | check (vasil) |
| `02:12:09:03:27:08` | h1309-cam | cam-19 | 185.175.218.142 | check |
| `02:43:03:02:0d:e9` | h1309-slides | slides-18 | 185.175.218.143 | check |
| `02:01:0a:81:22:f4` | h2213-cam | cam-8 | 185.175.218.144 | check |
| `02:0c:02:02:6d:74` | h2213-slides | slides-6 | 185.175.218.145 | check |
| `02:86:07:41:62:7e` | h2214-cam |  | 185.175.218.146 | check |
| `02:c8:06:c2:a8:37` | h2214-slides |  | 185.175.218.147 | check |
| `02:06:08:c0:ec:64` | h2215-cam |  | 185.175.218.148 | check |
| `02:c8:08:42:75:07` | h2215-slides |  | 185.175.218.149 | check |
| `02:17:0b:02:cb:fc` | janson-cam | cam-16 | 185.175.218.150 | check |
| `02:91:07:c2:64:9a` | janson-slides | slides-15 | 185.175.218.151 | check |
| `00:13:14:01:89:4b` | k1105-cam |  | 185.175.218.152 | check (vasil, chineese box) |
| `00:13:14:01:89:19` | k1105-slides |  | 185.175.218.153 | check (vasil, chineese box) |
| `00:13:14:01:89:39` | k3201-cam |  | 185.175.218.154 | check (vasil, chineese box)  |
| `00:13:14:01:63:cb` | k3201-slides |  | 185.175.218.155 | check (vasil, chineese box) |
| `02:06:06:41:82:58` | k3401-cam | cam-20 | 185.175.218.156 | check |
| `02:43:08:01:5f:81` | k3401-slides |  | 185.175.218.157 | check |
| `02:47:02:c2:33:95` | k4201-cam |  | 185.175.218.158 | check |
| `02:09:07:82:a4:ec` | k4201-slides |  | 185.175.218.159 | check |
| `02:08:07:81:3b:a4` | k4401-cam |  | 185.175.218.160 | check |
| `02:16:01:c2:00:e0` | k4401-slides |  | 185.175.218.161 | check (libv, frankenbox) |
| `02:07:03:42:41:d4` | k4601-cam |  | 185.175.218.162 | check |
| `02:92:08:81:8f:0e` | k4601-slides |  | 185.175.218.163 | check |
| `02:c9:04:81:73:97` | ua2114-cam | cam-1 | 185.175.218.164 | check |
| `02:c9:08:c0:fd:47` | ua2114-slides | slides-0 | 185.175.218.165 | check |
| `02:43:06:c2:9c:85` | ua2220-cam | cam-4 | 185.175.218.166 | check |
| `02:01:05:82:32:30` | ua2220-slides | slides-3 | 185.175.218.167 | checked 20221119 |
| `02:14:06:02:09:1c` | ub2147-cam |  | 185.175.218.168 | check |
| `02:14:04:82:f6:fc` | ub2147-slides |  | 185.175.218.169 | check |
| `02:c3:09:01:6f:4f` | ub2252a-cam | cam-17 | 185.175.218.170 | check |
| `02:54:04:83:26:c1` | ub2252a-slides | slides-16 | 185.175.218.171 | check |
| `02:12:0a:c2:05:60` | ub4136-cam | cam-5 | 185.175.218.172 | check |
| `02:56:06:01:09:b9` | ub4136-slides | slides-5 | 185.175.218.173 | checked 20221119 |
| `02:57:08:c3:27:d1` | ub5132-cam | cam-0 | 185.175.218.174 | check |
| `02:83:09:03:4b:46` | ub5132-slides | slides-1 | 185.175.218.175 | check |
| `02:48:06:c1:1c:a1` | ub5230-cam | cam-3 | 185.175.218.176 | checked 20221119 |
| `02:56:03:42:ba:91` | ub5230-slides | slides-4 | 185.175.218.177 | check |
| `02:8e:0a:02:61:82` | ud2119-cam | cam-10 | 185.175.218.178 | check |
| `02:c3:08:81:00:17` | ud2119-slides | slides-10 | 185.175.218.179 | check |
| `02:0e:07:01:d9:0c` | ud2120-cam | cam-7 | 185.175.218.180 | check |
| `02:43:06:c2:4d:41` | ud2120-slides | slides-9 | 185.175.218.181 | check |
| `02:55:0b:42:3e:91` | ud2208-cam | cam-6 | 185.175.218.182 | check |
| `02:c7:05:c1:ff:df` | ud2208-slides | slides-7 | 185.175.218.183 | check |
| `02:c2:04:81:0a:97` | ud2218a-cam | cam-9 | 185.175.218.184 | check |
| `02:09:0b:82:98:04` | ud2218a-slides | slides-8 | 185.175.218.185 | check |

#### Spares

| MAC | hostname | new name | IP | Remarks |
|-----|----------|----------|----|---------|
| `02:07:0a:82:66:3c` | spare0-cam | cam-15 | 185.175.218.186 | check |
| `02:c3:08:43:5b:43` | spare0-slides | slides-13 | 185.175.218.187 | check |
| `00:13:14:01:63:cf` | spare1-slides |  | 185.175.218.188 | check (vasil, chineese box, can also be cam) |
| `02:c8:06:c2:a8:37` | spare2-slides |  | 185.175.218.189 | check (was k4401-slides) |

#### Staff laptops

| MAC | hostname | IP | Multicast | Remarks |
|-----|----------|----|-----------|---------|
