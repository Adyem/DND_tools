FROM debian:buster

# Creating arguments
ARG DB_NAME
ARG ADM_USER
ARG ADM_PASS
ARG ROOT_PASS

# Setting to environment variables
ENV DB_NAME=${DB_NAME}
ENV ADM_USER=${ADM_USER}
ENV ADM_PASS=${ADM_PASS}
ENV ROOT_PASS=${MYSQL_ROOT_PASS}

# Installing mariadb-server
RUN apt-get update -y && apt-get upgrade -y && apt-get install -y mariadb-server

# Copying config file
COPY /tools/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf

# Copying script
COPY /tools/startup.sh /startup.sh
RUN chmod +x /startup.sh

# Running startup.sh
CMD [ "/startup.sh" ]