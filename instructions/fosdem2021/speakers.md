*** WORK IN PROGRESS. PLEASE CHECK BACK OFTEN OR SUBSCRIBE TO THE CHANGES! ***
# FOSDEM 2021 video: speakers manual

In the below document, we'll assume that your talk's unique event id in the FOSDEM system is 123456 , and accessible at:
- https://penta.fosdem.org/submission/FOSDEM21/event/123456
- https://penta.fosdem.org/event/edit/123456

## Before FOSDEM 2021
### Talk video recordings
Here's what you'll need to do to get your talk video in:
- Submit your prerecorded video through https://penta.fosdem.org/submission/FOSDEM21/event/123456 .
- Your room manager will then review your talk.
- Make sure your room ends up marked with state "done" at https://upload.video.fosdem.org/overview .
- Validate your final video using the link at the bottom of https://penta.fosdem.org/submission/FOSDEM21/event/123456 ![penta submission Final Video URL](final_video_url.png). This is what will be broadcast at FOSDEM 2021. In case this looks good, no feedback is needed from you. In case of any issues, please contact [video@fosdem.org](mailto:video@fosdem.org) . Hints:
  - Never share this link. Share your talk's unique event id.
  - Particularly check the end of the video. Make sure FOSDEM has the full recording.

### Talk Q&A: audience interaction using Matrix/Jitsi
After your talk has been broadcast as prerecorded video, you will have a chance to address your audio's questions in a live broadcast q&a session. FOSDEM 2021 will use https://chat.fosdem.org for that.

**Note:** This is a **matrix server with FOSDEM specific enrichments** only available using the **https://chat.fosdem.org web client. As a speaker, please do not use any other matrix client.**

Please prepare well beforehand for the q&a session to go smoothly:
- Make sure you have access to a comfortably large screen. >= 24" screen size and >= 1920x1080 resolution would be comfortable. Things will work on a 12" 1366x768 laptop screen, but usability will suffer. Juggling an outgoing video stream, chat messages and a question scoreboard on a small screen is not fun.
- Accept your https://chat.fosdem.org invite. Create your matrix account on https://chat.fosdem.org .
  - Potential spam issue with gmail.

- Join the backstage matrix room for your talk: [#talk-123456:fosdem.org](https://chat.fosdem.org/#/room/#talk-123456:fosdem.org)
    - This room is invite only. It's accessible only to you as a speaker, your optional co-speakers, your q&a session host and FOSDEM staff.
    - You should have received an invitation by email. In case you have trouble getting in, any FOSDEM staff should be able to invite you here.
    - TODO You'll have to explicitly accept 
- Join the general audience room for your talk.
    - You should have received an invitation to this room.
    - Alternatively, you can derive your matrix room from the [schedule](https://fosdem.org/2021/schedule/events/). Examples: D.cloud => [#cloud:fosdem.org](https://chat.fosdem.org/#/room/#cloud:fosdem.org), M.misc => [#misc:fosdem.org](https://chat.fosdem.org/#/room/#misc:fosdem.org) .
  
### Help! Something is wrong. Whom do I contact?
- For issues regarding https://upload.video.fosdem.org , please email [video@fosdem.org](mailto:video@fosdem.org). You may also be able to reach wouter live in the [#video:fosdem.org](https://chat.fosdem.org/#/room/#video:fosdem.org) matrix room.
- For issues regarding matrix, please email [experience@fosdem.org](mailto:experience@fosdem.org) . You may also be able to reach other speakers and the FOSDEM team live in the [#speakers:fosdem.org](https://chat.fosdem.org/#/room/#speakers:fosdem.org) matrix room.
  
## During FOSDEM 2021
Your talk is happens in three stages:
1. Your prerecorded video is broadcast.
2. You can answer audience questions during q&a.
3. You can speak to the super interested fraction of your audience in the hallway track.

### 1. Prerecorded talk video broadcast
Did you follow the steps outlined under "Before FOSDEM 2021"? Then your talk will be broadcast at the [scheduled](https://fosdem.org/2021/schedule/events/) time, the FOSDEM audience will see a 30 seconds preroll slide, followed by your talk. These videos will be available in the following places:
- https://fosdem.org : integrated into the page for your track.
- https://live.fosdem.org/watch/<track> (example: https://live.fosdem.org/watch/dcollab) 
- the FOSDEM matrix room for your talk (example: [https://chat.fosdem.org/#/room/#misc:fosdem.org](https://chat.fosdem.org/#/room/#misc:fosdem.org)
- (most of) the FOSDEM apps available at https://fosdem.org/2021/schedule/mobile/

Be in your talk's backstage room ([https://chat.fosdem.org/#/room/#talk-123456:fosdem.org](https://chat.fosdem.org/#/room/#talk-123456:fosdem.org) at the start of your talk's broadcast.

As soon as your prerecorded talk is being broadcast,  immediately join the embedded jitsi conference in your backstage room. You talk broadcast will switch over to that after the end of your prerecorded talk. 

Monitor your track's public room for interesting general audience questions and think of intelligent answers. **Hints**:
  - Use the scoreboard widget. It gathers popular upvoted questions from the public room.
  - Enlist the help of your backstage room host. (S)he is there to help you!

**IMPORTANT: How to know exactly when your q&a session goes live?**
- A bot in the room will warn you when your q&a is to go live.
- To be 200% sure, calculate your q&a start time yourself. Example:
  - Your scheduled start wall clock time is 10:00:00 am.
  - Add 30 s for a preroll (title) slide. 10:00:30 am.
  - Add the length of your talk video. Let's say it's 17:32 long.
  - Your q&a starts at 10:18:02 am.
- **Do not rely on the public video stream** to decide when to start speaking live. Due to mixing, buffering, there is a time delta between seeing on the public stream and starting your q&a video. You don't want to keep your audience waiting between your talk and the q&a!

### 2. Answering audience questions during q&a
You now have the opportunity to answer audience questions in a q&a session.

**Hints:**
  - Use your talk host's help. (S)he can keep an eye on audience feedback from the public room chat.
  - When your time is up, your talk will automatically switch over to the next talk. You may want to keep an eye on the clock and invite super interested people into a hallway track (see "Hallway track" below).

### 3. Hallway track
Think of this as a minority of the audience clustering around the speaker for an informal chat in the hallway after the talk has ended.

Once the live q&a is over, your backstage room will open up to the general audience. Audience members can then come and talk to you.

If you want to make sure your audience finds its way to this hallway track, make some publicity around it near the end of your q&a session. Example: "Any further questions? Would you like to speak to me? Join me now in matrix room #talk-123456 for an interactive video chat.".

### Help! Something is wrong. Whom do I contact?
You can reach the FOSDEM team in the [#speakers:fosdem.org](https://chat.fosdem.org/#/room/#speakers:fosdem.org) matrix room.

## After FOSDEM 2021
When agreeing to speak at FOSDEM, you explicitly granted FOSDEM vzw the right to publish your video under a CC BY-SA license. Your video will be uploaded to the FOSDEM video archive at https://video.fosdem.org .

### Help! Something is wrong. Whom do I contact?
- For issues regarding your video at https://video.fosdem.org , please email [video@fosdem.org](mailto:video@fosdem.org) .
- For issues regarding the https://video.fosdem.org site in general, please email both [video@fosdem.org](mailto:video@fosdem.org) and [server@fosdem.org](mailto:server@fosdem.org) .
