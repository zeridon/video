## Diagnostics
From ingestion to website, if things go wrong, you want to check where:
- Is the prerecorded file there?

  ```ssh root@<track>-vocto.video.fosdem.org ls -lh /mnt/video/<penta_id>.mp4```
 - if it is not , it should be on the root@validate.video.fosdem.org  /mnt/HC_Volume_15983445/orig/ 
- Is the prerecorded file a sensible length?

  ```ssh root@<track>-vocto.video.fosdem.org ffprobe /mnt/video/<penta_id>.mp4 |& grep Duration```
- Are all talks for this room properly scheduled?

  ```ssh root@<track>-vocto.video.fosdem.org systemctl list-timers```
  - if not, check penta 
- Is the output of the voctomix mixer nominal?

  ```mpv http://<track>-vocto.video.fosdem.org:8899 checks the output of the vocto mixer for the room```
- Is the public stream output nominal?

  ```mpv https://stream.fosdem.org/<track>.m3u8```

## Adding frontends
### Spin up the machines
- Get https://github.com/hetznercloud/cli and a read/write API key for the FOSDEM video project.
- Set up extra vm's:

<pre>
#! /bin/bash

for n in {11..70}
do
	hcloud server create --name streamfrontend$n.video.fosdem.org --image debian-10 --datacenter fsn1-dc14 --type cx21 --network video-int --ssh-key vk --ssh-key mark@looksaus --ssh-key gerry@fosdem.org
done
</pre>


<pre>
#! /bin/bash

for n in {11..15}
do
	hcloud server create --name streamfrontend$n.video.fosdem.org --image debian-10 --datacenter hel1-dc2 --type cx21 --network video-int --ssh-key vk --ssh-key mark@looksaus --ssh-key gerry@fosdem.org
done
</pre>




### DNS records

- generate A records

  ```hcloud server list | sed -e 's/  */ /g'|cut -d' ' -f 2,4 | sed -e 's/\(.*\) /\1\. 10800 IN A /g'|grep streamfrontend```

- generate AAAA records

  ```hcloud server list | sed -e 's/  */ /g'|cut -d' ' -f 2,5 | sed -e 's/\(.*\) /\1\. AAAA /g' | sed -e 's/\/64/1/g' | grep streamfrontend```

### Ansible deploy
- You'll need to have a recent ansible install, your key in hetzner and the secrets set up. If you don't know about this, this is probably not for you.

```ansible-playbook playbooks/site.yml --limit video-streamer-frontend -e "ansible_user=root"```
