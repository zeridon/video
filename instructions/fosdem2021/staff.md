# FOSDEM 2021 video and matrix: staff manual

## Before FOSDEM 2021

### Infodesk: Github issues
- Make sure your github account has access to the private [FOSDEM infodesk repo](https://github.com/FOSDEM/infodesk/issues/). Ask for access in #staff:fosdem.org .

### Chat.fosdem.org account
- Accept your https://chat.fosdem.org invite. Create your matrix account on https://chat.fosdem.org .
  - Attention: Potential spam issue with gmail.

### Channel subscribes
- Subscribe to the following channels:
  - #devroom-managers:fosdem.org . This is our highest priority channel for supporting.
  - #general:fosdem.org . No explanation needed.
  - #infodesk:fosdem.org . This is the conference's main virtual infodesk.
  - ~~#moderation:fosdem.org . This is obviously where the moderators are.~~
  - #speakers:fosdem.org . This is where we will help the speakers.
  - #staff:fosdem.org . This is where we coordinate between staff. (aka FIT)
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

### Invite a speaker into her invite-only q&a room
As staff, you have the ability to manually invite speakers into invite only q&a rooms, but only when you are in #missioncontrol:fosdem.org .

You'll need access to https://penta.fosdem.org to be able to verify things. Ask agk and johanvdw, possibly Gerry.

**DO NOT inviting a speaker into their invite-only q&a room without checking the following in penta:** 
  - Is their matrix id set? If not, ask them to enter their matrix id into their personal penta profile before doing anything.
  - Are they really speaking at the talk in question? Check the event id. You'll need it to invite them anyway.

The room you need to invite the speaker to is #talk-<penta_event_id>:fosdem.org . Example: #talk-11790:fosdem.org .

To manually invite a speaker into their invite-only talk room:

```#!conference inviteto #talk-11077:fosdem.org @claire.dross:fosdem.org```

If the bot isn't there, that doesn't work. In that case, use the normal invite mechanism:
```/invite @shin.ice:fosdem.org```

### Kick and ban someone from a public room
- Do not kick or ban directly. Either use the bot (see the chapter about syntax below) or report in #moderation:fosdem.org .

## Syntax for the bots
Much of the conference plumbing is run by two bots: mjolnir and FOSDEM .

### Mjolnir
https://github.com/matrix-org/mjolnir/blob/master/docs/moderators.md lists the basic commands.

Full bot syntax:
<pre>!mjolnir help
Mjolnir help:

!mjolnir                                                            - Print status information
!mjolnir status                                                     - Print status information
!mjolnir ban <list shortcode> <user|room|server> <glob> [reason]    - Adds an entity to the ban list
!mjolnir unban <list shortcode> <user|room|server> <glob> [apply]   - Removes an entity from the ban list. If apply is 'true', the users matching the glob will actually be unbanned
!mjolnir redact <user ID> [room alias/ID] [limit]                   - Redacts messages by the sender in the target room (or all rooms), up to a maximum number of events in the backlog (default 1000)
!mjolnir redact <event permalink>                                   - Redacts a message by permalink
!mjolnir kick <user ID> [room alias/ID] [reason]                    - Kicks a user in a particular room or all protected rooms
!mjolnir rules                                                      - Lists the rules currently in use by Mjolnir
!mjolnir sync                                                       - Force updates of all lists and re-apply rules
!mjolnir verify                                                     - Ensures Mjolnir can moderate all your rooms
!mjolnir list create <shortcode> <alias localpart>                  - Creates a new ban list with the given shortcode and alias
!mjolnir watch <room alias/ID>                                      - Watches a ban list
!mjolnir unwatch <room alias/ID>                                    - Unwatches a ban list
!mjolnir import <room alias/ID> <list shortcode>                    - Imports bans and ACLs into the given list
!mjolnir default <shortcode>                                        - Sets the default list for commands
!mjolnir deactivate <user ID>                                       - Deactivates a user ID
!mjolnir protections                                                - List all available protections
!mjolnir enable <protection>                                        - Enables a particular protection
!mjolnir disable <protection>                                       - Disables a particular protection
!mjolnir rooms                                                      - Lists all the protected rooms
!mjolnir rooms add <room alias/ID>                                  - Adds a protected room (may cause high server load)
!mjolnir rooms remove <room alias/ID>                               - Removes a protected room
!mjolnir move <room alias> <room alias/ID>                          - Moves a <room alias> to a new <room ID>
!mjolnir directory add <room alias/ID>                              - Publishes a room in the server's room directory
!mjolnir directory remove <room alias/ID>                           - Removes a room from the server's room directory
!mjolnir alias add <room alias> <target room alias/ID>              - Adds <room alias> to <target room>
!mjolnir alias remove <room alias>                                  - Deletes the room alias from whatever room it is attached to
!mjolnir resolve <room alias>                                       - Resolves a room alias to a room ID
!mjolnir shutdown room <room alias/ID>                              - Uses the bot's account to shut down a room, preventing access to the room on this server
!mjolnir powerlevel <user ID> <power level> [room alias/ID]         - Sets the power level of the user in the specified room (or all protected rooms)
!mjolnir help                                                       - This menu
</pre>

There are some undocumented shortcuts, but the critical thing to remember is that it matches * as "any character". So if you ban @travis:* then everyone with a username of travis will be banned. This extends to * on its own - this will destroy all of the rooms irrevocably.



### Conference bot

#### General:

```!conference help```   - This menu.
```!conference build```  - Builds the basic conference structure needed to prepare the rest of the conference. This is based off the bot's config.

#### People management:

```!conference verify <aud>```  - Dumps information about who would be invited to which rooms when the invite command is run for the auditorium.
```!conference invite [aud]```  - Issues invites to all the people to their relevant rooms. If an [aud] is supplied, only that auditorium will receive invites.
```!conference permissions```   - Updates moderator status for everyone that is supposed to have it.

#### Bridge management:

```!conference plumb-irc all```               - Plumbs all auditoriums into IRC channels.
```!conference plumb-irc <channel> <room>```  - Plumbs an IRC channel into a given room.

#### General management:

```!conference inviteme <room>```         - Asks the bot to invite you to the given room.

```!conference inviteto <room> <user>```  - Asks the bot to invite the given user to the given room.

```!conference widgets <aud>```           - Creates all widgets for the auditorium and its talks.


## After FOSDEM 2021
