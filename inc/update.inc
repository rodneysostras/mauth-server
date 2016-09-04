update() {
  yum clean all && \
  yum -y update && \
  yum clean all && \
  yum -y upgrade && \
  yum clean all && \
  cat /etc/redhat-release
}
