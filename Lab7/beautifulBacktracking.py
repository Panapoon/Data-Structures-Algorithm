def ok_to_append(seq, v):
    m = len(seq)
    for i in range(m):
        for j in range(i + 1, m):
            # ถ้า seq[i], seq[j], v เป็นลำดับเลขคณิต 3 พจน์
            if seq[i] + v == 2 * seq[j]:
                return False
    return True


def dfs(n, used, seq):
    if len(seq) == n + 1:
        return True
    for v in range(n + 1):
        if used[v]:
            continue
        if ok_to_append(seq, v):
            used[v] = True
            seq.append(v)
            if dfs(n, used, seq):
                return True
            seq.pop()
            used[v] = False
    return False


def beautiful_backtracking(n):
    used = [False] * (n + 1)
    seq = []
    if dfs(n, used, seq):
        return seq
    raise RuntimeError("No ordering found (unexpected for this problem).")


# -------------------------------
# main program
# -------------------------------
if __name__ == "__main__":
    n = int(input())
    ans = beautiful_backtracking(n)
    print(" ".join(map(str, ans)))
