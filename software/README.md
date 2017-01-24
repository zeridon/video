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

### Control hosts

| MAC | hostname | IP |
|-----|----------|----|
| ? | streamdump0 | 185.175.218.10 |
| ? | streamdump1 | 185.175.218.11 |
| ? | ? | 185.175.218.12 |
| ? | ? | 185.175.218.13 |
| ? | ? | 185.175.218.14 |
| ? | ? | 185.175.218.15 |

### Vocto laptops (a.k.a. vocotops)

| MAC | hostname | IP | Multicast |
|-----|----------|----|-----------|
| f0:de:f1:97:97:73 | vocto-aw1120 | 185.175.218.64 | 227.0.0.3 |
| f0:de:f1:b7:7d:aa | vocto-aw1121 | 185.175.218.65 | 227.0.1.3 |
| f0:de:f1:b0:bf:47 | vocto-aw1124 | 185.175.218.66 | 227.0.2.3 |
| f0:de:f1:b7:83:c8 | vocto-aw1125 | 185.175.218.67 | 227.0.3.3 |
| f0:de:f1:b7:76:2d | vocto-aw1126 | 185.175.218.68 | 227.0.4.3 |
| f0:de:f1:b7:f6:cc | vocto-h1301 | 185.175.218.69 | 227.1.0.3 |
| f0:de:f1:b7:f4:90 | vocto-h1302 | 185.175.218.70 | 227.1.1.3 |
| f0:de:f1:b7:81:12 | vocto-h1308 | 185.175.218.71 | 227.1.2.3 |
| f0:de:f1:b7:f7:8f | vocto-h1309 | 185.175.218.72 | 227.1.3.3 |
| f0:de:f1: | vocto-h2213 | 185.175.218.73 | 227.1.4.3 |
| f0:de:f1: | vocto-h2214 | 185.175.218.74 | 227.1.5.3 |
| f0:de:f1: | vocto-h2215 | 185.175.218.75 | 227.1.6.3 |
| f0:de:f1: | vocto-janson | 185.175.218.76 | 227.2.0.3 |
| f0:de:f1: | vocto-k1105 | 185.175.218.77 | 227.3.0.3 |
| f0:de:f1: | vocto-k3201 | 185.175.218.78 | 227.3.1.3 |
| f0:de:f1: | vocto-k3401 | 185.175.218.79 | 227.3.2.3 |
| f0:de:f1: | vocto-k4201 | 185.175.218.80 | 227.3.3.3 |
| f0:de:f1: | vocto-k4401 | 185.175.218.81 | 227.3.4.3 |
| f0:de:f1: | vocto-k4601 | 185.175.218.82 | 227.3.5.3 |
| f0:de:f1: | vocto-ua2114 | 185.175.218.83 | 227.4.0.3 |
| f0:de:f1: | vocto-ua2220 | 185.175.218.84 | 227.4.1.3 |
| f0:de:f1: | vocto-ub2252a | 185.175.218.85 | 227.4.2.3 |
| f0:de:f1: | vocto-ud2120 | 185.175.218.86 | 227.4.3.3 |
| f0:de:f1: | vocto-ud2218a | 185.175.218.87 | 227.4.4.3 |

### Video boxes

| MAC | hostname | IP | Multicast | Remarks |
|-----|----------|----|-----------|---------|
| 02:ce:09:c2:31:f3 | aw1120-slides | 185.175.218.128 | 227.0.0.1 | in BG
| 02:88:09:40:dc:5a | aw1120-cam | 185.175.218.129 | 227.0.0.2 |
| 02:4e:0a:41:53:d5 | aw1121-slides | 185.175.218.130 | 227.0.1.1 |
| 02:06:08:c0:ec:64 | aw1121-cam | 185.175.218.131 | 227.0.1.2 |
| 02:c3:08:81:00:17 | aw1124-slides | 185.175.218.132 | 227.0.2.1 |
| 02:08:06:02:09:b4 | aw1124-cam | 185.175.218.133 | 227.0.2.2 | in BG
| 02:c7:05:c1:ff:df | aw1125-slides | 185.175.218.134 | 227.0.3.1 |
| 02:49:08:81:6a:b5 | aw1125-cam | 185.175.218.135 | 227.0.3.2 |
| 02:07:05:42:9e:60 | aw1126-slides | 185.175.218.136 | 227.0.4.1 |
| 02:06:06:41:82:58 | aw1126-cam | 185.175.218.137 | 227.0.4.2 |
| 02:d9:08:42:05:87 | h1301-slides | 185.175.218.138 | 227.1.0.1 |
| ? | h1301-cam | 185.175.218.139 | 227.1.0.2 |
| 02:43:08:01:5f:81 | h1302-slides | 185.175.218.140 | 227.1.1.1 |
| 02:86:05:83:34:62 | h1302-cam | 185.175.218.141 | 227.1.1.2 |
| 02:0e:0a:02:02:40 | h1308-slides | 185.175.218.142 | 227.1.2.1 |
| ? | h1308-cam | 185.175.218.143 | 227.1.2.2 |
| 02:43:03:02:0d:e9 | h1309-slides | 185.175.218.144 | 227.1.3.1 |
| 02:12:09:03:27:08 | h1309-cam | 185.175.218.145 | 227.1.3.2 |
| 02:0c:02:02:6d:74 | h2213-slides | 185.175.218.146 | 227.1.4.1 |
| 02:12:0a:c2:05:60 | h2213-cam | 185.175.218.147 | 227.1.4.2 |
| 02:09:03:c2:f0:64 | h2214-slides | 185.175.218.148 | 227.1.5.1 | |
| 02:86:07:41:62:7e | h2214-cam | 185.175.218.149 | 227.1.5.2 |
| 02:c3:08:43:5b:43 | h2215-slides | 185.175.218.150 | 227.1.6.1 | lcd color off, bad contact? |
| 02:07:0a:82:66:3c | h2215-cam | 185.175.218.151 | 227.1.6.2 |
| 02:c8:08:42:75:07 | janson-slides | 185.175.218.152 | 227.2.0.1 |
| 02:48:06:c1:1c:a1 | janson-cam | 185.175.218.153 | 227.2.0.2 |
| 02:56:03:42:ba:91 | k1105-slides | 185.175.218.154 | 227.3.0.1 |  |
| 02:52:04:41:91:a9 | k1105-cam | 185.175.218.155 | 227.3.0.2 |
| 02:09:07:82:a4:ec | k3201-slides | 185.175.218.156 | 227.3.1.1 |
| 02:47:02:c2:33:95 | k3201-cam | 185.175.218.157 | 227.3.1.2 |
| 02:c8:06:c2:a8:37 | k3401-slides | 185.175.218.158 | 227.3.2.1 | |
| ? | k3401-cam | 185.175.218.159 | 227.3.2.2 |  |
| 02:92:08:81:8f:0e | k4201-slides | 185.175.218.160 | 227.3.3.1 |
| 02:07:03:42:41:d4 | k4201-cam | 185.175.218.161 | 227.3.3.2 |
| 02:0a:07:c2:77:08 | k4401-slides | 185.175.218.162 | 227.3.4.1 |
| 02:c9:04:81:73:97 | k4401-cam | 185.175.218.163 | 227.3.4.2 |
| 02:01:05:82:32:30 | k4601-slides | 185.175.218.164 | 227.3.5.1 |
| ? | k4601-cam | 185.175.218.165 | 227.3.5.2 |
| 02:14:04:82:f6:fc | ua2114-slides | 185.175.218.166 | 227.4.0.1 |
| ? | ua2114-cam | 185.175.218.167 | 227.4.0.2 |
| 02:56:06:01:09:b9 | ua2220-slides | 185.175.218.168 | 227.4.1.1 |
| 02:55:0b:42:3e:91 | ua2220-cam | 185.175.218.169 | 227.4.1.2 |
| 02:43:06:c2:4d:41 | ub2252a-slides | 185.175.218.170 | 227.4.2.1 |
| ? | ub2252a-cam | 185.175.218.171 | 227.4.2.2 |
| 02:83:09:03:4b:46 | ud2120-slides | 185.175.218.172 | 227.4.3.1 |
| 02:0e:07:01:d9:0c | ud2120-cam | 185.175.218.173 | 227.4.3.2 |
| 02:09:0b:82:98:04 | ud2218a-slides | 185.175.218.174 | 227.4.4.1 |  |
| 02:c3:098:01:6f:4f | ud2218a-cam | 185.175.218.175 | 227.4.4.2 |
| 02:c7:05:c1:ff:df | broken spare slides | n/a | n/a | bpi, lcd, network, ssd working, problem with scaler or h264 encoder? |
