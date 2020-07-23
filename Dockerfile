
#Download Amazon linux
FROM amazonlinux:2

RUN yum update -y && yum install -y initscripts;
RUN yum install -y sqlite-devel

CMD ["/usr/sbin/init"]

#Create folder
RUN mkdir -p /home/ec2-user/ekosimProject

#Copy executable to new folder
COPY main /home/ec2-user/ekosimProject

#Run the file inside image
CMD /home/ec2-user/ekosimProject


