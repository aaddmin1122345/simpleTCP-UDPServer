#!/bin/bash

cd c/tcp/

# 编译服务端和客户端程序
gcc tcpServer.c -o /tmp/tcpServer >/dev/null
gcc tcpClient.c -o /tmp/tcpClient >/dev/null

# 启动 tmux 会话
tmux new-session -d -s tcp_demo

# 创建水平分屏，左边为服务端，右边为客户端
tmux split-window -h

# 在左边运行服务端程序
# tmux send-keys -t tcp_demo:0.0 "./tcpServer" C-m

tmux send-keys -t tcp_demo:0.0 "sudo tcpdump -ilo -vvvnnxXSK -s0 port 65534" C-m
# 在右边再分为上下两个窗口，上面为客户端，下面为 tcpdump
tmux split-window -v

# 在右下窗口中运行 tcpdump
tmux send-keys -t tcp_demo:0.1 "/tmp/tcpServer" C-m

# 在右上窗口中运行客户端程序
tmux send-keys -t tcp_demo:0.2 "/tmp/tcpClient" C-m



# 切换焦点到客户端窗口
tmux select-pane -t tcp_demo:0.2

# 进入 tmux 会话
tmux attach-session -t tcp_demo
