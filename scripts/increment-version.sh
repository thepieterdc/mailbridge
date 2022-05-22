#!/bin/sh

set -eu

usage() {
    echo "Syntax: ./scripts/increment-version.sh"
    exit 1
}

# Get the current version.
version=$(cat CMakeLists.txt | grep "mailbridge VERSION" | grep -o '".*"' | tr -d '"')

# Split the version.
major=$(echo "$version" | egrep -o "^[0-9]+")
minor=$(echo "$version" | egrep -o "\.[0-9]+\." | egrep -o "[0-9]+")
bugfix=$(echo "$version" | egrep -o "\.[0-9]+$" | egrep -o "[0-9]+")

# Increment the bugfix version.
bugfix=$((bugfix+1))

# Build the new version.
newversion="$major.$minor.$bugfix"

# Set the new version.
./scripts/set-version.sh "$newversion"