#!/usr/bin/env python3
import sys
import argparse

# ---------- Core: LPS (prefix π) ----------
def compute_lps(pattern: str):
    n = len(pattern)
    lps = [0] * n
    length = 0
    i = 1
    while i < n:
        if pattern[i] == pattern[length]:
            length += 1
            lps[i] = length
            i += 1
        else:
            if length != 0:
                length = lps[length - 1]
            else:
                lps[i] = 0
                i += 1
    return lps

# ---------- KMP search (left-to-right) ----------
def kmp_search_lr(text: str, pattern: str):
    if not pattern:
        return []
    lps = compute_lps(pattern)
    n, m = len(text), len(pattern)
    i = j = 0
    ans = []
    while i < n:
        if text[i] == pattern[j]:
            i += 1
            j += 1
            if j == m:
                ans.append(i - m)  # 0-based start index
                j = lps[j - 1]
        else:
            if j != 0:
                j = lps[j - 1]
            else:
                i += 1
    return ans

# ---------- Naive search (left-to-right) ----------
def naive_search_lr(text: str, pattern: str):
    n, m = len(text), len(pattern)
    ans = []
    for s in range(n - m + 1):
        ok = True
        for k in range(m):
            if text[s + k] != pattern[k]:
                ok = False
                break
        if ok:
            ans.append(s)
    return ans

# ---------- Utilities ----------
def tokenize_and_join(s: str) -> str:
    """
    รับสตริงที่คั่นด้วยช่องว่าง เช่น 'X Y X Y' แล้วรวมเป็น 'XYXY'
    ถ้าผู้ใช้พิมพ์ติดกันอยู่แล้วก็จะได้เหมือนเดิม
    """
    toks = s.split()
    if len(toks) <= 1:
        return s.strip()
    return "".join(toks)

def main():
    parser = argparse.ArgumentParser(description="KMP vs Naive String Matching (with LR/RL) for Lab #8")
    parser.add_argument("--algo", choices=["kmp", "naive"], default="kmp", help="เลือกอัลกอริทึม (ดีฟอลต์ kmp)")
    args = parser.parse_args()

    data = sys.stdin.read().strip().splitlines()
    if len(data) < 4:
        print("ERROR: ต้องมีอินพุต 4 บรรทัด: alphabet, nPattern nText, pattern, text", file=sys.stderr)
        sys.exit(1)

    # บรรทัดที่ 1: alphabet (ไม่จำเป็นต้องใช้ในการคำนวณ แต่ต้องอ่าน)
    alphabet_line = data[0].strip()

    # บรรทัดที่ 2: ตัวเลข 2 ค่า (nPattern, nText) — ใช้เพื่อตรวจทานเฉยๆ
    n_pat, n_txt = map(int, data[1].split())

    # บรรทัดที่ 3: pattern
    pattern = tokenize_and_join(data[2])

    # บรรทัดที่ 4: text
    text = tokenize_and_join(data[3])

    # ตรวจความยาวให้สอดคล้อง (ถ้าไม่ตรงก็ยังคงเดินต่อไปตามสตริงจริง)
    # สามารถเตือนบน stderr ได้ (ไม่กระทบ output ที่โจทย์ต้องตรวจ)
    if len(pattern) != n_pat:
        print(f"WARNING: pattern length = {len(pattern)} ไม่ตรงกับที่ระบุ = {n_pat}", file=sys.stderr)
    if len(text) != n_txt:
        print(f"WARNING: text length = {len(text)} ไม่ตรงกับที่ระบุ = {n_txt}", file=sys.stderr)

    # 1) พิมพ์ prefix π (LPS) ของ pattern (ตามโจทย์ ใช้ของ pattern เดิม LR)
    lps = compute_lps(pattern)
    print(" ".join(map(str, lps)))

    # 2) หา match ทั้ง LR และ RL
    if args.algo == "kmp":
        lr_starts_0 = kmp_search_lr(text, pattern)  # 0-based
        rev_pattern = pattern[::-1]
        rl_starts_for_rev = kmp_search_lr(text, rev_pattern)  # 0-based start ของ reverse(pattern)
    else:
        lr_starts_0 = naive_search_lr(text, pattern)
        rev_pattern = pattern[::-1]
        rl_starts_for_rev = naive_search_lr(text, rev_pattern)

    # แปลงเป็นตำแหน่ง 1-based และติดทิศทาง
    # LR: รายงานตำแหน่งเริ่มต้น (1-based)
    lr_results = [(s + 1, "LR") for s in lr_starts_0]

    # RL: ถ้า reverse(pattern) เริ่มที่ s (0-based), ตำแหน่ง "ตัวแรกของ pattern เมื่ออ่านขวา->ซ้าย"
    # คือปลายขวาของช่วง match: s + m - 1 (0-based) => แปลงเป็น 1-based: s + m
    m = len(pattern)
    rl_results = [(s + m, "RL") for s in rl_starts_for_rev]

    # รวมแล้วเรียงตามตำแหน่ง (ถ้าตำแหน่งเท่ากัน ให้ LR มาก่อน RL เพื่อความคงที่)
    all_results = lr_results + rl_results
    all_results.sort(key=lambda x: (x[0], x[1]))

    # 3) พิมพ์จำนวนคำตอบ K และรายการคำตอบ
    print(len(all_results))
    for pos, direction in all_results:
        print(f"{pos} {direction}")

if __name__ == "__main__":
    main()