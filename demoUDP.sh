#!/bin/bash

### A simple UDP demo script ###

# set -euC
#
# tmux rename-window "UDP demo"

#    Window setup
# +--------+--------+
# | server | client |
# +--------+--------+
# |     tcpdump     |
# +-----------------+
#
# tmux split-window -h
# tmux split-window -fl99
#
# tmux send-keys -t{top-left}  "./udpServer.py"
# tmux send-keys -t{top-right} "./udpClient.py"
#
# tmux send-keys "sudo tcpdump -ilo -vvvnnxXK port 12000" C-m

python3 simpleUDP.py
python3 simpleClientUDP.py
watch -tn.1 'ss -ant "( sport == 65533 or dport == 65533 )"'
