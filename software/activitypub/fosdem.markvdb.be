server {
    listen 443 ssl;
    server_name fosdem.markvdb.be;
    ssl_certificate /etc/letsencrypt/live/fosdem.markvdb.be/fullchain.pem;
    ssl_certificate_key /etc/letsencrypt/live/fosdem.markvdb.be/privkey.pem;
    location / {
        proxy_pass http://127.0.0.1:8000;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
    }
}
