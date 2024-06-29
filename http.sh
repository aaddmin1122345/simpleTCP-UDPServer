#!/bin/bash

# 使用 curl 发送一个 HTTP GET 请求
echo "Sending HTTP GET request..."
curl -v https://www.swfu.edu.cn/

# 使用 curl 发送一个 HTTP POST 请求
echo "Sending HTTP POST request..."
curl -v -X POST -d "action=get_captcha" https://0x00.fun/wp-admin/admin-ajax.php

# 使用 curl 发送一个 HTTP 请求并保存响应到文件
echo "Saving HTTP response to file..."
curl -v -o response.txt https://www.baidu.com

# 使用 curl 获取 HTTP 响应头
echo "Fetching HTTP headers..."
curl -v -I https://www.baidu.com
