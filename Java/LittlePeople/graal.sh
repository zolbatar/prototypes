#!/bin/sh
export PATH_TO_FX=/home/daryl/Development/Java/javafx-sdk-11.0.2/lib
export PATH_TO_FX_MODS=/home/daryl/Development/Java/javafx-jmods-11.0.2
javac --module-path $PATH_TO_FX_MODS -d mods/LittlePeople $(find src/ -name "*.java")
cp -r src/sample/*.fxml mods/LittlePeople/sample/
java --module-path $PATH_TO_FX:mods -m LittlePeople/sample.Main
