fail2ban() {
	yum -y install fail2ban
	systemctl enable fail2ban.service
	systemctl start fail2ban.service
}
