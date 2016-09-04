
hhvm() {
#https://infinitescript.com/2015/02/building-and-installing-hhvm-on-centos-7/
# Need to be ran under root priv or you can sudo it
# Update your CentOS first
yum update -y

# Enable the EPEL repository

yum install -y epel-release

# Install some dependencies 

yum install cpp gcc-c++ cmake3 git psmisc {binutils,boost,jemalloc,numactl}-devel \
{ImageMagick,sqlite,tbb,bzip2,openldap,readline,elfutils-libelf,gmp,lz4,pcre}-devel \
lib{xslt,event,yaml,vpx,png,zip,icu,mcrypt,memcached,cap,dwarf}-devel \
{unixODBC,expat,mariadb}-devel lib{edit,curl,xml2,xslt}-devel \
glog-devel oniguruma-devel ocaml gperf enca libjpeg-turbo-devel openssl-devel \
{fastlz,double-conversion,re2}-devel make -y

# Optional dependencies (these extensions are not built by default)

yum install {fribidi,libc-client,glib2}-devel -y

# Get our hhvm
cd
git clone https://github.com/facebook/hhvm -b master  hhvm  --recursive
cd hhvm

# Okay let's go
cmake3 .
# Multithreads compiling
make -j$(($(nproc)+1))
# Compiled?
./hphp/hhvm/hhvm --version
# Install it
make install
# Final
hhvm --version

wget https://github.com/hhvm/packaging/raw/master/hhvm/deb/skeleton/etc/init.d/hhvm -O /etc/init.d/hhvm

sudo chmod +x /etc/init.d/hhvm

#hhvm -m daemon -c /etc/hhvm/server.ini -d hhvm.server.type=fastcgi -d hhvm.server.port=9000
}
