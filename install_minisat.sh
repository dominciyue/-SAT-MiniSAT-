#!/bin/bash

echo "Start installing minisat..."
sudo apt update
sudo apt install libc6 libc-bin zip build-essential minisat zlib1g zlib1g-dev -y
echo "Installation complete"