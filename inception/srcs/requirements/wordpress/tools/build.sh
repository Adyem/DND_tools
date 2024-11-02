#!/bin/bash

set -e

# Create html directory and/or remove old files
mkdir /var/www
mkdir /var/www/html
cd /var/www/html
rm -rf *

# Download Wordpress installer
curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar

# Run Wordpress installer
chmod +x wp-cli.phar
mv wp-cli.phar /usr/local/bin/wp

# Download Wordpress
wp core download --allow-root

# Set fpm port to 9000
sed -i 's/listen = \/run\/php\/php7.3-fpm.sock/listen = 9000/g' /etc/php/7.3/fpm/pool.d/www.conf