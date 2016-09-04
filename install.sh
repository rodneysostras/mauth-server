#!/bin/bash 
# SCRIPT PARA INSTALACAO DO MAUTH
# DATE : 29/04/2016
# AUTOR: RODNEY SOSTRAS
# VERSION: 1.0
# CENTOS 6.7
# UPDATE DATE:29-04-2016
#http://www.thegeekstuff.com/2012/05/encrypt-bash-shell-script/

echo "Iniciando instalacao"

source "inc/epel.inc"
source "inc/update.inc"
source "inc/fail2ban.inc"
source "inc/cfs.inc"
source "inc/nginx.inc"
source "inc/hhvm.inc"
