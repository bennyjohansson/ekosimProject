#Download Amazon linux
FROM amazonlinux:2

RUN yum update -y && yum install -y initscripts;
RUN yum install -y sqlite-devel

CMD ["/usr/sbin/init"]

#Create folder
#RUN mkdir -p /home/ecosim
RUN mkdir -p /home/ec2-user/ekosimProject

#Copy executable to new folder
#COPY main /home/ecosim
COPY main /home/ec2-user/ekosimProject

#Copy company specification files
# COPY bempa_AB /home/ecosim
# COPY bempa_co /home/ecosim
# COPY benny_inc /home/ecosim
# COPY limpan_AB /home/ecosim
# COPY benny_enterprises /home/ecosim
# COPY johansson_och_johansson /home/ecosim


#Run the file inside image
#CMD /home/ecosim/main
CMD /home/ec2-user/ekosimProject