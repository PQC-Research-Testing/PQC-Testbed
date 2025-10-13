#!/bin/bash

# Check if a directory is provided as an argument
if [ -z "$1" ]; then
  echo "Usage: $0 <directory>"
  exit 1
fi

DIR="$1"

# Check if the provided path is a valid directory
if [ ! -d "$DIR" ]; then
  echo "Error: $DIR is not a valid directory."
  exit 1
fi

# Find and delete all subdirectories named "build"
find "$DIR" -type d -name "build" -exec rm -rf {} +
find "$DIR" -type d -name "cmake" -exec rm -rf {} +
