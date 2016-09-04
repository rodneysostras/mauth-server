
nginx() {
sudo yum install -y gcc gcc-c++ pcre-devel zlib-devel make wget unzip openssl-devel libxml2-devel libxslt-devel gd-devel perl-ExtUtils-Embed GeoIP-devel gperftools-devel centos-release-scl #nginx
sudo yum install -y devtoolset-3-gcc-c++ devtoolset-3-binutils #page speed google

PS_NGX_EXTRA_FLAGS="--with-cc=/opt/rh/devtoolset-3/root/usr/bin/gcc"
cd
NPS_VERSION=1.11.33.3
wget https://github.com/pagespeed/ngx_pagespeed/archive/release-${NPS_VERSION}-beta.zip -O release-${NPS_VERSION}-beta.zip
unzip release-${NPS_VERSION}-beta.zip
cd ngx_pagespeed-release-${NPS_VERSION}-beta/
wget https://dl.google.com/dl/page-speed/psol/${NPS_VERSION}.tar.gz
tar -xzvf ${NPS_VERSION}.tar.gz  # extracts to psol/

cd
wget https://github.com/nbs-system/naxsi/archive/master.zip -O naxsi-master.zip
unzip naxsi-master.zip

#https://github.com/openresty/srcache-nginx-module
cd
SRCACHE_VERSION=0.31
wget https://github.com/openresty/srcache-nginx-module/archive/v${SRCACHE_VERSION}.zip -O srcache-nginx-module-${SRCACHE_VERSION}.zip
unzip srcache-nginx-module-${SRCACHE_VERSION}.zip

#https://github.com/openresty/memc-nginx-module
cd
MEMC_VERSION=0.17
wget https://github.com/openresty/memc-nginx-module/archive/v${MEMC_VERSION}.zip -O memc-nginx-module-${MEMC_VERSION}.zip
unzip memc-nginx-module-${MEMC_VERSION}.zip

cd
# check http://nginx.org/en/download.html for the latest version
NGINX_VERSION=1.10.1
wget http://nginx.org/download/nginx-${NGINX_VERSION}.tar.gz
tar -xvzf nginx-${NGINX_VERSION}.tar.gz
cd nginx-${NGINX_VERSION}/
./configure \
--add-module=$HOME/naxsi-master/naxsi_src \
--add-module=$HOME/srcache-nginx-module-${SRCACHE_VERSION} \
--add-module=$HOME/memc-nginx-module-${MEMC_VERSION} \
--add-module=$HOME/ngx_pagespeed-release-${NPS_VERSION}-beta \
${PS_NGX_EXTRA_FLAGS} \
--prefix=/etc/nginx \
--sbin-path=/usr/sbin/nginx \
--conf-path=/etc/nginx/nginx.conf \
--error-log-path=/var/log/nginx/error.log \
--http-log-path=/var/log/nginx/access.log \
--pid-path=/var/run/nginx.pid \
--lock-path=/var/run/nginx.lock \
--http-client-body-temp-path=/var/cache/nginx/client_temp \
--http-proxy-temp-path=/var/cache/nginx/proxy_temp \
--http-fastcgi-temp-path=/var/cache/nginx/fastcgi_temp \
--http-uwsgi-temp-path=/var/cache/nginx/uwsgi_temp \
--http-scgi-temp-path=/var/cache/nginx/scgi_temp \
--user=nginx \
--group=nginx \
--with-http_ssl_module \
--with-http_realip_module \
--with-http_addition_module \
--with-http_sub_module \
--with-http_dav_module \
--with-http_flv_module \
--with-http_mp4_module \
--with-http_gunzip_module \
--with-http_gzip_static_module \
--with-http_random_index_module \
--with-http_secure_link_module \
--with-http_stub_status_module \
--with-http_auth_request_module \
--with-http_v2_module \
--with-http_xslt_module \
--with-http_image_filter_module \
--with-http_geoip_module \
--with-http_degradation_module \
--with-http_perl_module \
--with-threads \
--with-stream \
--with-stream_ssl_module \
--with-http_slice_module \
--with-mail \
--with-mail_ssl_module \
--with-file-aio \
--with-http_v2_module \
--with-ipv6 \
--with-pcre \
--with-google_perftools_module \
--with-debug

make
sudo make install

wget https://raw.githubusercontent.com/rodneysostras/NginxINIScriptCentos/master/nginx -O /etc/init.d/nginx
#https://www.nginx.com/resources/wiki/start/topics/examples/redhatnginxinit/

sudo chkconfig --add nginx
sudo chkconfig nginx on

sudo chmod +x /etc/init.d/nginx

sudo service nginx start

sudo mkdir -p /var/www/{vhost,default,/default/log,default/public_html}
sudo mkdir -p /etc/nginx/default.d
sudo chmod 755 /var/www/*
sudo chmod 755 /etc/nginx/default.d/

restorecon -R -v /var/www/*

}
