#!/bin/sh
git add .
git commit -m "Heroku Upload"
git push heroku master
heroku logs -t
