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

### Video boxes

| MAC | hostname | IP | Multicast |
|-----|----------|----|-----------|
| ? | aw1120-slides | 185.175.218.128 | 227.0.0.1 |
| ? | aw1120-cam | 185.175.218.129 | 227.0.0.2 |
| ? | aw1121-slides | 185.175.218.130 | 227.0.1.1 |
| ? | aw1121-cam | 185.175.218.131 | 227.0.1.2 |
| ? | aw1124-slides | 185.175.218.132 | 227.0.2.1 |
| ? | aw1124-cam | 185.175.218.133 | 227.0.2.2 |
| ? | aw1125-slides | 185.175.218.134 | 227.0.3.1 |
| ? | aw1125-cam | 185.175.218.135 | 227.0.3.2 |
| ? | aw1126-slides | 185.175.218.136 | 227.0.4.1 |
| ? | aw1126-cam | 185.175.218.137 | 227.0.4.2 |
| ? | h1301-slides | 185.175.218.138 | 227.1.0.1 |
| ? | h1301-cam | 185.175.218.139 | 227.1.0.2 |
| ? | h1302-slides | 185.175.218.140 | 227.1.1.1 |
| ? | h1302-cam | 185.175.218.141 | 227.1.1.2 |
| ? | h1308-slides | 185.175.218.142 | 227.1.2.1 |
| ? | h1308-cam | 185.175.218.143 | 227.1.2.2 |
| ? | h1309-slides | 185.175.218.144 | 227.1.3.1 |
| ? | h1309-cam | 185.175.218.145 | 227.1.3.2 |
| ? | h2213-slides | 185.175.218.146 | 227.1.4.1 |
| ? | h2213-cam | 185.175.218.147 | 227.1.4.2 |
| ? | h2214-slides | 185.175.218.148 | 227.1.5.1 |
| ? | h2214-cam | 185.175.218.149 | 227.1.5.2 |
| ? | h2215-slides | 185.175.218.150 | 227.1.6.1 |
| ? | h2215-cam | 185.175.218.151 | 227.1.6.2 |
| ? | janson-slides | 185.175.218.152 | 227.2.0.1 |
| ? | janson-cam | 185.175.218.153 | 227.2.0.2 |
| ? | k1105-slides | 185.175.218.154 | 227.3.0.1 |
| ? | k1105-cam | 185.175.218.155 | 227.3.0.2 |
| ? | k3201-slides | 185.175.218.156 | 227.3.1.1 |
| ? | k3201-cam | 185.175.218.157 | 227.3.1.2 |
| ? | k3401-slides | 185.175.218.158 | 227.3.2.1 |
| ? | k3401-cam | 185.175.218.159 | 227.3.2.2 |
| ? | k4201-slides | 185.175.218.160 | 227.3.3.1 |
| ? | k4201-cam | 185.175.218.161 | 227.3.3.2 |
| ? | k4401-slides | 185.175.218.162 | 227.3.4.1 |
| ? | k4401-cam | 185.175.218.163 | 227.3.4.2 |
| ? | k4601-slides | 185.175.218.164 | 227.3.5.1 |
| ? | k4601-cam | 185.175.218.165 | 227.3.5.2 |
| ? | ua2114-slides | 185.175.218.166 | 227.4.0.1 |
| ? | ua2114-cam | 185.175.218.167 | 227.4.0.2 |
| ? | ua2220-slides | 185.175.218.168 | 227.4.1.1 |
| ? | ua2220-cam | 185.175.218.169 | 227.4.1.2 |
| ? | ub2252a-slides | 185.175.218.170 | 227.4.2.1 |
| ? | ub2252a-cam | 185.175.218.171 | 227.4.2.2 |
| ? | ud2120-slides | 185.175.218.172 | 227.4.3.1 |
| ? | ud2120-cam | 185.175.218.173 | 227.4.3.2 |
| ? | ud2218a-slides | 185.175.218.174 | 227.4.4.1 |
| ? | ud2218a-cam | 185.175.218.175 | 227.4.4.2 |

