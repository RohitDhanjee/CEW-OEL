#!/bin/bash

# Compile code.c with libcurl and cJSON libraries
gcc -o code code.c -lcurl -I/usr/include/cjson -lcjson


# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running code..."
    
    # Run the compiled program
    ./code
    
    # Check if execution was successful
    if [ $? -eq 0 ]; then
        echo "code executed successfully."
    else
        echo "Failed to execute code2."
    fi
else
    echo "Compilation failed. Exiting..."
fi

