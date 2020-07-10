
#Download Amazon linux
FROM amazonlinux:2

RUN yum update -y && yum install -y initscripts;
RUN yum install sqlite-devel

CMD ["/usr/sbin/init"]

#Create folder
RUN mkdir -p /home/ecosim

#Copy executable to new folder
COPY main /home/ecosim

#Run the file inside image
CMD /home/ecosim/main


