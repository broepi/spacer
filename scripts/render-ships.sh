#!/usr/bin/bash

blender -b blender/playership.blend -o render/playership/ -f 0 -e 63 -a
blender -b blender/enemyship.blend -o render/enemyship/ -f 0 -e 63 -a
