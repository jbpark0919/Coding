from collections import deque

# 상하좌우
dx = [0, 0, -1, 1]
dy = [1, -1, 0, 0]

def simulation(queue):
    answer = 0
    
    while queue:
        nxt_list = []
        
        # 이동
        for _ in range(len(queue)):
            cx, cy, dir_, size = queue.popleft()
        
            nx = cx + dx[dir_] * 0.5
            ny = cy + dy[dir_] * 0.5
            
            if -1000 <= nx <= 1000 and -1000 <= ny <= 1000:
                nxt_list.append((nx, ny, dir_, size))
        
        
        # 터지는지 확인
        cnt_dic = {}
        size_dic = {}
        for x, y, _, size in nxt_list:
            cnt_dic[(x, y)] = cnt_dic.get((x, y), 0) + 1
            size_dic[(x, y)] = size_dic.get((x, y), 0) + size
        
        # 터뜨리기
        for (x, y), v in cnt_dic.items():
            if v > 1:
                answer += size_dic[(x, y)]
        
        # 터지면 빼기
        n_len = len(nxt_list)
        for idx, (x, y, _, _) in enumerate(nxt_list[::-1]): # 뒤에서부터 빼기
            if cnt_dic[(x, y)] > 1:
                nxt_list.pop(n_len - 1 - idx)
        
        for info in nxt_list:
            queue.append(info)

    return answer

T = int(input())

for t in range(1, T + 1):
    K = int(input())
    
    queue = deque()
    
    for _ in range(K):
        info = list(map(int, input().split())) # x, y, 방향, 크기
        queue.append(info)
    
    print(f"#{t} {simulation(queue)}")