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

    cat README.md | grep "\-voctop" | sed -e 's/`//g' | sed -e 's/ //g' | cut -d'|' -f2 | while read mac; do wol $mac; done;

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
| `` | streamdump0 | 185.175.218.10 |
| `00:0f:53:07:0a:60` | control | 185.175.218.11 |

### Voctops

| MAC | hostname | IP |
|-----|----------|----|
| `507B9D58421D` | aw1120-voctop | 185.175.218.64 |
| `507B9D38A3BC` | aw1121-voctop | 185.175.218.65 |
| `507B9D9CBB44` | aw1125-voctop | 185.175.218.66 |
| `68F728DF066F` | aw1126-voctop | 185.175.218.67 |
| `68F728DF1714` | h1301-voctop | 185.175.218.68 |
| `68F728F91950` | h1302-voctop | 185.175.218.69 |
| `68F72892B3A8` | h1308-voctop | 185.175.218.70 |
| `68F728DF046F` | h1309-voctop | 185.175.218.71 |
| `507B9D59AC85` | h2213-voctop | 185.175.218.72 |
| `68F728DAE0FE` | h2214-voctop | 185.175.218.73 |
| `507B9D9CB53A` | h2215-voctop | 185.175.218.74 |
| `68F728F90D0E` | janson-voctop | 185.175.218.75 |
| `507B9D99C63E` | k1105-voctop | 185.175.218.76 |
| `68F728DF1222` | k3201-voctop | 185.175.218.77 |
| `68F72893919C` | k3401-voctop | 185.175.218.78 |
| `68F72892AC09` | k4201-voctop | 185.175.218.79 |
| `507B9D9BDB57` | k4401-voctop | 185.175.218.80 |
| `68F728F9B614` | k4601-voctop | 185.175.218.81 |
| `68F728F9B476` | ua2114-voctop | 185.175.218.82 |
| `68F728DF15AA` | ua2220-voctop | 185.175.218.83 |
| `68F72891D5B9` | ub2147-voctop | 185.175.218.84 |
| `507B9D68C61B` | ub2252a-voctop | 185.175.218.85 |
| `507B9D9CBE47` | ub4136-voctop | 185.175.218.86 |
| `68F728FB9C6D` | ub5132-voctop | 185.175.218.87 |
| `68F728DF0D9F` | ub5230-voctop | 185.175.218.88 |
| `507B9D68C128` | ud2119-voctop | 185.175.218.89 |
| `507B9D9CB02A` | ud2120-voctop | 185.175.218.90 |
| `507B9D9CB02C` | ud2208-voctop | 185.175.218.91 |
| `507B9D68C56E` | ud2218a-voctop | 185.175.218.92 |

#### Spares

| MAC | hostname | IP |
|-----|----------|----|
| `507B9D68C125` | spare0-voctop | 185.175.218.93 |

### Video boxes

| MAC | hostname | IP | Remarks |
|-----|----------|----|---------|
| `02:88:09:40:dc:5a` | aw1120-cam | 185.175.218.128 | check |
| `02:8e:06:02:95:26` | aw1120-slides | 185.175.218.129 | check |
| `02:02:0a:82:05:40` | aw1121-cam | 185.175.218.130 | check |
| `02:4e:0a:41:53:d5` | aw1121-slides | 185.175.218.131 | check |
| `02:49:08:81:6a:b5` | aw1125-cam | 185.175.218.132 | check |
| `02:d7:0a:42:1d:b3` | aw1125-slides | 185.175.218.133 | check |
| `02:08:06:02:09:b4` | aw1126-cam | 185.175.218.134 | check |
| `02:07:05:42:9e:60` | aw1126-slides | 185.175.218.135 | check |
| `02:0e:0a:02:02:40` | h1301-cam | 185.175.218.136 | check |
| `02:d9:08:42:05:87` | h1301-slides | 185.175.218.137 | check |
| `02:52:04:41:91:a9` | h1302-cam | 185.175.218.138 | check |
| `02:ce:09:c2:31:f3` | h1302-slides | 185.175.218.139 | check |
| `02:46:07:c2:47:6d` | h1308-cam | 185.175.218.140 | check |
| `02:86:05:83:34:62` | h1308-slides | 185.175.218.141 | check |
| `02:12:09:03:27:08` | h1309-cam | 185.175.218.142 | check |
| `02:43:03:02:0d:e9` | h1309-slides | 185.175.218.143 | check |
| `02:01:0a:81:22:f4` | h2213-cam | 185.175.218.144 | check |
| `02:0c:02:02:6d:74` | h2213-slides | 185.175.218.145 | check |
| `02:86:07:41:62:7e` | h2214-cam | 185.175.218.146 | check |
| `02:09:03:c2:f0:64` | h2214-slides | 185.175.218.147 | check |
| `02:06:08:c0:ec:64` | h2215-cam | 185.175.218.148 | check |
| `02:c8:08:42:75:07` | h2215-slides | 185.175.218.149 | check |
| `02:17:0b:02:cb:fc` | janson-cam | 185.175.218.150 | check |
| `02:91:07:c2:64:9a` | janson-slides | 185.175.218.151 | check |
| `` | k1105-cam |  |  |
| `` | k1105-slides |  |  |
| `` | k3201-cam |  |  |
| `` | k3201-slides |  |  |
| `02:06:06:41:82:58` | k3401-cam | 185.175.218.156 | check |
| `02:43:08:01:5f:81` | k3401-slides | 185.175.218.157 | check |
| `02:47:02:c2:33:95` | k4201-cam | 185.175.218.158 | check |
| `02:09:07:82:a4:ec` | k4201-slides | 185.175.218.159 | check |
| `02:08:07:81:3b:a4` | k4401-cam | 185.175.218.160 | check |
| `02:c8:06:c2:a8:37` | k4401-slides | 185.175.218.161 | check |
| `02:07:03:42:41:d4` | k4601-cam | 185.175.218.162 | check |
| `02:92:08:81:8f:0e` | k4601-slides | 185.175.218.163 | check |
| `02:c9:04:81:73:97` | ua2114-cam | 185.175.218.164 | check |
| `02:08:04:02:52:50` | ua2114-slides | 185.175.218.165 | check |
| `02:43:06:c2:9c:85` | ua2220-cam | 185.175.218.166 | check |
| `02:01:05:82:32:30` | ua2220-slides | 185.175.218.167 | check |
| `02:14:06:02:09:1c` | ub2147-cam | 185.175.218.168 | check |
| `02:14:04:82:f6:fc` | ub2147-slides | 185.175.218.169 | check |
| `02:c3:09:01:6f:4f` | ub2252a-cam | 185.175.218.170 | check |
| `02:54:04:83:26:c1` | ub2252a-slides | 185.175.218.171 | check |
| `02:12:0a:c2:05:60` | ub4136-cam | 185.175.218.172 | check |
| `02:56:06:01:09:b9` | ub4136-slides | 185.175.218.173 | check |
| `02:57:08:c3:27:d1` | ub5132-cam | 185.175.218.174 | check |
| `02:83:09:03:4b:46` | ub5132-slides | 185.175.218.175 | check |
| `02:48:06:c1:1c:a1` | ub5230-cam | 185.175.218.176 | check |
| `02:56:03:42:ba:91` | ub5230-slides | 185.175.218.177 | check |
| `02:8e:0a:02:61:82` | ud2119-cam | 185.175.218.178 | check |
| `02:c3:08:81:00:17` | ud2119-slides | 185.175.218.179 | check |
| `02:0e:07:01:d9:0c` | ud2120-cam | 185.175.218.180 | check |
| `02:43:06:c2:4d:41` | ud2120-slides | 185.175.218.181 | check |
| `02:55:0b:42:3e:91` | ud2208-cam | 185.175.218.182 | check |
| `02:c7:05:c1:ff:df` | ud2208-slides | 185.175.218.183 | check |
| `02:c2:04:81:0a:97` | ud2218a-cam | 185.175.218.184 | check |
| `02:09:0b:82:98:04` | ud2218a-slides | 185.175.218.185 | check |

#### Spares

| MAC | hostname | IP | Remarks |
|-----|----------|----|---------|
| `02:07:0a:82:66:3c` | spare0-cam | 185.175.218.186 | ok (vasil) |
| `02:c3:08:43:5b:43` | spare0-slides | 185.175.218.187 | ok (vasil) |

#### Staff laptops

| MAC | hostname | IP | Multicast | Remarks |
|-----|----------|----|-----------|---------|
| `3c:97:0e:15:9c:65`| dragast | | | |
| `f0:de:f1:c4:7a:b4`| looksaus | | | |
| `f0:de:f1:fe:42:09` | glottis | | | |
| `f0:de:f1:bb:1d:45` | cerberus | | | |
| `f0:de:f1:ca:b6:bc` | neter | | | |
| `3c:97:0e:83:a5:c9` | video-team0 | | | |
| `3c:97:0e:ce:46:31` | video-team1 | | | |
| `3c:97:0e:ae:c7:h2` | video-team2 | | | |
| `3c:97:0e:bd:02:7e` | video-team3 | | | |
| `3c:97:0e:9a:17:95` | video-team4 | | | |
