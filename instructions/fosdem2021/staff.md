# FOSDEM 2021 video and matrix: staff manual

## Before FOSDEM 2021
- Accept your https://chat.fosdem.org invite. Create your matrix account on https://chat.fosdem.org .
  - Attention: Potential spam issue with gmail.
- Subscribe to the following channels:
  - #general:fosdem.org . This is 
  - #infodesk:fosdem.org . This is the conference's main virtual infodesk.
  - #speakers:fosdem.org . This is where we will help the speakers.
  - #staff:fosdem.org . This is where we coordinate betwen staff.
  - #stands:fosdem.org . This is where we will help the stand holders.
  - #missioncontrol:fosdem.org . This is the private "sudo" room. Staff and matrix people only. You'll need to be in here to moderate, invite etcetera.
  - #video:fosdem.org . This is the public room for video issues.
  - #volunteers:fosdem.org . This is the public room for volunteers.

In case you need any help, try to get into #missioncontrol:fosdem.org first. Almost everything is solvable from there. @shin.ice:fosdem.org should be able to help you get in if needed. After checking your staff credentials, obviously.

## During FOSDEM 2021
### Step into an invite-only room
As staff, you have the ability to step into most any room, but only when you are in #missioncontrol:fosdem.org .

To invite yourself to the invite-only room:

```!conference inviteme #cloud-devroom_testing:fosdem.org```

### Invite someone to an invite-only room
As staff, you have the ability to invite people into most any room, but only when you are in #missioncontrol:fosdem.org .

To invite someone else to an invite-only room:

```! conference inviteto #cloud-devroom_testing:fosdem.org @shin.ice:fosdem.org```

### Kick and ban someone from a public room
TODO

## Conference bot help

### General:

```!conference help```   - This menu.
```!conference build```  - Builds the basic conference structure needed to prepare the rest of the conference. This is based off the bot's config.

### People management:

```!conference verify <aud>```  - Dumps information about who would be invited to which rooms when the invite command is run for the auditorium.
```!conference invite [aud]```  - Issues invites to all the people to their relevant rooms. If an [aud] is supplied, only that auditorium will receive invites.
```!conference permissions```   - Updates moderator status for everyone that is supposed to have it.

### Bridge management:

```!conference plumb-irc all```               - Plumbs all auditoriums into IRC channels.
```!conference plumb-irc <channel> <room>```  - Plumbs an IRC channel into a given room.

### General management:

```!conference inviteme <room>```         - Asks the bot to invite you to the given room.

```!conference inviteto <room> <user>```  - Asks the bot to invite the given user to the given room.

```!conference widgets <aud>```           - Creates all widgets for the auditorium and its talks.


## After FOSDEM 2021
