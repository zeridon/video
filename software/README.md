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
| `3c:97:0e:97:31:c6` | streamdump0 | 185.175.218.10 |
| `3c:97:0e:8a:0c:bd` | streamdump1 | 185.175.218.11 |

### Voctops

| MAC | hostname | IP | Multicast |
|-----|----------|----|-----------|
| `28:d2:44:a7:31:fd` | aw1120-voctop | 185.175.218.64 | 227.0.0.3 |
| `28:d2:44:95:06:81` | aw1121-voctop | 185.175.218.65 | 227.0.1.3 |
| `28:d2:44:bb:4a:c5` | aw1125-voctop | 185.175.218.66 | 227.0.2.3 |
| `68:f7:28:16:83:ae` | aw1126-voctop | 185.175.218.67 | 227.0.3.3 |
| `28:d2:44:82:25:10` | h1301-voctop | 185.175.218.68 | 227.1.0.3 |
| `28:d2:44:f0:9e:69` | h1302-voctop | 185.175.218.69 | 227.1.1.3 |
| `28:d2:44:98:1a:58` | h1308-voctop | 185.175.218.70 | 227.1.2.3 |
| `28:d2:44:8d:c0:d1` | h1309-voctop | 185.175.218.71 | 227.1.3.3 |
| `28:d2:44:bb:4c:99` | h2213-voctop | 185.175.218.72 | 227.1.4.3 |
| `28:d2:44:bc:a8:ec` | h2214-voctop | 185.175.218.73 | 227.1.5.3 |
| `28:d2:44:bc:a1:b7` | h2215-voctop | 185.175.218.74 | 227.1.6.3 |
| `28:d2:44:bc:a7:3f` | janson-voctop | 185.175.218.75 | 227.2.0.3 |
| `28:d2:44:92:97:be` | k1105-voctop | 185.175.218.76 | 227.3.0.3 |
| `28:d2:44:bb:4a:d5` | k3201-voctop | 185.175.218.77 | 227.3.1.3 |
| `28:d2:44:83:f2:7d` | k3401-voctop | 185.175.218.78 | 227.3.2.3 |
| `28:d2:44:94:49:a2` | k4201-voctop | 185.175.218.79 | 227.3.3.3 |
| `28:d2:44:b9:33:e5` | k4401-voctop | 185.175.218.80 | 227.3.4.3 |
| `28:d2:44:98:18:bd` | k4601-voctop | 185.175.218.81 | 227.3.5.3 |
| `28:d2:44:66:f9:b0` | ua2114-voctop | 185.175.218.82 | 227.4.0.3 |
| `28:d2:44:ac:99:4b` | ua2118-voctop | 185.175.218.83 | 227.4.1.3 |
| `28:d2:44:4c:58:cb` | ua2220-voctop | 185.175.218.84 | 227.4.2.3 |
| `28:d2:44:67:04:4d` | ub2252a-voctop | 185.175.218.85 | 227.5.0.3 |
| `68:f7:28:4c:e0:54` | ub2147-voctop | 185.175.218.86 | 227.5.1.3 |
| `28:d2:44:82:32:be` | ud2120-voctop | 185.175.218.87 | 227.6.0.3 |
| `28:d2:44:68:9c:8a` | ud2208-voctop | 185.175.218.88 | 227.6.1.3 |
| `28:d2:44:96:18:d5` | ud2119-voctop | 185.175.218.89 | 227.6.2.3 |
| `68:f7:28:70:a3:5d` | ud2218a-voctop | 185.175.218.90 | 227.6.3.3 |

#### Spares

| MAC | hostname | IP | Multicast |
|-----|----------|----|-----------|
| `28:d2:44:a9:21:44` | spare0-voctop | 185.175.218.91 | 227.9.0.1 |

### Video boxes

| MAC | hostname | IP | Remarks |
|-----|----------|----|---------|
| `02:88:09:40:dc:5a` | aw1120-cam | 185.175.218.128 | ok |
| `02:8e:06:02:95:26` | aw1120-slides | 185.175.218.129 | ok |
| `02:02:0a:82:05:40` | aw1121-cam | 185.175.218.130 | ok |
| `02:4e:0a:41:53:d5` | aw1121-slides | 185.175.218.131 | ok |
| `02:49:08:81:6a:b5` | aw1125-cam | 185.175.218.132 | ok |
| `02:d7:0a:42:1d:b3` | aw1125-slides | 185.175.218.133 | ok |
| `02:86:07:41:62:7e` | aw1126-cam | 185.175.218.134 | ok |
| `02:07:05:42:9e:60` | aw1126-slides | 185.175.218.135 | ok |
| `02:0e:0a:02:02:40` | h1301-cam | 185.175.218.136 | ok |
| `02:d9:08:42:05:87` | h1301-slides | 185.175.218.137 | ok |
| `02:52:04:41:91:a9` | h1302-cam | 185.175.218.138 | ok |
| `02:ce:09:c2:31:f3` | h1302-slides | 185.175.218.139 | ok |
| `02:46:07:c2:47:6d` | h1308-cam | 185.175.218.140 | ok |
| `02:86:05:83:34:62` | h1308-slides | 185.175.218.141 | ok |
| `02:12:09:03:27:08` | h1309-cam | 185.175.218.142 | ok |
| `02:43:03:02:0d:e9` | h1309-slides | 185.175.218.143 | ok |
| `02:01:0a:81:22:f4` | h2213-cam | 185.175.218.144 | ok |
| `02:0c:02:02:6d:74` | h2213-slides | 185.175.218.145 | ok |
| `02:86:07:41:62:7e` | h2214-cam | 185.175.218.146 | ok |
| `02:09:03:c2:f0:64` | h2214-slides | 185.175.218.147 | ok |
| `02:06:08:c0:ec:64` | h2215-cam | 185.175.218.148 | ok |
| `02:c8:08:42:75:07` | h2215-slides | 185.175.218.149 | ok |
| `02:17:0b:02:cb:fc` | janson-cam | 185.175.218.150 | ok |
| `02:91:07:c2:64:9a` | janson-slides | 185.175.218.151 | ok |
| `02:06:06:41:82:58` | k1105-cam | 185.175.218.152 | ok |
| `02:43:08:01:5f:81` | k1105-slides | 185.175.218.153 | ok |
| `02:47:02:c2:33:95` | k3201-cam | 185.175.218.154 | ok |
| `02:09:07:82:a4:ec` | k3201-slides | 185.175.218.155 | ok |
| `02:08:07:81:3b:a4` | k3401-cam | 185.175.218.156 | ok |
| `02:c8:06:c2:a8:37` | k3401-slides | 185.175.218.157 | ok |
| `02:07:03:42:41:d4` | k4201-cam | 185.175.218.158 | ok |
| `02:92:08:81:8f:0e` | k4201-slides | 185.175.218.159 | ok |
| `02:c9:04:81:73:97` | k4401-cam | 185.175.218.160 | ok |
| `02:08:04:02:52:50` | k4401-slides | 185.175.218.161 | ok |
| `02:43:06:c2:9c:85` | k4601-cam | 185.175.218.162 | ok |
| `02:01:05:82:32:30` | k4601-slides | 185.175.218.163 | ok |
| `02:14:06:02:09:1c` | ua2114-cam | 185.175.218.164 | ok |
| `02:14:04:82:f6:fc` | ua2114-slides | 185.175.218.165 | ok |
| `02:c3:09:01:6f:4f` | ua2118-cam | 185.175.218.166 | ok |
| `02:54:04:83:26:c1` | ua2118-slides | 185.175.218.167 | ok |
| `02:12:0a:c2:05:60` | ua2220-cam | 185.175.218.168 | ok |
| `02:56:06:01:09:b9` | ua2220-slides | 185.175.218.169 | ok |
| `02:57:08:c3:27:d1` | ub2147-cam | 185.175.218.170 | ok |
| `02:83:09:03:4b:46` | ub2147-slides | 185.175.218.171 | ok |
| `02:48:06:c1:1c:a1` | ub2252a-cam | 185.175.218.172 | ok |
| `02:56:03:42:ba:91` | ub2252a-slides | 185.175.218.173 | ok |
| `02:8e:0a:02:61:82` | ud2119-cam | 185.175.218.174 | ok |
| `02:c3:08:81:00:17` | ud2119-slides | 185.175.218.175 | ok |
| `02:0e:07:01:d9:0c` | ud2120-cam | 185.175.218.176 | ok |
| `02:43:06:c2:4d:41` | ud2120-slides | 185.175.218.177 | ok |
| `02:55:0b:42:3e:91` | ud2208-cam | 185.175.218.178 | ok |
| `02:c7:05:c1:ff:df` | ud2208-slides | 185.175.218.179 | ok |
| `02:c2:04:81:0a:97` | ud2218a-cam | 185.175.218.180 | ok |
| `02:09:0b:82:98:04` | ud2218a-slides | 185.175.218.181 | ok |

#### Spares

| MAC | hostname | IP | Remarks |
|-----|----------|----|---------|
| `02:86:07:41:62:7e` | spare0-cam | 185.175.218.182 | ok (vasil) |
| `02:c3:08:43:5b:43` | spare0-slides | 185.175.218.183 | lcd color off, bad contact? (vasil) |

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
