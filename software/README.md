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
youtube-dl -f 22 https://www.youtube.com/watch?v=077UlBtrqWs -o 720p.mp4
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

| MAC | hostname | IP | Multicast | Remarks |
|-----|----------|----|-----------|---------|
| ? | aw1120-slides | 185.175.218.128 | 227.0.0.1 |
| ? | aw1120-cam | 185.175.218.129 | 227.0.0.2 |
| 02:4e:0a:41:53:d5 | aw1121-slides | 185.175.218.130 | 227.0.1.1 |
| 02:06:08:c0:ec:64 | aw1121-cam | 185.175.218.131 | 227.0.1.2 |
| 02:c3:08:81:00:17 | aw1124-slides | 185.175.218.132 | 227.0.2.1 |
|  | aw1124-cam | 185.175.218.133 | 227.0.2.2 |
| 02:c7:05:c1:ff:df | aw1125-slides | 185.175.218.134 | 227.0.3.1 |
| ? | aw1125-cam | 185.175.218.135 | 227.0.3.2 |
| 02:07:05:42:9e:60 | aw1126-slides | 185.175.218.136 | 227.0.4.1 |
| 02:06:06:41:82:58 | aw1126-cam | 185.175.218.137 | 227.0.4.2 |
| ? | h1301-slides | 185.175.218.138 | 227.1.0.1 |
| 02:0e:0a:02:02:40 | h1301-cam | 185.175.218.139 | 227.1.0.2 |
| 02:43:08:01:5f:81 | h1302-slides | 185.175.218.140 | 227.1.1.1 |
| ? | h1302-cam | 185.175.218.141 | 227.1.1.2 |
| ? | h1308-slides | 185.175.218.142 | 227.1.2.1 |
| ? | h1308-cam | 185.175.218.143 | 227.1.2.2 |
| ? | h1309-slides | 185.175.218.144 | 227.1.3.1 |
| ? | h1309-cam | 185.175.218.145 | 227.1.3.2 |
| 02:0c:02:02:6d:74 | h2213-slides | 185.175.218.146 | 227.1.4.1 |
| ? | h2213-cam | 185.175.218.147 | 227.1.4.2 |
| ? | h2214-slides | 185.175.218.148 | 227.1.5.1 |
| ? | h2214-cam | 185.175.218.149 | 227.1.5.2 |
| 02:c3:08:43:5b:43 | h2215-slides | 185.175.218.150 | 227.1.6.1 | lcd color off, bad contact? |
| ? | h2215-cam | 185.175.218.151 | 227.1.6.2 |
| ? | janson-slides | 185.175.218.152 | 227.2.0.1 |
| ? | janson-cam | 185.175.218.153 | 227.2.0.2 |
| ? | k1105-slides | 185.175.218.154 | 227.3.0.1 |
| 02:52:04:41:91:a9 | k1105-cam | 185.175.218.155 | 227.3.0.2 |
| 02:09:07:82:a4:ec | k3201-slides | 185.175.218.156 | 227.3.1.1 |
| 02:47:02:c2:33:95 | k3201-cam | 185.175.218.157 | 227.3.1.2 |
| ? | k3401-slides | 185.175.218.158 | 227.3.2.1 |
| ? | k3401-cam | 185.175.218.159 | 227.3.2.2 |
| ? | k4201-slides | 185.175.218.160 | 227.3.3.1 |
| ? | k4201-cam | 185.175.218.161 | 227.3.3.2 |
| 02:0a:07:c2:77:08 | k4401-slides | 185.175.218.162 | 227.3.4.1 |
| 02:c9:04:81:73:97 | k4401-cam | 185.175.218.163 | 227.3.4.2 |
| ? | k4601-slides | 185.175.218.164 | 227.3.5.1 |
| ? | k4601-cam | 185.175.218.165 | 227.3.5.2 |
| ? | ua2114-slides | 185.175.218.166 | 227.4.0.1 |
| ? | ua2114-cam | 185.175.218.167 | 227.4.0.2 |
| ? | ua2220-slides | 185.175.218.168 | 227.4.1.1 |
| 02:55:0b:42:3e:91 | ua2220-cam | 185.175.218.169 | 227.4.1.2 |
| 02:43:06:c2:4d:41 | ub2252a-slides | 185.175.218.170 | 227.4.2.1 |
| ? | ub2252a-cam | 185.175.218.171 | 227.4.2.2 |
| 02:83:09:03:4b:46 | ud2120-slides | 185.175.218.172 | 227.4.3.1 |
| 02:0e:07:01:d9:0c | ud2120-cam | 185.175.218.173 | 227.4.3.2 |
| ? | ud2218a-slides | 185.175.218.174 | 227.4.4.1 |
| ? | ud2218a-cam | 185.175.218.175 | 227.4.4.2 |

