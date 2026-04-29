"""
算法刷题复习系统 - HTTP 服务器
使用 Python 标准库（无依赖），提供 REST API
"""

import json
import os
from http.server import HTTPServer, BaseHTTPRequestHandler
from urllib.parse import urlparse, parse_qs, unquote
from datetime import date
from dataclasses import asdict

import scanner

PORT = 8080
STATIC_DIR = os.path.dirname(__file__)


def write_json(handler, data: dict, status: int = 200):
    handler.send_response(status)
    handler.send_header("Content-Type", "application/json")
    handler.send_header("Access-Control-Allow-Origin", "*")
    handler.end_headers()
    handler.wfile.write(json.dumps(data, ensure_ascii=False).encode("utf-8"))


def write_text(handler, text: str, status: int = 200):
    handler.send_response(status)
    handler.send_header("Content-Type", "text/plain; charset=utf-8")
    handler.end_headers()
    handler.wfile.write(text.encode("utf-8"))


def send_file(handler, filepath: str, content_type: str):
    if not os.path.exists(filepath):
        handler.send_error(404, "File not found")
        return
    with open(filepath, "rb") as f:
        content = f.read()
    handler.send_response(200)
    handler.send_header("Content-Type", content_type)
    handler.send_header("Content-Length", len(content))
    handler.end_headers()
    handler.wfile.write(content)


class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        parsed = urlparse(self.path)
        path = parsed.path
        qs = parse_qs(parsed.query)

        # 静态文件
        if path == "/" or path == "/dashboard":
            send_file(self, os.path.join(STATIC_DIR, "dashboard.html"), "text/html; charset=utf-8")
            return

        # API 路由
        if path == "/api/problems":
            all_problems = scanner.scan_all()
            write_json(self, [asdict(p) for p in all_problems])
            return

        if path == "/api/problems/due":
            due = scanner.scan_due()
            write_json(self, [asdict(p) for p in due])
            return

        if path == "/api/stats":
            write_json(self, scanner.get_stats())
            return

        if path == "/api/today":
            write_json(self, scanner.get_today_stats())
            return

        # 分类汇总（洛谷风格首页）
        if path == "/api/categories":
            write_json(self, scanner.get_all_categories_summary())
            return

        # 算法笔记列表
        if path == "/api/algorithms":
            write_json(self, scanner.get_all_categories())
            return

        # 单算法笔记：/api/algorithms/{name}
        if path.startswith("/api/algorithms/"):
            name = unquote(path[len("/api/algorithms/"):])
            if not name:
                write_json(self, {"error": "algorithm name required"}, 400)
                return
            content = scanner.load_algorithm_note(name)
            write_json(self, {"name": name, "content": content})
            return

        # 单题详情：/api/problems/{id}
        if path.startswith("/api/problems/"):
            pid = path[len("/api/problems/"):]
            p = scanner.get_problem(pid)
            if p:
                notes = scanner.load_notes(p)
                data = asdict(p)
                data["notes"] = notes
                write_json(self, data)
            else:
                write_json(self, {"error": "Not found"}, 404)
            return

        # 其他静态资源
        if path.startswith("/static/"):
            filename = path[len("/static/"):]
            send_file(self, os.path.join(STATIC_DIR, "static", filename), "application/octet-stream")
            return

        self.send_error(404, "Not found")

    def do_POST(self):
        parsed = urlparse(self.path)
        path = parsed.path

        length = int(self.headers.get("Content-Length", 0))
        body = self.rfile.read(length).decode("utf-8")

        try:
            data = json.loads(body) if body else {}
        except json.JSONDecodeError:
            write_json(self, {"error": "Invalid JSON"}, 400)
            return

        # 复习接口
        if path == "/api/review":
            pid = data.get("problemId")
            quality = data.get("quality")
            if not pid or quality is None:
                write_json(self, {"error": "problemId and quality required"}, 400)
                return
            result = scanner.review_problem(pid, int(quality))
            if result:
                write_json(self, asdict(result))
            else:
                write_json(self, {"error": "Problem not found"}, 404)
            return

        # 新增题目
        if path == "/api/problems":
            try:
                p = scanner.add_problem(
                    problemId=data["problemId"],
                    name=data.get("name", ""),
                    platform=data.get("platform", "LeetCode"),
                    category=data.get("category", "未分类"),
                    difficulty=data.get("difficulty", "未评级"),
                    notes=data.get("notes", ""),
                    firstCompleted=data.get("firstCompleted"),
                    url=data.get("url", "")
                )
                write_json(self, asdict(p), 201)
            except Exception as e:
                write_json(self, {"error": str(e)}, 400)
            return

        self.send_error(404, "Not found")

    def do_PUT(self):
        parsed = urlparse(self.path)
        path = parsed.path

        length = int(self.headers.get("Content-Length", 0))
        body = self.rfile.read(length).decode("utf-8")

        try:
            data = json.loads(body) if body else {}
        except json.JSONDecodeError:
            write_json(self, {"error": "Invalid JSON"}, 400)
            return

        # 保存算法笔记 PUT /api/algorithms/{name}
        if path.startswith("/api/algorithms/"):
            name = unquote(path[len("/api/algorithms/"):])
            if not name:
                write_json(self, {"error": "algorithm name required"}, 400)
                return
            content = data.get("content", "")
            scanner.save_algorithm_note(name, content)
            write_json(self, {"name": name, "content": content})
            return

        self.send_error(404, "Not found")

    def do_DELETE(self):
        parsed = urlparse(self.path)
        path = parsed.path

        if path.startswith("/api/problems/"):
            pid = path[len("/api/problems/"):]
            if not pid:
                write_json(self, {"error": "problemId required"}, 400)
                return
            success = scanner.delete_problem(pid)
            if success:
                write_json(self, {"message": "Deleted", "problemId": pid})
            else:
                write_json(self, {"error": "Problem not found"}, 404)
            return

        self.send_error(404, "Not found")

    def log_message(self, format, *args):
        print(f"[{self.log_date_time_string()}] {args[0]}")


def run():
    print(f"🚀 算法复习系统启动: http://localhost:{PORT}")
    print(f"📊 Dashboard: http://localhost:{PORT}/dashboard")
    server = HTTPServer(("", PORT), RequestHandler)
    server.serve_forever()


if __name__ == "__main__":
    run()
