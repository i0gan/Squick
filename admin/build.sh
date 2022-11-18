#! /bin/bash
# if nodejs version > 17, set environment bellow
#export NODE_OPTIONS=--openssl-legacy-provider
npm run build:prod
rm -rf ../deploy/data/admin/www
cp -r ./dist ../deploy/data/admin/www
