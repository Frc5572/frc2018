#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
node $DIR/server.js "$DIR"
exit_status=$?
if [ $exit_status -eq 200 ]; then # Restart Process
	exec "$DIR/$(basename $0)"
fi
