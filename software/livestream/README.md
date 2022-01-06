# livestream

This is what is running on https://live.fosdem.org/

## Installing

- ssh into live.fosdem.org as the non-root user: <pre>ssh fosdem@web0.video.fosdem.org</pre>
- clone this repo: <pre>git clone git@github.com:FOSDEM/video.git</pre>
- change into this directory: <pre>cd video/software/livestream</pre>
- install the thing: <pre>composer install</pre>
- exit<pre>exit</pre>
- ssh into live.fosdem.org as the root user: <pre>ssh root@web0.video.fosdem.org</pre>
- symlink the web app: <pre>ln -s /home/fosdem/video/software/livestream/ /var/www/livestream</pre>
- restart nginx: <pre>service nginx restart</pre>
- exit<pre>exit</pre>
