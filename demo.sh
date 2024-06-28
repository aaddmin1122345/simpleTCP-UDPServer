#!/bin/bash

### A simple TCP demo script ###

# set -euC
#
# tmux rename-window "TCP demo"

#    Window setup
# +--------+--------+
# | server | client |
# +--------+--------+
# |      watch      |
# +-----------------+
# |     tcpdump     |
# +-----------------+
#
# tmux split-window -h
# tmux split-window -fl99
# tmux split-window -l12
#
# tmux send-keys -t{top-left} "./simpleTCP.py"
#
# tmux send-keys -t{top-right} "./simpleClient.py"
#
# tmux send-keys -t{up-of} "watch -tn.1 'ss -ant \"( sport == 12000 or dport == 12000 )\"'" C-m
#
# tmux send-keys "sudo tcpdump -ilo -vvvnnxXSK -s0 port 12000" C-m

python3 simpleTCP.py
python3 simpleClient.py
watch -tn.1 'ss -ant "( sport == 65534 or dport == 65534 )"'



