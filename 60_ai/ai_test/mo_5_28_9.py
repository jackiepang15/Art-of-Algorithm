from itertools import permutations, product

# 目标行和、列和
row_sums = [343, 172, 190, 424]
col_sums = [190, 334, 460, 145]

# 所有4x4的拉丁方（每行每列都是1,2,3,4的排列）
# 生成所有可能的填数方案
def generate_latin_squares():
    # 第一行固定为(1,2,3,4)的一个排列（由于对称性，我们可以枚举第一行）
    # 实际上为了不遗漏，需要更完整的搜索
    # 但4x4拉丁方只有576个，可以穷举
    squares = []
    for row0 in permutations([1,2,3,4]):
        for row1 in permutations([1,2,3,4]):
            ok = True
            for j in range(4):
                if row1[j] in [row0[j]]:
                    ok = False
                    break
            if not ok:
                continue
            for row2 in permutations([1,2,3,4]):
                ok = True
                for j in range(4):
                    if row2[j] in [row0[j], row1[j]]:
                        ok = False
                        break
                if not ok:
                    continue
                for row3 in permutations([1,2,3,4]):
                    ok = True
                    for j in range(4):
                        if row3[j] in [row0[j], row1[j], row2[j]]:
                            ok = False
                            break
                    if ok:
                        squares.append([row0, row1, row2, row3])
    return squares

print('Generating latin squares...')
squares = generate_latin_squares()
print(f'Total latin squares: {len(squares)}')

# 对于每个格子，添零方式：k=0(不添), k=1(添1个零->*10), k=2(添2个零->*100), k=3(添3个零->*1000)
# d * 10^k 的可能值: d, 10d, 100d, 1000d

def solve():
    solutions = []
    for sq in squares:
        # 每个格子有4种添零选择 (k=0,1,2,3)
        # 16个格子，4^16 = 2^32 太多了
        # 需要剪枝：按行/列约束逐步搜索
        
        # 用回溯法
        grid_k = [[None]*4 for _ in range(4)]  # 每个格子的k值
        
        def backtrack(pos):
            if pos == 16:
                # 检查所有行列
                for i in range(4):
                    s = sum(sq[i][j] * (10 ** grid_k[i][j]) for j in range(4))
                    if s != row_sums[i]:
                        return None
                for j in range(4):
                    s = sum(sq[i][j] * (10 ** grid_k[i][j]) for i in range(4))
                    if s != col_sums[j]:
                        return None
                return [row[:] for row in grid_k]
            
            i, j = pos // 4, pos % 4
            d = sq[i][j]
            for k in range(4):  # k=0,1,2,3
                grid_k[i][j] = k
                val = d * (10 ** k)
                
                # 剪枝：检查第i行是否已满且和是否匹配
                if j == 3:  # 行结束
                    row_sum = sum(sq[i][jj] * (10 ** grid_k[i][jj]) for jj in range(4))
                    if row_sum != row_sums[i]:
                        continue
                
                # 剪枝：检查第j列是否已满且和是否匹配
                if i == 3:  # 列结束
                    col_sum = sum(sq[ii][j] * (10 ** grid_k[ii][j]) for ii in range(4))
                    if col_sum != col_sums[j]:
                        continue
                
                result = backtrack(pos + 1)
                if result is not None:
                    return result
            
            grid_k[i][j] = None
            return None
        
        result = backtrack(0)
        if result is not None:
            solutions.append((sq, result))
            break  # 找一个解就够了
    
    return solutions

print('Solving...')
sol = solve()
if sol:
    sq, ks = sol[0]
    print('\n=== SOLUTION ===')
    print('Grid (digits):')
    for row in sq:
        print(row)
    print('\nZero-padding exponents (k where digit -> digit*10^k):')
    for row in ks:
        print(row)
    print('\nActual values (digit * 10^k):')
    for i in range(4):
        print([sq[i][j] * (10**ks[i][j]) for j in range(4)])
    print('\nRow sums:', [sum(sq[i][j]*(10**ks[i][j]) for j in range(4)) for i in range(4)])
    print('Col sums:', [sum(sq[i][j]*(10**ks[i][j]) for i in range(4)) for j in range(4)])
else:
    print('No solution found with k in {0,1,2,3}')
