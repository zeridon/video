#! /usr/bin/python

from PIL import Image
from PIL import ImageFont
from PIL import ImageDraw

from slugify import slugify
import argparse
import subprocess
import json
import sys
import wget
import xml.etree.ElementTree as ET 

penta_url='https://archive.fosdem.org/2016/schedule/xml'

parser = argparse.ArgumentParser()
parser.add_argument("-e", "--event", help="a json formatted file that contains what we need to process the video of a presentation at FOSDEM", required=True)
args = parser.parse_args()

with open(args.event) as event_file:
    data = json.load(event_file)

if data['needs_video_team_intervention']:
    # FIXME. Do something
    sys.exit(1)

# Get the pentabarf xml file and parse it
penta = wget.download(penta_url)
pentaparse = ET.parse(penta).getroot()
# FIXME Either keep the downloaded penta xml file and make sure it doesn't get downloaded again, or throw it out and always get a fresh one.

# Find the talk with a specific id.
talk = pentaparse.find(".//event[@id='"+data['event_id']+"']")

# Create the relevant file names for this video from the talk
title = talk.find('title').text
slug_title = slugify(title)
videobasename = slug_title
videomp4name = videobasename+ '.mp4'
videotsname = videobasename+ '.ts'
prerollbasename = 'preroll'+ slug_title
prerollimgname = prerollbasename+ '.jpg'
prerolltsname = prerollbasename+ '.ts'
print "prerolltsname is "+prerolltsname
postrollbasename = 'postroll'
postrollimgname = postrollbasename+ '.jpg'
postrolltsname = postrollbasename+ '.ts'

# Get a list of speakers from the talk
persons = [p.text for p in talk.find('persons')]
personsline = ''
for p in persons:
    personsline += p + '   '

# Grab the file we need and give it the slugified title for a name
url = data['url'] + "?start=" + data['start'] + "&end=" + data['end']
filename =  wget.download(url,out=videomp4name)

# Create custom preroll from penta metadata
img = Image.open("preroll.jpg")
draw = ImageDraw.Draw(img)
font = ImageFont.truetype("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf", 64)
draw.text((0, 0),title,(0,0,0),font=font)
draw.text((0, 100),personsline,(0,0,0),font=font)
img.save(prerollimgname)

# Throw image at ffmpeg to create a 5 second mpeg ts
subprocess.check_call(['ffmpeg', '-y', '-loop', '1' , '-i', prerollimgname, '-c:v', 'libx264', '-r', '25', '-frames:v',  '125', prerolltsname])
subprocess.check_call(['ffmpeg', '-y', '-loop', '1' , '-i', postrollimgname, '-c:v', 'libx264', '-r', '25', '-frames:v',  '125', postrolltsname])

# Concatenate preroll, video and postroll
subprocess.check_call(['ffmpeg', '-y', '-i', videomp4name, '-c', 'copy', videotsname])
concatcommand = 'ffmpeg -f mpegts -i "concat:'+prerolltsname+ '|'+ videotsname+ '|'+ postrolltsname+'" -c copy -bsf:a aac_adtstoasc '+ videobasename+ '_final.mp4'
subprocess.check_call(concatcommand, shell=True)

# Throw at video.fosdem.org mirrors

