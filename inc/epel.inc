epel() {
	yum -y install epel-release yum-priorities
	sed -i "s|enabled=1|enabled=1\npriority=10|" /etc/yum.repos.d/epel.repo
}
