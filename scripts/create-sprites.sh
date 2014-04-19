#!/usr/bin/bash

./scripts/spritesheet.py render/playership/ res/playership.png
./scripts/spritesheet.py render/enemyship/ res/enemyship.png
./scripts/hyperspin.py render/playership/ res/playership-hyperspin.png 0 32
./scripts/hyperspin.py render/playership/ res/playership-hyperspin-engine.png 32 32
./scripts/hyperspin.py render/enemyship/ res/enemyship-hyperspin.png 0 32
./scripts/hyperspin.py render/enemyship/ res/enemyship-hyperspin-engine.png 32 32
./scripts/radar.py
