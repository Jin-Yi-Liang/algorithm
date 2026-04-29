#!/bin/bash
# Kubernetes 部署脚本

set -e

NAMESPACE="${NAMESPACE:-algorithm}"
echo "🚀 部署到 Kubernetes 集群 (namespace: ${NAMESPACE})"

# 创建 namespace（如果不存在）
kubectl create namespace ${NAMESPACE} --dry-run=client -o yaml | kubectl apply -f -

# 应用部署配置
kubectl apply -f k8s-deployment.yaml -n ${NAMESPACE}

echo "✅ 部署完成"
echo ""
echo "📊 查看部署状态:"
echo "   kubectl get pods -n ${NAMESPACE}"
echo "   kubectl get svc -n ${NAMESPACE}"
echo ""
echo "🔍 查看日志:"
echo "   kubectl logs -f deployment/algorithm-review -n ${NAMESPACE}"
echo ""
echo "🌐 访问服务（端口转发）:"
echo "   kubectl port-forward svc/algorithm-review-service 8080:80 -n ${NAMESPACE}"
