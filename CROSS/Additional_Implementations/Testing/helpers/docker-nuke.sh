#!/usr/bin/env bash

# Ignore Ctrl+C (SIGINT) signal
trap '' SIGINT

docker rm -f -v $(docker ps -aq)
docker rmi -f  $(docker images -q)
docker volume rm $(docker volume ls -q)
docker network rm $(docker network ls -q)
#docker buildx prune -f