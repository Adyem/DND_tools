all:
	@echo "\033[1m\033[38;2;135;206;235mUsage:\033[0m"
	@echo "\033[38;2;60;200;60m	make up		→ Launch the network\033[0m"
	@echo "\033[38;2;0;206;209m	make build	→ Build the (changed) containers\033[0m"
	@echo "\033[38;2;255;165;0m	make rebuild	→ Wipe all data and rebuild the containers\033[0m"
	@echo "\033[38;2;139;0;0m	make stop	→ Turn off the network\033[0m"
	@echo "\033[38;2;139;0;0m	make down	→ Turn off the network and destroy it\033[0m"
	@echo "\033[38;2;255;0;0m	make clean	→ Stop, destroy and delete entire network and related data\033[0m"
	@echo "\033[38;2;255;0;0m	make re		→ Stop, destroy, delete, build and start the network\033[0m"
	@echo "\033[38;2;70;130;180m	make logs	→ Show the logs of all containers\033[0m"
	@echo "\033[38;2;70;130;180m	make status	→ Show the status of all containers\033[0m"

up:
	@echo "\033[38;2;60;200;60mLaunching the network\033[5m...\033[0m"
	@mkdir -p /home/adyem/data
	@mkdir -p /home/adyem/data/wordpress
	@mkdir -p /home/adyem/data/mariadb
	@mkdir -p /home/adyem/data/website
	@docker-compose -f srcs/docker-compose.yml up -d

build:
	@echo "\033[38;2;0;206;209mBuilding the containers\033[5m...\033[0m"
	@docker-compose -f srcs/docker-compose.yml build

rebuild:
	@echo "\033[38;2;255;165;0m(Re)building the containers without cache...\033[0m"
	@docker-compose -f srcs/docker-compose.yml build --no-cache

stop:
	@echo "\033[38;2;139;0;0mStopping the network\033[5m...\033[0m"
	@docker-compose -f srcs/docker-compose.yml stop

down:
	@echo "\033[38;2;139;0;0mStopping and destroying the network\033[5m...\033[0m"
	@docker-compose -f srcs/docker-compose.yml down

logs:
	@echo "\033[38;2;70;130;180mShowing the logs of all containers\033[5m...\033[0m"
	@docker-compose -f srcs/docker-compose.yml logs

status:
	@echo "\033[38;2;70;130;180mShowing the status of all containers\033[5m...\033[0m"
	@docker-compose -f srcs/docker-compose.yml ps

clean:
	@echo "\033[38;2;139;0;0mCleaning the network\033[5m...\033[0m"
	@docker-compose -f srcs/docker-compose.yml down --rmi all --volumes

re: 
	@echo "\033[38;2;255;0;0mStopping, destroying, rebuilding and starting the network\033[5m...\033[0m"
	@make clean
	@make rebuild
	@make up

.PHONY: all up build rebuild stop down re clean logs status
