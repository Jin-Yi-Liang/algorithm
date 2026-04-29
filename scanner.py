"""
算法刷题复习系统 - 核心业务逻辑
SM-2 + Leitner 混合间隔重复算法
"""

import json
import os
from datetime import date, timedelta
from dataclasses import dataclass, asdict, fields
from typing import Optional

PROBLEMS_DIR = os.path.join(os.path.dirname(__file__), "problems")
NOTES_DIR = os.path.join(os.path.dirname(__file__), "notes")

# Leitner 盒子间隔表（天）
BOX_INTERVALS = {1: 1, 2: 3, 3: 7, 4: 14, 5: 30}


@dataclass
class Problem:
    problemId: str
    name: str
    platform: str = "LeetCode"
    category: list = None
    difficulty: str = "未评级"
    leitnerBox: int = 1
    easeFactor: float = 2.5
    interval: int = 0
    repetitions: int = 0
    nextReview: str = ""
    lastReview: Optional[str] = None
    firstCompleted: Optional[str] = None
    url: Optional[str] = ""
    totalReviews: int = 0
    history: list = None
    original_folder: str = ""  # 实际文件夹名，扫描时设置

    def __post_init__(self):
        if self.history is None:
            self.history = []
        if self.category is None:
            self.category = []
        if not self.nextReview:
            self.nextReview = str(date.today())

    @property
    def folder_name(self) -> str:
        return f"{self.problemId}_{self.name}"

    @property
    def folder_path(self) -> str:
        return os.path.join(PROBLEMS_DIR, self.folder_name)

    @property
    def notes_path(self) -> str:
        return os.path.join(self.folder_path, "notes.md")

    @property
    def review_path(self) -> str:
        return os.path.join(self.folder_path, "review.json")


def ensure_problem_dir(problem: Problem) -> None:
    os.makedirs(problem.folder_path, exist_ok=True)


# ─── SM-2 + Leitner 核心算法 ───────────────────────────────────────

def sm2_leitner_update(problem: Problem, quality: int) -> Problem:
    """
    质量评分 q ∈ [0..5]：
      5 - 完全掌握，很轻松回忆起
      4 - 正确，很快想起来
      3 - 正确，有一点犹豫
      2 - 正确，但很困难/需要提示
      1 - 正确，但极困难
      0 - 完全忘记

    规则：
      q >= 3 → 答对，box += 1（最高5）
      q < 3  → 答错，box = 1（降回L1）
    """
    today = date.today()

    if quality < 3:
        # 答错：降回盒子1，重新积累
        problem.leitnerBox = 1
        problem.interval = 1
        problem.repetitions = 0
    else:
        # 答对：升级盒子
        problem.repetitions += 1
        new_box = min(5, problem.leitnerBox + 1)
        problem.leitnerBox = new_box
        base_interval = BOX_INTERVALS[new_box]

        # SM-2 EF 更新
        ef_delta = 0.1 - (5 - quality) * (0.08 + (5 - quality) * 0.02)
        problem.easeFactor = max(1.3, problem.easeFactor + ef_delta)

        # 间隔 = max(SM-2计算值, 盒子基准值)
        if problem.repetitions == 1:
            problem.interval = 1
            problem.firstCompleted = str(today)
        elif problem.repetitions == 2:
            problem.interval = 3
        else:
            sm2_interval = int(problem.interval * problem.easeFactor)
            problem.interval = max(sm2_interval, base_interval)

    problem.nextReview = str(today + timedelta(days=problem.interval))
    problem.lastReview = str(today)
    problem.totalReviews += 1
    problem.history.append({
        "date": str(today),
        "quality": quality,
        "box": problem.leitnerBox,
        "interval": problem.interval
    })

    return problem


# ─── 文件读写 ─────────────────────────────────────────────────────

def load_review(problem: Problem) -> Problem:
    if not os.path.exists(problem.review_path):
        return problem
    with open(problem.review_path, "r", encoding="utf-8") as f:
        data = json.load(f)
    for k, v in data.items():
        if hasattr(problem, k):
            setattr(problem, k, v)
    return problem


def save_review(problem: Problem) -> None:
    folder = problem.original_folder or problem.folder_name
    folder_path = os.path.join(PROBLEMS_DIR, folder)
    os.makedirs(folder_path, exist_ok=True)
    review_path = os.path.join(folder_path, "review.json")
    with open(review_path, "w", encoding="utf-8") as f:
        json.dump(asdict(problem), f, ensure_ascii=False, indent=2)


def load_notes(problem: Problem) -> str:
    if os.path.exists(problem.notes_path):
        with open(problem.notes_path, "r", encoding="utf-8") as f:
            return f.read()
    return ""


def save_notes(problem: Problem, content: str) -> None:
    ensure_problem_dir(problem)
    with open(problem.notes_path, "w", encoding="utf-8") as f:
        f.write(content)


# ─── 扫描接口 ─────────────────────────────────────────────────────

def scan_all() -> list[Problem]:
    """扫描所有题目"""
    problems = []
    if not os.path.exists(PROBLEMS_DIR):
        return problems
    for folder in sorted(os.listdir(PROBLEMS_DIR)):
        folder_path = os.path.join(PROBLEMS_DIR, folder)
        if not os.path.isdir(folder_path):
            continue
        review_path = os.path.join(folder_path, "review.json")
        if not os.path.exists(review_path):
            continue
        with open(review_path, "r", encoding="utf-8") as f:
            data = json.load(f)
        p = Problem(**{k: v for k, v in data.items() if k in Problem.__dataclass_fields__})
        p.original_folder = folder  # 记录实际文件夹名
        # 兼容旧格式：category 可能是字符串（如 "前缀和+差分"），需要拆成列表
        if isinstance(p.category, str):
            p.category = [c.strip() for c in p.category.split('+') if c.strip()] if p.category else []
        problems.append(p)
    return problems


def scan_due(today: Optional[date] = None) -> list[Problem]:
    """扫描今天应复习的题目（含逾期）"""
    if today is None:
        today_obj = date.today()
    else:
        today_obj = today if isinstance(today, date) else date.fromisoformat(today)
    today_str = str(today_obj)

    all_problems = scan_all()
    due = []
    for p in all_problems:
        if p.nextReview and p.nextReview <= today_str:
            due.append(p)
    return sorted(due, key=lambda x: x.category[0] if x.category else "")


def get_today_stats() -> dict:
    """获取今日刷题统计"""
    today_str = str(date.today())
    all_problems = scan_all()

    new_today = 0      # 今日新增（含已完成）
    reviewed_today = 0  # 今日复习过（含答对/答错）
    reviewed_correct_today = 0  # 今日答对

    for p in all_problems:
        if p.firstCompleted == today_str:
            new_today += 1
        if p.lastReview == today_str:
            reviewed_today += 1
            # 检查最后一次复习是否答对（quality >= 3）
            if p.history:
                last = p.history[-1]
                if last.get("quality", 0) >= 3:
                    reviewed_correct_today += 1

    return {
        "newToday": new_today,
        "reviewedToday": reviewed_today,
        "reviewedCorrectToday": reviewed_correct_today,
        "totalToday": new_today + reviewed_today
    }


def get_stats() -> dict:
    """获取统计数据"""
    problems = scan_all()
    today_str = str(date.today())

    box_counts = {1: 0, 2: 0, 3: 0, 4: 0, 5: 0}
    category_counts = {}
    platform_counts = {}
    overdue_count = 0
    mastered_count = 0  # box 5

    for p in problems:
        box_counts[p.leitnerBox] = box_counts.get(p.leitnerBox, 0) + 1
        for cat in p.category:
            category_counts[cat] = category_counts.get(cat, 0) + 1
        platform_counts[p.platform] = platform_counts.get(p.platform, 0) + 1

        if p.nextReview and p.nextReview < today_str:
            overdue_count += 1
        if p.leitnerBox == 5:
            mastered_count += 1

    return {
        "total": len(problems),
        "overdue": overdue_count,
        "mastered": mastered_count,
        "boxCounts": box_counts,
        "categoryCounts": category_counts,
        "platformCounts": platform_counts,
    }


def review_problem(problemId: str, quality: int) -> Optional[Problem]:
    """复习一道题，更新状态"""
    all_problems = scan_all()
    for p in all_problems:
        if p.problemId == problemId:
            updated = sm2_leitner_update(p, quality)
            save_review(updated)
            return updated
    return None


def _make_url(problemId: str, platform: str) -> str:
    """根据平台和题目ID生成题目链接"""
    if "LeetCode" in platform or "LC" in problemId or problemId.startswith("LCR"):
        num = problemId.replace("LC", "").replace("LCR", "")
        return f"https://leetcode.cn/problems/{num}/" if "CN" in platform else f"https://leetcode.com/problems/{num}/"
    if "洛谷" in platform:
        num = problemId.lstrip("PLGK")
        return f"https://www.luogu.com.cn/problem/P{num}"
    if "PTA" in platform:
        num = problemId.lstrip("PTAL")
        return f"https://pintia.cn/problem-sets/994805046380707840/exam/problems/type/7?problemSetProblemId={num}"
    if "牛客网" in platform or "NowCoder" in platform or problemId.startswith("NC"):
        # NC132303C -> contest=132303, suffix=C
        num = problemId.lstrip("NC")
        contest_id = num[:-1]
        suffix = num[-1]
        return f"https://ac.nowcoder.com/acm/contest/{contest_id}/{suffix}"
    return ""


def add_problem(
    problemId: str,
    name: str,
    platform: str = "LeetCode",
    category: str = "未分类",
    difficulty: str = "未评级",
    notes: str = "",
    firstCompleted: Optional[str] = None,
    url: str = ""
) -> Problem:
    """添加新题目（已完成的题目 nextReview 设为明天，避免当天重复出现）"""
    # 去重检查：同 platform + problemId 已存在则报错
    for existing in scan_all():
        if existing.problemId == problemId and existing.platform == platform:
            raise ValueError(f"题目 {problemId}（{platform}）已存在，请勿重复添加")

    auto_url = _make_url(problemId, platform)
    today = str(date.today())
    tomorrow = str(date.today() + timedelta(days=1))

    # 规范化 category 为列表
    if isinstance(category, str):
        cat_list = [c.strip() for c in category.split("+") if c.strip()] if category else []
    else:
        cat_list = category or []
    p = Problem(
        problemId=problemId,
        name=name,
        platform=platform,
        category=cat_list,
        difficulty=difficulty,
        nextReview=tomorrow if firstCompleted else today,
        firstCompleted=firstCompleted or today,
        url=url or auto_url
    )
    ensure_problem_dir(p)
    if notes:
        save_notes(p, notes)
    save_review(p)
    return p


def get_problem(problemId: str) -> Optional[Problem]:
    """获取单个题目"""
    for p in scan_all():
        if p.problemId == problemId:
            return p
    return None


def delete_problem(problemId: str) -> bool:
    """删除题目（删除文件夹）"""
    all_problems = scan_all()
    for p in all_problems:
        if p.problemId == problemId:
            import shutil
            if os.path.exists(p.folder_path):
                shutil.rmtree(p.folder_path)
            return True
    return False


# ─── 算法笔记管理 ───────────────────────────────────────────────

def load_algorithm_note(category: str) -> str:
    """读取某算法的笔记，不存在则返回空字符串"""
    os.makedirs(NOTES_DIR, exist_ok=True)
    path = os.path.join(NOTES_DIR, f"{category}.md")
    if os.path.exists(path):
        with open(path, "r", encoding="utf-8") as f:
            return f.read()
    return ""


def save_algorithm_note(category: str, content: str) -> None:
    """保存某算法的笔记"""
    os.makedirs(NOTES_DIR, exist_ok=True)
    path = os.path.join(NOTES_DIR, f"{category}.md")
    with open(path, "w", encoding="utf-8") as f:
        f.write(content)


def get_problems_by_category(category: str) -> list:
    """获取指定类别的所有题目（题目可属于多个类别）"""
    return [p for p in scan_all() if category in p.category]


def get_all_categories() -> list[dict]:
    """
    获取所有算法类别，按一级分类分组，含笔记内容、题目数、题目列表。
    一个题目可属于多个分类（如 ["图论","最短路"] 的题目会在"图论"和"最短路"下都出现）。
    返回格式：[{name: "图论", totalCount, subcategories: [{name, content, problemCount, problems}, ...]}, ...]
    按一级分类总题数降序排列。
    """
    all_problems = scan_all()

    # cat_map: key=完整分类名(individual tag), value=Problem列表
    # 一个题目有多个tag时，会出现在多个tag的列表中
    cat_map = {}
    for p in all_problems:
        for cat in p.category:
            if cat not in cat_map:
                cat_map[cat] = []
            cat_map[cat].append(p)

    # 构建 category 条目
    cat_entries = {}
    for cat, problems in cat_map.items():
        cat_entries[cat] = {
            "name": cat,
            "content": load_algorithm_note(cat),
            "problemCount": len(problems),
            "problems": sorted(problems, key=lambda x: x.problemId)
        }

    # 按一级分类聚合（无"-"则group就是自己）
    group_map = {}
    for cat, entry in cat_entries.items():
        group = cat.split("-")[0] if "-" in cat else cat
        if group not in group_map:
            group_map[group] = {
                "name": group,
                "totalCount": 0,
                "subcategories": []
            }
        group_map[group]["totalCount"] += entry["problemCount"]
        group_map[group]["subcategories"].append(entry)

    result = list(group_map.values())
    result.sort(key=lambda x: -x["totalCount"])
    for g in result:
        g["subcategories"].sort(key=lambda x: -x["problemCount"])
        for sc in g["subcategories"]:
            sc["problems"] = [
                {
                    "problemId": p.problemId,
                    "name": p.name,
                    "platform": p.platform,
                    "leitnerBox": p.leitnerBox,
                    "nextReview": p.nextReview,
                    "difficulty": p.difficulty,
                    "url": p.url,
                }
                for p in sc["problems"]
            ]
    return result


def get_all_categories_summary() -> list[dict]:
    """
    获取所有分类的汇总信息，按分类名分组。
    返回格式：[{
        "name": "前缀和",
        "problemCount": 2,
        "difficultyBreakdown": {"入门": 2},
        "platforms": ["洛谷"],
        "problems": [{problemId, name, platform, difficulty, leitnerBox, nextReview, url}, ...]
    }, ...]
    按 problemCount 降序排列。
    """
    all_problems = scan_all()

    cat_map = {}
    for p in all_problems:
        for cat in p.category:
            if cat not in cat_map:
                cat_map[cat] = []
            cat_map[cat].append(p)

    result = []
    for cat, problems in cat_map.items():
        difficulty_breakdown = {}
        platforms_set = set()
        problem_list = []

        for p in problems:
            difficulty_breakdown[p.difficulty] = difficulty_breakdown.get(p.difficulty, 0) + 1
            platforms_set.add(p.platform)
            problem_list.append({
                "problemId": p.problemId,
                "name": p.name,
                "platform": p.platform,
                "difficulty": p.difficulty,
                "leitnerBox": p.leitnerBox,
                "nextReview": p.nextReview,
                "url": p.url,
            })

        result.append({
            "name": cat,
            "problemCount": len(problems),
            "difficultyBreakdown": difficulty_breakdown,
            "platforms": sorted(platforms_set),
            "problems": problem_list,
        })

    DIFFICULTY_ORDER = {
        "未评级": 1, "入门": 2, "简单": 3, "基础题": 3,
        "L1": 3, "L2": 5, "L3": 8,
        "中等": 5, "普及+/提高": 6, "普及/提高-": 7, "困难": 9
    }
    FIXED_ORDER = {"前缀和": 0, "差分": 1, "滑动窗口": 2, "二分": 3}
    result.sort(key=lambda x: (
        FIXED_ORDER.get(x["name"], 4),
        min(DIFFICULTY_ORDER.get(d, 5) for d in x["difficultyBreakdown"].keys()) if x["difficultyBreakdown"] else 4,
        -x["problemCount"]
    ))
    return result


if __name__ == "__main__":
    # 简单测试
    print("总题数:", len(scan_all()))
    print("今日待复习:", len(scan_due()))
    print("统计数据:", get_stats())
