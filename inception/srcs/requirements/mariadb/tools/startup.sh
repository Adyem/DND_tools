#!/bin/bash

# Exit on error
set -e

# Start mysql
service mysql start

# Wait for mysql to start
while ! mysqladmin ping --silent; do
    sleep 1
done
sleep 1

# Setting up database
echo "CREATE DATABASE IF NOT EXISTS ${DB_NAME} ;" > db.sql
echo "CREATE USER IF NOT EXISTS '${ADM_USER}'@'%' IDENTIFIED BY '${ADM_PASS}' ;" >> db.sql
echo "GRANT ALL PRIVILEGES ON ${DB_NAME}.* TO '${ADM_USER}'@'%' ;" >> db.sql
echo "ALTER USER 'root'@'localhost' IDENTIFIED BY '${ROOT_PASS}' ;" >> db.sql
echo "FLUSH PRIVILEGES ;" >> db.sql

# Execute sql script
mysql < db.sql

# Terminate mysql
kill $(cat /var/run/mysqld/mysqld.pid)

# Start mysql in foreground
mysqld