#!/bin/bash
# 构建 Docker 镜像脚本

set -e

IMAGE_NAME="algorithm-review"
TAG="latest"

echo "🔨 构建 Docker 镜像：${IMAGE_NAME}:${TAG}"

docker build -t ${IMAGE_NAME}:${TAG} .

echo "✅ 镜像构建完成"
echo "   镜像名：${IMAGE_NAME}:${TAG}"

# 可选：推送到镜像仓库
# docker tag ${IMAGE_NAME}:${TAG} your-registry/${IMAGE_NAME}:${TAG}
# docker push your-registry/${IMAGE_NAME}:${TAG}
