#!/bin/bash

# Your script command goes here
./run_code.sh

# Run the script every minute for 3 hours
for ((i=0; i<180; i++)); do
    sleep 60  # Sleep for 60 seconds (1 minute)
    ./run_code.sh  # Your script command goes here
done

