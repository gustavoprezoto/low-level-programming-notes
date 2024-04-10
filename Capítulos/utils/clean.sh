#!/bin/bash

directory="."

find "$directory" -type f -name "*.o" -delete
find "$directory" -type f ! -name "*.*" -delete

echo "Directory cleaned."