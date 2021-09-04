#!/usr/bin/env bash

docker-compose down
docker volume rm docker_onboarding_volume
docker-compose build --no-cache
docker-compose up --force-recreate -d

