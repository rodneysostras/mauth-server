csf() {
	sudo yum -y install wget perl unzip net-tools perl-libwww-perl perl-LWP-Protocol-https perl-GDGraph perl-CPAN -y

	cd
	tar -xzf $HOME/mauth-server/source/csf.tgz
	cd csf
	sh install.sh

	perl /usr/local/csf/bin/csftest.pl
	sh /usr/local/csf/bin/remove_apf_bfd.sh

	sed -i 's|TESTING = "1"|TESTING = "0"|' /etc/csf/csf.conf
	
	perl -MCPAN -e shell & install GD::Graph
	
	chkconfig --level 235 csf on
	
	systemctl enable csf
	systemctl enable lfd
	
	systemctl start csf
	systemctl start lfd
}
