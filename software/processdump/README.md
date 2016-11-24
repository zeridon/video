# Simple and rather dirty script for slicing FOSDEM videos decentrally

The core idea of this experiment is to radically simplify and delegate the cutting of FOSDEM videos to the maximum extent possible.

In practice?
* At the end of both Saturday and Sunday, if everything goes well (hah!) mp4 dumps of the picture in picture streams automatically become available on dump.video.fosdem.org.
* Every talk in penta gets its own json file.
* The json files goes into a public github repo.
* The devroom managers, speakers and whoever they delegate update the json for their room or talk.
* A few processing machines regularly pull from github and process the updated files.

## Dependencies

<pre>apt-get install python-wget python-slugify</pre>

## Configuration
* Don't forget to set the penta xml url in the .py file.
* If you want to test/help develop this before the public FOSDEM video dump hosts are up, you'll want some properly indexed mp4 files on an nginx with the http mp4 module enabled. Drop by on irc.freenode.net#fosdem-video and we should be able to help.

## TODO
Lots. Just a prototype now really.
