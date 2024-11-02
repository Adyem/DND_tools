FROM debian:buster

# Creating arguments
ARG DOMAIN
ARG CERTS_

# Setting to environment variables
ENV DOMAIN=$DOMAIN
ENV CERTS_=$CERTS_

# Installing nginx and openssl
RUN apt-get update -y && apt-get upgrade -y && apt-get install -y nginx && apt-get install -y openssl

# Copying scripts
COPY /tools/ /

# Setting permissions and running build.sh
RUN chmod +x /build.sh
RUN /build.sh

# Launching nginx
CMD [ "nginx", "-g", "daemon off;"]