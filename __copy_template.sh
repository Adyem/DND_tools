#!/usr/bin/env bash

# copy_template.sh
# Usage: ./copy_template.sh <new_name>
# - new_name must be lowercase letters and underscores only
# - first character must be a lowercase letter [a-z]

# Check for exactly one argument
if [ $# -ne 1 ]; then
    echo "Error: You must provide exactly one argument."
    exit 1
fi

ARG="$1"

# Validate the argument:
# - Must match only [a-z_]+
# - First character must be [a-z]
if [[ ! "$ARG" =~ ^[a-z] ]]; then
    echo "Error: The first character must be a lowercase letter [a-z]."
    exit 1
fi
if [[ ! "$ARG" =~ ^[a-z_]+$ ]]; then
    echo "Error: Argument can only contain lowercase letters [a-z] and underscores [_]."
    exit 1
fi

# Copy template files to new names
cp template.hpp "${ARG}.hpp"
cp template.cpp "${ARG}.cpp"

# Compute uppercase and capitalized versions
ARG_UPPER=$(echo "$ARG" | tr '[:lower:]' '[:upper:]')

# Capitalized is first letter uppercase, then rest as is
# E.g. if ARG=chaos_goblin => Chaos_goblin
ARG_CAPITALIZED="$(tr '[:lower:]' '[:upper:]' <<< "${ARG:0:1}")${ARG:1}"

# Perform replacements
sed -i "s/template/${ARG}/g" "${ARG}.hpp" "${ARG}.cpp"
sed -i "s/TEMPLATE/${ARG_UPPER}/g" "${ARG}.hpp" "${ARG}.cpp"
sed -i "s/Template/${ARG_CAPITALIZED}/g" "${ARG}.hpp" "${ARG}.cpp"

echo "Successfully created ${ARG}.hpp and ${ARG}.cpp from template files."
