FROM debian:buster

# Creating arguments
ARG DOMAIN
ARG DB_NAME
ARG ADM_PASS
ARG ADM_USER
ARG DB_HOST
ARG TITLE
ARG ADM_MAIL
ARG NORMAL_USER
ARG NORMAL_PASS
ARG NORMAL_MAIL

# Setting to environment variables
ENV DOMAIN=${DOMAIN}
ENV DB_NAME=${DB_NAME}
ENV ADM_PASS=${ADM_PASS}
ENV ADM_USER=${ADM_USER}
ENV DB_HOST=${DB_HOST}
ENV TITLE=${TITLE}
ENV ADM_MAIL=${ADM_MAIL}
ENV NORMAL_USER=${NORMAL_USER}
ENV NORMAL_PASS=${NORMAL_PASS}
ENV NORMAL_MAIL=${NORMAL_MAIL}

# Installing php-fpm, php-mysql and curl
RUN apt-get update -y && apt-get upgrade -y && apt-get install -y php-fpm && apt-get install -y php-mysql && apt-get install -y curl

# Copying scripts
COPY ./tools/ /

# Setting permissions and running build.sh
RUN chmod +x /build.sh
RUN chmod +x /startup.sh
RUN /build.sh

# Running startup.sh
CMD [ "/startup.sh" ]