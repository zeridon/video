#!/usr/bin/perl -w

# Dependencies: apt install libmojolicious-perl

use strict;
use warnings;
use feature "say";

use Mojo::UserAgent;

my $ua = Mojo::UserAgent->new(timeout => 10);
$ua->proxy->detect;

my $overview = $ua->get("https://upload.video.fosdem.org/api/v1/event/2/overview")->result->json;

my %rooms;
my %states;

foreach my $talk(@$overview) {
	if(!exists($rooms{$talk->{room}})) {
		$rooms{$talk->{room}} = {};
	}
	if(!exists($rooms{$talk->{room}}{$talk->{state}})) {
		$rooms{$talk->{room}}{$talk->{state}} = 1;
	} else {
		$rooms{$talk->{room}}{$talk->{state}}++;
	}
	if(!exists($states{$talk->{state}})) {
		$states{$talk->{state}} = 1;
	} else {
		$states{$talk->{state}}++;
	}
}
say "Per-room totals:";

foreach my $room(sort keys %rooms) {
	say "\t$room";
	foreach my $state(sort keys %{$rooms{$room}}) {
		say "\t\t$state: $rooms{$room}{$state}";
	}
}
say "\nGlobal totals:";
foreach my $state(sort keys %states) {
	say "\t$state: $states{$state}";
}

say "\nGlobal total of " . scalar(@$overview) . " talks";
