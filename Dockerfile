#Download Amazon linux
FROM amazonlinux:2

# Install debugging and development tools
RUN yum update -y && yum install -y \
    initscripts \
    sqlite-devel \
    gdb \
    valgrind \
    strace \
    procps-ng

CMD ["/usr/sbin/init"]

# Create folder for the application
RUN mkdir -p /home/ec2-user/ekosimProject

# Copy executable to new folder
COPY main /home/ec2-user/ekosimProject

# Make sure the executable has proper permissions
RUN chmod +x /home/ec2-user/ekosimProject/main

# Create a script to run with debugging
RUN echo '#!/bin/bash' > /home/ec2-user/ekosimProject/debug_run.sh && \
    echo 'echo "=== Running with memory debugging ===" ' >> /home/ec2-user/ekosimProject/debug_run.sh && \
    echo 'echo "Process info before start:"' >> /home/ec2-user/ekosimProject/debug_run.sh && \
    echo 'cat /proc/meminfo | head -5' >> /home/ec2-user/ekosimProject/debug_run.sh && \
    echo 'echo "Running main application..."' >> /home/ec2-user/ekosimProject/debug_run.sh && \
    echo '/home/ec2-user/ekosimProject/main 2>&1 | head -200' >> /home/ec2-user/ekosimProject/debug_run.sh && \
    chmod +x /home/ec2-user/ekosimProject/debug_run.sh

# Set working directory
WORKDIR /home/ec2-user/ekosimProject

# Default command to run (can be overridden)
CMD ["./debug_run.sh"]
