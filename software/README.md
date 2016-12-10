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
If you want to realisticly fake the streaming output of a video box, that is easy!
<pre>
apt-get install youtube-dl
youtube-dl -f 22 https://www.youtube.com/watch?v=T6AEhM1GWvw -o 720p.mp4
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
* Vocto containers are in 185.175.218.64/26
* Videoboxes are in 185.175.218.128/26

### Vocto hosts

| MAC | hostname | IP |
|-----|----------|----|
| 00:23:7d:d3:6a:e8 | voctohost0 | 185.175.218.10 |
| 00:25:b3:d7:c1:b6 | voctohost1 | 185.175.218.11 |
| 18:a9:05:57:af:22 | voctohost2 | 185.175.218.12 |
| 00:23:7d:d3:6b:b4 | voctohost3 | 185.175.218.13 |
| 00:25:b3:d7:c2:5e | voctohost4 | 185.175.218.14 |
| 18:a9:05:55:e9:88 | voctohost5 | 185.175.218.15 |
| 00:23:7d:d3:6a:ec | voctohost0 ilo | 185.175.218.20 |
| 00:23:7d:d3:6b:b4 | voctohost1 ilo | 185.175.218.21 |
| 18:a9:05:57:af:26 | voctohost2 ilo | 185.175.218.22 |
| 00:23:7d:d3:6b:b8 | voctohost3 ilo | 185.175.218.23 |
| 00:25:b3:d7:c2:62 | voctohost4 ilo | 185.175.218.24 |
| 18:a9:05:55:e9:8c | voctohost5 ilo | 185.175.218.25 |

### Vocto containers

| MAC | hostname | IP |
|-----|----------|----|
| 00:16:3e:41:11:01 | vocto-aw1120 | 185.175.218.64 |
| 00:16:3e:41:11:02 | vocto-aw1121 | 185.175.218.65 |
| 00:16:3e:41:11:03 | vocto-aw1124 | 185.175.218.66 |
| 00:16:3e:41:11:04 | vocto-aw1125 | 185.175.218.67 |
| 00:16:3e:41:11:05 | vocto-aw1126 | 185.175.218.68 |
| 00:16:3e:41:11:06 | vocto-h1301 | 185.175.218.69 |
| 00:16:3e:41:11:07 | vocto-h1302 | 185.175.218.70 |
| 00:16:3e:41:11:08 | vocto-h1308 | 185.175.218.71 |
| 00:16:3e:41:11:09 | vocto-h1309 | 185.175.218.72 |
| 00:16:3e:41:11:10 | vocto-h2213 | 185.175.218.73 |
| 00:16:3e:41:11:11 | vocto-h2214 | 185.175.218.74 |
| 00:16:3e:41:11:12 | vocto-h2215 | 185.175.218.75 |
| 00:16:3e:41:11:13 | vocto-janson | 185.175.218.76 |
| 00:16:3e:41:11:14 | vocto-k1105 | 185.175.218.77 |
| 00:16:3e:41:11:15 | vocto-k3201 | 185.175.218.78 |
| 00:16:3e:41:11:16 | vocto-k3401 | 185.175.218.79 |
| 00:16:3e:41:11:17 | vocto-k4201 | 185.175.218.80 |
| 00:16:3e:41:11:18 | vocto-k4401 | 185.175.218.81 |
| 00:16:3e:41:11:19 | vocto-k4601 | 185.175.218.82 |
| 00:16:3e:41:11:20 | vocto-ua2114 | 185.175.218.83 |
| 00:16:3e:41:11:21 | vocto-ua2220 | 185.175.218.84 |
| 00:16:3e:41:11:22 | vocto-ub2252a | 185.175.218.85 |
| 00:16:3e:41:11:23 | vocto-ud2120 | 185.175.218.86 |
| 00:16:3e:41:11:24 | vocto-ud2218a | 185.175.218.87 |

### Video boxes

| MAC | hostname | IP | Multicast |
|-----|----------|----|-----------|
| ? | aw1120-slides | 185.175.218.128 | ff02::f0:001%eth0 |
| ? | aw1120-cam | 185.175.218.129 | ff02::f0:002%eth0 |
| ? | aw1121-slides | 185.175.218.130 | ff02::f0:011%eth0 |
| ? | aw1121-cam | 185.175.218.131 | ff02::f0:012%eth0 |
| ? | aw1124-slides | 185.175.218.132 | ff02::f0:021%eth0 |
| ? | aw1124-cam | 185.175.218.133 | ff02::f0:022%eth0 |
| ? | aw1125-slides | 185.175.218.134 | ff02::f0:031%eth0 |
| ? | aw1125-cam | 185.175.218.135 | ff02::f0:032%eth0 |
| ? | aw1126-slides | 185.175.218.136 | ff02::f0:041%eth0 |
| ? | aw1126-cam | 185.175.218.137 | ff02::f0:042%eth0 |
| ? | h1301-slides | 185.175.218.138 | ff02::f0:101%eth0 |
| ? | h1301-cam | 185.175.218.139 | ff02::f0:102%eth0 |
| ? | h1302-slides | 185.175.218.140 | ff02::f0:111%eth0 |
| ? | h1302-cam | 185.175.218.141 | ff02::f0:112%eth0 |
| ? | h1308-slides | 185.175.218.142 | ff02::f0:121%eth0 |
| ? | h1308-cam | 185.175.218.143 | ff02::f0:122%eth0 |
| ? | h1309-slides | 185.175.218.144 | ff02::f0:131%eth0 |
| ? | h1309-cam | 185.175.218.145 | ff02::f0:132%eth0 |
| ? | h2213-slides | 185.175.218.146 | ff02::f0:141%eth0 |
| ? | h2213-cam | 185.175.218.147 | ff02::f0:142%eth0 |
| ? | h2214-slides | 185.175.218.148 | ff02::f0:151%eth0 |
| ? | h2214-cam | 185.175.218.149 | ff02::f0:152%eth0 |
| ? | h2215-slides | 185.175.218.150 | ff02::f0:161%eth0 |
| ? | h2215-cam | 185.175.218.151 | ff02::f0:162%eth0 |
| ? | janson-slides | 185.175.218.152 | ff02::f0:201%eth0 |
| ? | janson-cam | 185.175.218.153 | ff02::f0:202%eth0 |
| ? | k1105-slides | 185.175.218.154 | ff02::f0:301%eth0 |
| ? | k1105-cam | 185.175.218.155 | ff02::f0:302%eth0 |
| ? | k3201-slides | 185.175.218.156 | ff02::f0:311%eth0 |
| ? | k3201-cam | 185.175.218.157 | ff02::f0:312%eth0 |
| ? | k3401-slides | 185.175.218.158 | ff02::f0:321%eth0 |
| ? | k3401-cam | 185.175.218.159 | ff02::f0:322%eth0 |
| ? | k4201-slides | 185.175.218.160 | ff02::f0:331%eth0 |
| ? | k4201-cam | 185.175.218.161 | ff02::f0:332%eth0 |
| ? | k4401-slides | 185.175.218.162 | ff02::f0:341%eth0 |
| ? | k4401-cam | 185.175.218.163 | ff02::f0:342%eth0 |
| ? | k4601-slides | 185.175.218.164 | ff02::f0:351%eth0 |
| ? | k4601-cam | 185.175.218.165 | ff02::f0:352%eth0 |
| ? | ua2114-slides | 185.175.218.166 | ff02::f0:401%eth0 |
| ? | ua2114-cam | 185.175.218.167 | ff02::f0:402%eth0 |
| ? | ua2220-slides | 185.175.218.168 | ff02::f0:411%eth0 |
| ? | ua2220-cam | 185.175.218.169 | ff02::f0:412%eth0 |
| ? | ub2252a-slides | 185.175.218.170 | ff02::f0:421%eth0 |
| ? | ub2252a-cam | 185.175.218.171 | ff02::f0:422%eth0 |
| ? | ud2120-slides | 185.175.218.172 | ff02::f0:431%eth0 |
| ? | ud2120-cam | 185.175.218.173 | ff02::f0:432%eth0 |
| ? | ud2218a-slides | 185.175.218.174 | ff02::f0:441%eth0 |
| ? | ud2218a-cam | 185.175.218.175 | ff02::f0:442%eth0 |

