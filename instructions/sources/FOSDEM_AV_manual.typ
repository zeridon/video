// FOSDEM AV Manual - Typst conversion
#import "@preview/tablex:0.0.8": tablex

#set document(
  title: "FOSDEM AV Manual",
  author: "FOSDEM Video",
)

#set page(
  margin: (top: 2cm, bottom: 4cm, left: 2cm, right: 2cm),
  header: [
    #grid(
      columns: (auto, 1fr),
      gutter: 1em,
      [
        #image("logo-gear.pdf", width: 3em)
        #text(size: 8pt)[FOSDEM AV Manual \ Version: #datetime.today().display()]
      ],
      [],
    )
  ],
  footer: [
    #text(size: 8pt)[Version: #datetime.today().display()]
    #h(1fr)
    #context text(size: 8pt)[Page #counter(page).display() of #counter(page).final().first()]
  ],
)

#set heading(numbering: "1.1.1.1")

#set par(justify: true)

// Title page
#align(center)[
  #text(size: 14pt)[FOSDEM AV Manual]

  #text(size: 16pt)[FOSDEM Video]

  #v(4em)

  #datetime.today().display()

  #v(8em)

  #image("logo-gear.pdf", width: 80mm)

  #v(1em)

  #text(size: 24pt, weight: "bold")[FOSDEM AV Manual]
]

#pagebreak()

#outline(depth: 4, indent: 1em)

#pagebreak()

= People

Video is a big task, so there are many people working together to make it all
happen. Here's all the teams:

== AW, H, K, U and J teams

You should be a team of at least three per building: AW, H, K, U respectively.
J has a dedicated knowledgeable volunteer.

Video coordination happens through the following channels:

- Fixed telephony - phone number 200 calls the NOC.
- Fixed telephony - phone number 2XX calls the closest VOC.
- Fixed telephony - you'll have a phone directory for with phones for all rooms
  and VOCs.
- Matrix - \#video-backstage:fosdem.org is the general channel for announcements
  and general issues.
- Matrix - \#video:fosdem.org is the general channel for visitors, online
  viewers, etc. for reporting issues and asking questions.
- Matrix - there will be separate per-building Matrix rooms for discussions
  about the building, sound checks, etc.
- Matrix - there are the standard channels for devroom-managers, volunteers and
  volunteers-backstage, where people also report issues.

For invites to all to the matrix channels, please contact the NOC people to
invite you.

Your tasks before the conference starts:

- (Friday) take the equipment to the rooms in your building
- (Friday) work from the biggest to the smallest room
- (Friday) do basic setup: cam, sound, plug in cables, basic audio checks with
  microphones, ... See below for details.
- (days of the conference) ensure the rooms are ready before the first talk
  starts

During the day, you'll have a fixed spot in the building. The below spots
should also appear in https://nav.fosdem.org.

- AW: AW.1125
- K: Floor 4 between K.4401 and K.4201
- H: room H.2111
- UB: room UB4.228

Your job during the conference, with the backup from the VOC team, is to do
the following in your building:

- monitor video and update scene if necessary. See the "Monitoring and control
  of video streams" section for more details;
- assist speakers and respond to problem reports in the building;
- proactively fix problems with video. In some rooms, this includes
  preventatively replacing batteries!

== Video operations control or VOC

You are in the NOC in the K building or in the VOC of a building.

Your job is to constantly monitor all the equipment and streams for problems,
and to arrange fixes for any that occur. You have visual monitoring of all
audio streams.

You have methods for contacting all relevant parties. The preferred one for
issues that require quick reaction is the stationary phone to call the relevant
people, or in person, if they're in your VOC.

- monitor video and update scene if necessary. See the "Monitoring and control
  of video streams" section for more details;
- monitor matrix channels for problem reports;
- answer the phone in the VOC for bug/problem reports;
- communicate with dispatch and NOC/VOCs about room-related issues -
  closing/opening rooms, etc.

Do not run out to fix problems yourselves. Delegate to the per building teams.
Maintaining contact between everyone is your main priority.

For more details on the monitoring, see "Monitoring and control of video
streams".

== In the devroom

If you are volunteering to be a camera operator inside a devroom, please:

- stay near the video equipment, keeping it safe (from people tripping over
  cables for example!)
- make sure the camera is aimed at the speaker
- monitor the devroom video/audio feeds (headphones!) for problems
- signal problems to VOC via matrix

Please do _NOT_ disconnect or turn off any equipment yourself. That is the task
of the per building team only.

= Monitoring and control of video streams

There should be the following monitoring available:

- Page with video previews of camera, slides and mix streams, with sound
  levels. It can show all rooms, or a single building. \
  This is the main tool and is available at
  https://control.video.fosdem.org/showbuilding.php;
- Grafana with audio levels of the camera's input, for all rooms and selectable
  for a set of rooms;
- Ability to stream every box's stream to check for issues in video or audio -
  this usually an `mpv` invocation;
- Control interface for the video mix, to select the scene to be shown, at \
  https://control.video.fosdem.org/ with user and password. Request access from
  NOC or your per-building video responsible person;
- (TBD) Host-level monitoring for all involved infrastructure, to see network
  outages and such.

Access to those systems is provided on Friday. Every per-building team should
have a way to see the monitoring well enough, either via the in-room beamer, or
some spare large screen.

== General overview

The `showbuilding.php` looks like this:

#figure(image("showbuilding.png", width: 170mm))

On top, you can select the buildings to see.

For each room in the building, from top to bottom:

- Room name. Its background is white if the sound levels are ok, red if there
  is no data, and yellow if the audio levels are not within the defined
  boundaries;
- Snapshot of the camera input, updated every 2--3 seconds;
- Snapshot of the slides/laptop input, updated every 2--3 seconds;
- Snapshot of the mixed stream output from the video mixer, updated every 2--3
  seconds. This is what gets sent to the viewers of the streams;
- Graph of the levels of the sound. The blue line is the microphone input, the
  green-yellow is the room ambiance level picked from the camera internal
  microphone.

The three bands on the sound levels are, from top to bottom:

- Yellow band, from 0 dBm to -14 dBm - peaking/too high;
- Green band, from -14 dBm to -30 dBm - ok;
- Red band, below -30 dBm - too quiet or missing;

The sound levels for the microphone input during a talk need to be in the
middle (green) band. It's good for the levels from the camera also to be in
that band during a talk.

== Per-room control

The per-room control looks like this:

#figure(image("control.video.png", width: 170mm))

The "room status" on top is used to set if the room is either full or not.
It's mostly for use for the devroom managers.

The 4 buttons below control the video mix:

- side-by-side presenter - picture in picture, large slides, small camera view.
  This is the default
- side-by-side slides - picture in picture, large camera, small slides view.
- fullscreen presenter - the camera view on full screen.
- fullscreen slides - the slides view on full screen.

On the right side there is a preview of the current streams, same as in
`showbuilding.php` above. Below that is a graph of the output levels, same as
described above.

Below that there's a link to a Grafana instance with all levels.

On the bottom left there is the audio mixer control. It's split in two parts -
input and output.

The inputs are the three inputs on the box, and `PC` is the analog input from
the HDMI capture card (the sound channel split from it). It carries either the
camera audio (for a cambox) or the presenter's audio from their HDMI output
(for the slides box).

The outputs are to the camera, to the room PA, and to the left/right channel of
the headphone jack (for monitoring purposes).

For each slider, there's the current setting and the level at the moment, that
should be moving in almost-real-time.

At the inputs, below the sliders there's a checkbox to select to which output
channels the input channel gets sent.

= Rooms

We have 30 rooms: 13 small, 15 large and 2 extra large rooms.

For the extra-large rooms (Janson, K.1105) we use ULB's audio for both input
(microphones) and output (PA).

For the large rooms, we use the room's PA and our own microphones.

For the remaining rooms, we provide our own PA and microphones.

- AW: AW1120 (S), AW1121 (S)
- K: K1105 (XXL), K3201 (S), K3401 (S), K3601 (S), K4201 (S), K4401 (S),
  K4601 (S)
- H: H1301 (L), H1302 (L), H1308 (L), H1309 (L), H2213 (S), H2214 (S),
  H2215 (L)
- UA: UA2214 (L), UA2118 (L), UA2220 (L), UB2147 (S), UB2252A (L)
- UB4: UB4132 (S), UB4136 (S), UB5132 (L), UB5230 (L)
- UD: UD2120 (L), UD2208 (L), UD2218A (L)
- UD6: UD6215 (L)
- J: Janson (XXL), J.1106 (S, spare)

Every room has one gray box with the equipment needed to setup the room. The
box is labeled with the room number and includes a checklist with all equipment
inside and a checklist for the setup.

The checklist is the main pointer on how to setup the room. There's a copy
below without the room-specific details for where the cable runs are and the
camera placement.
#pagebreak()

#include("FOSDEM_Room_setup_checklist.typ")

== Small rooms

These have a projector and a tie pin microphone for the speaker. Audience
questions must be repeated by the lecturer to be recorded properly.

A loudspeaker is also connected to amplify the lecturer for the room.

The connections there are as follows:

- Network cable (video VLAN) to the presenter box (any port)
- Network cable from the presenter to camera box (any port, one on each box)
- Camera to AC power
- Microphone receiver for the speaker microphone to channel IN 3 of the mixer
  of the presenter's videobox
- XLR cable from the OUT 1 channel of the audio mixer of the presenter's
  videobox to channel 1 (LEFT) of the camera
- XLR cable from the OUT 2 channel of the audio mixer of the presenter's
  videobox to our loudspeaker
- USB power bank to the microphone receiver
- HDMI from the camera to the HDMI IN port of the video box
- HDMI cable from the presenter box HDMI OUT to the beamer in the room (if the
  beamer is HDMI)
- HDMI cable from the speaker's laptop to the HDMI IN port of the presenter box

#pagebreak()

=== Cabling diagram

#figure(
  rotate(-90deg, reflow: true, image("../../graph/cabling_small_rooms.png", width: 200mm)),
)

#pagebreak()

== Large rooms

These have a projector, a tie pin mic for the speaker and an audience
microphone. They use the Sony HXR-NX100 camera. For the rooms that don't have
a PA, there's also a dedicated loudspeaker.

The connections there are as follows:

- Network cable (video VLAN) to the presenter box (any port)
- Network cable from the presenter to camera box (any port, one on each box)
- Camera, to AC power
- Microphone receiver for the speaker microphone to channel IN 3 of the mixer
  of the presenter's videobox
- Microphone receiver for the audience microphone to channel IN 2 of the mixer
  of the presenter's videobox
- XLR cable from the OUT 1 channel of the audio mixer of the presenter's
  videobox to channel 1 (LEFT) of the camera
- XLR cable from the OUT 2 channel of the audio mixer of the presenter's
  videobox to the room PA
- USB for charging from the presenter's videobox charging ports to the
  receivers in the mixer of the presenter's videobox
- HDMI from the camera to the HDMI port of the camera videobox
- HDMI cable from the presenter's video box HDMI OUT to the beamer in the room
  (if the beamer is HDMI)
- HDMI cable from the speaker's laptop to the HDMI IN port of the presenter's
  videobox

#pagebreak()

=== Cabling diagram

#figure(
  rotate(-90deg, reflow: true, image("../../graph/cabling_large_rooms.png", width: 200mm)),
)

#pagebreak()
== Extra large rooms

It has a projector, and all audio is handled by ULB. They use the Sony
HXR-NX100 camera.

The connections there are as follows:

- Network cable (video VLAN) to the presenter box (any port)
- Network cable from the presenter to camera box (any port, one on each box)
- Camera, to AC power
- XLR cable from ULB's audio mixer to channel 1 (LEFT) of the camera
- XLR cable from the OUT 2 channel of the audio mixer of the presenter's
  videobox to the room PA
- HDMI from the camera to the HDMI port of the camera videobox
- HDMI cable from the presenter's video box HDMI OUT to the beamer in the room
- HDMI cable from the speaker's laptop to the HDMI IN port of the presenter's
  videobox

#pagebreak()

=== Cabling diagram

#figure(
  rotate(-90deg, reflow: true, image("../../graph/cabling_xxl_rooms.png", width: 200mm)),
)
#pagebreak()

== Packing and storing equipment

Each room has its designated video gear box for storing all non-rented
equipment. Follow this sequence for efficient packing:

+ Position the videoboxes vertically in one corner of the box
+ Place the small Peli case (typically containing tie pin mic) vertically next
  to the videoboxes
+ Position the large Peli case (typically containing hand mic) on the opposite
  side of the videoboxes
+ Add the videobox power supply units
+ Fill remaining spaces between and above with other equipment

_Note_: Ensure each Peli case, videobox and laptop is returned to its original
box, matching the IDs on the equipment with those listed in the box's checklist.

#figure(image("per_room_video_box_filled.jpg", width: 120mm))

= FOSDEM video boxes

The FOSDEM video box will take care of the streaming and recording. There is no
need to operate the controls on the camera (once on and in the correct video
mode, which the setup team will have done). The setup team should also have
connected the following:

- at least one network cable
- a power cable, connected to mains, with the box already turned on
- slides boxes (the one for the speaker) only:
  - The right HDMI connection should be connected to the projector (HDMI loop
    out)
  - The left HDMI connection should have a loose HDMI cable, for connecting to
    the presenter laptop (HDMI in)
- Cam boxes only:
  - An HDMI cable to the (powered on) camera

Order of connections and powering on does not matter, each order will work.
There is no need to reboot the box after connections have changed. Fully
booting the box takes about a minute, and it should show its status on the
display, which every few seconds is replaced with the video input it receives.

_Do not attempt to power off the box unassisted, as this may damage the
integrity of the system._ If you suspect it may be malfunctioning and there is
not enough diagnostic information, contact the control and monitoring team (see
chapter "During the event" for full details). They may already be aware of the
problem, but quick reporting helps cut down on reaction times.

While the box contains a network switch (all four ports are connected), _do not
connect your own equipment_ to the box. The boxes are on a special subnet with
reserved bandwidth for the video streaming, and any other equipment may
compromise the quality of the broadcast.

_The boxes have only HDMI input and HDMI output._ For lecturers with only VGA
outputs, the per-building video team is required to ask them for their time
machine license registration. Mini-DP and some other connectors might be
available with the per-building team. The HDMI signal is automatically scaled
to 1080p (1920×1080) at 50Hz. Matching this on the presenter laptop is a good
idea, but not a requirement.

_The display on the box will show all vital information about the current status
of the box._ It shows a snapshot of the stream video, replaced with signal and
its network status (connected/disconnected), the recording status (yes/no), the
streaming status (yes/no) and others every few seconds. The sides of the
display show the audio levels of the built-in audio mixer.

The boxes report all this information to control while their network status is
good, where the control and monitoring team keeps an eye on all rooms. If
something is wrong, they may send somebody your way to correct it. Please
follow the instructions (if any) of video team members. Keeping an eye on the
box vitals and correcting any problems you notice is encouraged.

= Tripod

We use the Manfrotto MVH 502. This should hopefully be self-explanatory. Please
offer feedback to VOC if that is not the case.

#pagebreak()

= Camera

FOSDEM will use one camera model: the Sony HXR-NX100.

== Standard camera settings and quick checklist

#table(
  columns: (auto, auto),
  stroke: 0.5pt,
  [Resolution], [1920×1080],
  [Refresh rate], [50p],
  [MIC-CHANNEL1 (left)], [Speaker and audience microphone],
  [MIC-CHANNEL2 (right)], [Internal microphone],
  [Power source], [Cable AND Battery],
  [Lens cover], [Remove!],
  [Camera/Tripod], [Cam must be attached to tripod plate],
)

== Camera setup for a room

=== Screw camera on mount

Screw the camera onto the tripod. Every camera has a screw hole at the bottom
that can be used for this. The plate has a distinct "point camera in this
direction" arrow, pay attention to this. The screw can be tightened by a coin
or similar object.

#figure(image("Cam00.jpg", width: 120mm))

=== Power and HDMI connectors

First plug in the battery at the back, then plug in both the HDMI and the power
cable. Both connectors can be found next to each other to the right of the
battery slot at the back. Look at the picture if you're unsure.

Do not forget to hook up the other end of the HDMI cable to the FOSDEM Video
Box and the power cable into the mains.

#figure(image("Sony01.jpg", width: 120mm))

=== Microphone

Plug the XLR cable from the audio mixer (in the slides box) output or ULB's
audio system (for J and K.1105) into Input1. This is the main audio input and
audio stream that's provided to the outside world.

#figure(image("sony_connect_xlr.jpg", width: 120mm))

=== Power on

You can find the power button on the left side of the camera (looking from
behind). Look in the bottom right corner.

#figure(image("Sony03.jpg", width: 120mm))

=== Factory default settings

Does the camera ask for a time and date? Then you can skip this section, as it
already is on factory default settings. Does the camera NOT ask for a time and
date? Then we have to reset things.

First we reset all but the picture profile settings to factory default:
Menu → "Others" (three drawers icon) → Initialize → OK.

Now we set date/time. Not important. Just click the SET button a few times to
get through this.

Then we reset picture profile 4 (the default picture profile) to factory
default:
Menu → Camera set (camera icon) → Picture profile → PP4 → Setting → Reset →
Yes.

=== Audio settings

The audio settings can only be done through the hardware switches on the
camera. Make sure to set the switches to the correct positions, as these
directly affect the availability of audio on the recordings and live streams.
Wrong settings means no audio! If unsure, verify with the image below.

#table(
  columns: (auto, auto, auto, auto, auto),
  stroke: 0.5pt,
  [*Input*], [*Left switch*], [*Middle switch*], [*Right switch*], [*Dial*],
  [Input1], [BOTTOM (Mic 48V)], [MIDDLE (EXT MIC)], [BOTTOM (MANUAL)], [5],
  [Input2], [BOTTOM (Mic 48V)], [TOP (INT MIC)], [BOTTOM (MANUAL)], [5],
)

#figure(image("sony_audio_settings.jpg", width: 120mm))

=== Audio levels

To configure the audio levels, use the following procedure for small rooms:

- Set the levels to 5 for both channels;
- For the internal camera microphone (channel 2, small rooms) talk loud near
  the camera and make sure the levels don't go over the end (using the dial);
- For channel 1 (speaker microphone) yell while wearing the microphone and make
  sure the levels don't go over the end (using the dial);

For the other (large, XXL) rooms:

- Set the levels to 5 for both channels;
- For the speaker microphone yell while wearing the microphone and make sure
  the levels don't go over the end, adjusting from the mixing console;
- For all the other microphones, talk moderately loudly while adjusting the
  microphones, making sure that they don't go over the top;
- Adjust the overall volume for the room to be audible as much as possible
  without creating feedback;
- Additionally test for feedback while moving with the microphone around the PA
  system in the room and adjust accordingly.

=== Video output configuration

The video configuration will be done through the on-screen display.

Set up like this:

Menu → 2nd icon (two arrows) → Video out → HDMI → 1080p.

#figure(image("Sony05.jpg", width: 120mm))

The resolution information displayed on the OSD relates to recording to the SD
card, which we do not use. _Ignore this text_, as the video output config is
completely separate from the recording setting on this model.

#figure(image("Sony06.jpg", width: 120mm))

For rooms with low light conditions only, press button 3 (LOWLUX) to have the
camera auto adapt to low light levels. A candle icon appears in the bottom
right corner of the OSD screen.

=== Remove the lens cover

_Do not forget to remove the lens cover._ Store it in the camera bag for safe
keeping.

#figure(image("Sony07.jpg", width: 120mm))

=== Checklist

Please check the following before leaving:

- Does CH1 on the camera display spike when you tap the (powered on) wireless
  speaker microphone?
- Does CH2 on the camera display spike when you tap the camera itself with your
  fingers?
- Turn off the wireless speaker microphone before leaving to conserve battery
  power for during the day.
- Do both video boxes say mode 1080p50 on the LCD display?
- Does the camera video box display the camera image on the LCD display?

If any of these do not work, re-check your connections and settings. Still no
luck? Contact VOC!

=== Contact control

When you have finished setup of the room, please report to VOC for a full test.
They will let you know what rooms still need attention.

= During the event

It is expected of the devroom video volunteers that they keep an eye on the
following, in order of importance:

- The wireless speaker mic is on during talks
- The wireless speaker mic is worn correctly (see below)
- The audio volume is not too low or too high (clipping is bad!)
- The camera is aimed at the speaker, _not_ the projection screen (the
  projection screen is captured separately!)
- None of the video equipment is stolen or tampered with
- The video boxes/laptops are turned on and have OK network status.

The main task is ensuring audio quality. Video quality, while important, is
only a secondary concern. A recording without video is still usable, but a
recording without audio is completely useless.

The correct way to wear a lapel mic is as follows:

- The microphone is attached at speaker's clothes near the neck, under the chin
  (centrally);
- There are no necklaces or lanyards that would touch it during the talk;
- There are no scarves or similar that cover the microphone or will touch it;
- The microphone is attached to the topmost layer of clothes (so there's
  nothing above it that would touch it);
- If there is no place where the microphone can be attached, a lanyard can be
  used for this purpose, on top of all the clothing of the speaker;
- The microphone receiver is attached to the belt of the speaker. If not
  possible, it's attached on top of a pocket;
- If the speaker has neither a belt nor pockets, he/she can hold the receiver
  in hand, or worst case scenario, it can be attached with duct tape to the
  waist (with a full loop around the waist) _(this is a joke, do not duct-tape
  speakers)_
- The speaker is notified that if he's not facing in the direction of the
  microphone (e.g. not looking straight) the audio will be less audible.

Video team members will be both monitoring remotely as well as visiting rooms
with problems. If you have questions, concerns or problems and there is no
video team member nearby, contact them in `FOSDEM Video`. If your video box
shows issues on the LCD, most likely somebody is already on their way to you.
When communicating with video team members, please mention the _room number_ as
opposed to the devroom name. Devrooms move around, room numbers stay constant.

#pagebreak()

= System infrastructure overview

#figure(
  rotate(-90deg, reflow: true, image("../../graph/overview.pdf", width: 200mm)),
)

Above is a general schema of the setup.

This section explains how the video streaming and recording works in general
for FOSDEM, to use as a helper to understanding the system and dealing with
issues.

The system's code and recipes for deployment are available in FOSDEM's GitHub
repo `infrastructure`, in the `ansible` subdirectory.

Below is a list of components (some software, some whole-system) that are the
pieces of the whole thing.

== sproxy

`sproxy` is a small piece of software available at
https://github.com/FOSDEM/sproxy and FOSDEM's Debian package repository. It's
written in C and its role is to receive a stream of bytes on `stdin` in a
ring-buffer and provide the following TCP endpoints (up to 32) to clients:

- Port 8899 - this provides the stream from the current point onward. This is
  used for normal video clients that want to access the stream as it's being
  pushed at the moment;
- Port 8898 - this provides the stream with half of what's currently in the
  buffer, to allow clients to quickly start displaying the stream. This is used
  mostly for debug purposes, as it just makes it faster to find a keyframe;
- Port 80 - this provides the stream from the current point onward, after it
  receives some HTTP headers. This was implemented for compatibility with some
  streaming devices for the 2020 edition.

The main use of `sproxy` is to allow multiple clients to access a MPEG-TS
encapsulated video (H.264, AAC) in real time without the need of any previous
setup. MPEG-TS allows this, as it's not relevant when in the stream the client
starts reading, as the encapsulation is self-synchronizing.

`sproxy` is the successor of multicast UDP running over the network, as that
proved to create hard to debug problems with even moderate packet loss (which
TCP doesn't have).

== video-box

Implemented in role `video-box`.

The `video-box` is in general a capture device that provides `sproxy` interface
from its video and audio capture, plus some monitoring functions.

In the box you can find:

- HDMI capture device, based on the MacroSilicon MS2131 chip. The two HDMI
  ports on the box are connected to it;
- A 5-port Ethernet switch;
- A 5-port audio mixer with 2 XLR outputs and 3 XLR inputs, all for line
  level;
- A power-board that handles powering all the components and provides 4 × USB-A
  power ports at 250 mW and one USB-A port that should be pass-through to the
  control board;
- A Radxa X4 board, which controls everything (a normal x86_64 single-board
  computer);
- A three-section display;

== video-voctop

Implemented in role `video-voctop`.

The `voctop` is the video mixer that fetches the streams for the camera and
presenter from a room, and provides the "finished" video stream to the
streaming and recording infrastructure. The finished stream is again presented
via `sproxy`.

The mixing is done using `voctomix` (version 1). There are three sources for
`voctomix`:

- `cam`, fetched from the box marked to be camera in the room;
- `grabber`, fetched from the box marked to be slides/presenter in the room;
- `background` that contains artwork/the year, and is the thing most forgotten
  to be updated every year.

All streams are chewed and converted exactly to what voctomix requires (raw
video, 1080p, 25fps, SAR/DAR 1:1) and via a single `ffmpeg` instance a MPEG-TS
stream that contains video streams with 720p and 1080p is provided via an
`sproxy` instance.

The reason for mixing both video streams in the same MPEG-TS stream is that the
laptop runs out of memory bandwidth if another copy of the raw stream is taken
out of `voctomix`, and this also makes the preparation of the HLS easier.

`voctomix` provides control via text protocol on port `9999` which is used by
the control server to switch the possible views/mixes of the stream:

- Full-screen camera;
- Full-screen presentation;
- Mix, large top-left presentation, small camera bottom right (the default);
- Mix, large top-left camera, small presentation bottom right;

== video-control-server

Partially implemented in role `video-control-server`. Partially, because some
of the stuff gets tweaked and updated on the running node before and during
FOSDEM.

The following tasks are handled by the control server:

- A database (with interface) of the mapping room → voctop → camerabox →
  slidesbox. This is queried from the voctops and streambackend to know where
  to get the data for a particular room;
- A Grafana instance to plot the sound levels;
- A preview page with all rooms (selectable by building) showing
  camera/slides/mix and sound levels for every room (`showbuilding.php`);
- A control interface for every room for changing the current video mix,
  controlling the audio mixers and room status (`vocto.php`). It's
  authenticated with users/passwords provided to devroom managers and VOC
  people;
- DHCP and DNS server for the video VLAN.

The majority of the traffic to the control server is the fetching of raw video
frames from the voctops, and amounts to a steady 300 Mbps. This was the initial
reason to move this node on-site.

== video-audio-parser

Implemented in role `video-audio-parser`.

The following tasks are handled by the video-audio-parser:

- An InfluxDB database with sound levels for voctops and audio mixers (called
  `ebur2`)
- Instances of `audiofetcher` that fetch data from the voctops to plot sound
  levels;

== video-streambackend

Implemented in the role `video-streambackend`.

This is a (currently) single physical server outside of ULB that fetches all
mixed video streams from the voctops, and creates:

- A HLS stream with two video (selectable) streams for viewing by end users;
- 20-minute dumps of video streams, to be processed by `SReview`

These are both created by using `ffmpeg`. The HLS stream is served via `nginx`
to the streamfrontends, and the dumps are served via either `ssh`/`sshfs` or
NFS to `sreview`.

== video-streamfrontend

Implemented in the role `video-streamfrontend`.

This is a somewhat simple caching proxy implemented with `nginx` that presents
the video streams from the streambackend to end users.

== video-streamdump

The `streamdump`'s role is to connect to all video-boxes and all voctops, to
fetch the video they provide to record it to be used for restore for
emergencies. There is usually one at ULB and one externally.

== HLS player

`web0`'s role is to host the HLS player (implemented in JavaScript) that
end-users load to play the HLS stream with. It shows the video stream for the
relevant room and allows for selecting the video quality that the users want to
see.

= Historical notes

Things done in the past that we moved away from:

== mod_nginx_rtmp

The module is nice, but has serious limitations on multi-audio/video stream
processing, strange failures, and at some point didn't have any updates or
support. It was used to push from the voctops to the streambackend. After its
removal, all video transfers became pull-based.

== multicast

Sending MPEG-TS over UDP over multicast saved bandwidth due to the multiple
consumers of every stream. But packet loss in MPEG-TS was leading to subtle
issues in `ffmpeg`'s parsing and processing and needing the restart of streams
for issues that were hard to catch.

Experiments were done with flow control (didn't help) and reliable multicast
(the libraries didn't work, or at least Vasil was unable to make them), but
nothing came out of that, so `sproxy` was born.
