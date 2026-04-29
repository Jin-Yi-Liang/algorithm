# 算法刷题复习系统 - Docker 镜像
FROM python:3.12-slim

# 设置工作目录
WORKDIR /app

# 复制应用文件
COPY server.py .
COPY scanner.py .
COPY dashboard.html .
COPY .vscode/ .vscode/

# 复制 problems 和 notes 目录（题目数据和笔记）
COPY problems/ ./problems/
COPY notes/ ./notes/

# 暴露端口
EXPOSE 8080

# 启动命令
CMD ["python", "server.py"]
