#!/bin/bash
touch /var/app/current/myDB/Bennyworld.db
touch /var/app/current/myDB/Bennyland.db
touch /var/app/current/myDB/Saraland.db
sudo chown webapp /var/app/current/myDB/*
sudo chmod a+w /var/app/current/myDB/*.db
