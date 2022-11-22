# Software Architecture

The software hierarchy is dictated by 2 main goals: _recording_ and _streaming_
of the video streams encoded inside the box.

## Video boxes

The video boxes are the boxes we deploy to each room. These will run ffmpeg to
grab the output from the H.264 encoders and send that to our voctocore servers.

We are currently using a vanilla Debian GNU/Linux 11 as our base system.
Additional software is distributed and installed via Ansible.

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
| `d0:67:26:cc:86:56` | streamdump0 | 185.175.218.10 |
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

| MAC | hostname | IP | Remarks |
|-----|----------|----|---------|
| `02:57:08:c3:27:d1` | cam0 | 185.175.218.128 | not checked |
| `02:c9:04:81:73:97` | cam1 | 185.175.218.129 | not checked |
| `02:0e:0a:02:02:40` | cam2 | 185.175.218.130 | not checked |
| `02:48:06:c1:1c:a1` | cam3 | 185.175.218.131 | not checked |
| `02:43:06:c2:9c:85` | cam4 | 185.175.218.132 | not checked |
| `02:12:0a:c2:05:60` | cam5 | 185.175.218.133 | not checked |
| `02:55:0b:42:3e:91` | cam6 | 185.175.218.134 | not checked |
| `02:0e:07:01:d9:0c` | cam7 | 185.175.218.135 | not checked |
| `02:01:0a:81:22:f4` | cam8 | 185.175.218.136 | not checked |
| `02:c2:04:81:0a:97` | cam9 | 185.175.218.137 | not checked |
| `02:8e:0a:02:61:82` | cam10 | 185.175.218.138 | not checked |
| `02:08:06:02:09:b4` | cam11 | 185.175.218.139 | not checked |
| `02:49:08:81:6a:b5` | cam12 | 185.175.218.140 | not checked |
| `02:02:0a:82:05:40` | cam13 | 185.175.218.141 | not checked |
| `02:88:09:40:dc:5a` | cam14 | 185.175.218.142 | not checked |
| `02:07:0a:82:66:3c` | cam15 | 185.175.218.143 | not checked |
| `02:17:0b:02:cb:fc` | cam16 | 185.175.218.144 | not checked |
| `02:c3:09:01:6f:4f` | cam17 | 185.175.218.145 | not checked |
| `02:46:07:c2:47:6d` | cam18 | 185.175.218.146 | not checked |
| `02:12:09:03:27:08` | cam19 | 185.175.218.147 | not checked |
| `02:06:06:41:82:58` | cam20 | 185.175.218.148 | not checked |
| `02:14:06:02:09:1c` | cam21 | 185.175.218.149 | not checked |
| `02:07:03:42:41:d4` | cam22 | 185.175.218.150 | not checked |
| `02:52:04:41:91:a9` | cam23 | 185.175.218.151 | not checked |
| `02:08:07:81:3b:a4` | cam24 | 185.175.218.152 | not checked |
| `02:47:02:c2:33:95` | cam25 | 185.175.218.153 | not checked |
| `02:c9:08:c0:fd:47` | slides0 | 185.175.218.154 | not checked |
| `02:83:09:03:4b:46` | slides1 | 185.175.218.155 | not checked |
| `02:d9:08:42:05:87` | slides2 | 185.175.218.156 | not checked |
| `02:01:05:82:32:30` | slides3 | 185.175.218.157 | not checked |
| `02:56:03:42:ba:91` | slides4 | 185.175.218.158 | not checked |
| `02:56:06:01:09:b9` | slides5 | 185.175.218.159 | not checked |
| `02:0c:02:02:6d:74` | slides6 | 185.175.218.160 | not checked |
| `02:c7:05:c1:ff:df` | slides7 | 185.175.218.161 | not checked |
| `02:09:0b:82:98:04` | slides8 | 185.175.218.162 | not checked |
| `02:43:06:c2:4d:41` | slides9 | 185.175.218.163 | not checked |
| `02:c3:08:81:00:17` | slides10 | 185.175.218.164 | not checked |
| `02:d7:0a:42:1d:b3` | slides11 | 185.175.218.165 | not checked |
| `02:8e:06:02:95:26` | slides12 | 185.175.218.166 | not checked |
| `02:c3:08:43:5b:43` | slides13 | 185.175.218.167 | not checked |
| `02:07:05:42:9e:60` | slides14 | 185.175.218.168 | not checked |
| `02:91:07:c2:64:9a` | slides15 | 185.175.218.169 | not checked |
| `02:54:04:83:26:c1` | slides16 | 185.175.218.170 | not checked |
| `02:86:05:83:34:62` | slides17 | 185.175.218.171 | not checked |
| `02:43:03:02:0d:e9` | slides18 | 185.175.218.172 | not checked |
| `02:4e:0a:41:53:d5` | slides19 | 185.175.218.173 | not checked |
| `02:09:07:82:a4:ec` | slides20 | 185.175.218.174 | not checked |
| `02:ce:09:c2:31:f3` | slides21 | 185.175.218.175 | not checked |
| `02:92:08:81:8f:0e` | slides22 | 185.175.218.176 | not checked |
| `02:14:04:82:f6:fc` | slides23 | 185.175.218.177 | not checked |
| `02:43:08:01:5f:81` | slides24 | 185.175.218.178 | not checked |
| `02:09:03:c2:f0:64` | slides25 | 185.175.218.179 | TODO scaler dead, splitter disconnected |#### Spares

| MAC | hostname | IP | Remarks |
|-----|----------|----|---------|

#### Staff laptops

| MAC | hostname | IP | Multicast | Remarks |
|-----|----------|----|-----------|---------|
