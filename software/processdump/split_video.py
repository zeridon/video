#! /usr/bin/python

from slugify import slugify
import argparse
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
    #FIXME. Do something
    sys.exit(1)

# Get the pentabarf xml file and parse it
penta = wget.download(penta_url)
e = ET.parse(penta).getroot()
e.findall(".//event")

# Find the event with a specific id and create the videofilename from it
t=e.find(".//event[@id='"+data['event_id']+"']").find('title').text
slug_title=slugify(t)
videofilename=slug_title+'.mp4'


# Grab the file we need and give it the slugified title for a name
url = data['url'] + "?start=" + data['start'] + "&end=" + data['end']
filename =  wget.download(url,out=videofilename)

# Do all kinds of fancy preroll, postroll, postprocessing

# Throw at video.fosdem.org mirrors

