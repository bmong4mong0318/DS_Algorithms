import random
import time
import sys
sys.setrecursionlimit(100000)


# 선택 정렬: 오름차순
def selectionSort(S) -> None:
    for i in range(len(S)):
        smallest = i
        for j in range(i, len(S)):
            if S[i] > S[j]:
                smallest = j
            S[i], S[smallest] = S[smallest], S[i]

# 버블 정렬: 오름차순
def bubbleSort(S) -> None:
    n = len(S)
    for i in range(n - 1, 0, -1):
        for j in range(i):
            if S[j+1] < S[j]:
                S[j+1], S[j] = S[j], S[j+1]

# 삽입 정렬: 오름차순
def insertionSort(S) -> None:
    for i in range(1, len(S)):
        for j in range(i, 0, -1):
            if S[j-1] > S[j]:
                S[j-1], S[j] = S[j], S[j-1]

# 쉘 정렬: 오름차순
def  shellSort(S) -> None:
    n = len(S)
    interval = n // 2
    while interval > 0:
        for j in range(interval, n):
            tmp = S[j]
            h = j - interval
            while h >= 0 and S[h] > tmp:
                S[h + interval] = S[h]
                h -= interval
            S[h + interval] = tmp
        interval //= 2

# 2) 고급 정렬 알고리즘: 퀵.병합 정렬
# 퀵 정렬: 오름차순
def  quickSort(S, first:int, last:int) -> None:
    if first >= last: return
    pivot = first
    left, right = first + 1, last

    while left <= right:
        while left <= last and S[left] <= S[pivot]:
            left += 1
        while right > first and S[right] >= S[pivot]:
            right -= 1
        if left > right:
            S[right], S[pivot] = S[pivot], S[right]
        else:
            S[left], S[right] = S[right], S[left]

    quickSort(S, first, right - 1)
    quickSort(S, right + 1, last)

# 병합 정렬: 오름차순
def  mergeSort(S) -> None:
    if len(S) <= 1:
        return S

    mid = len(S) // 2
    left = mergeSort(S[:mid])
    right = mergeSort(S[mid:])

    result = []
    while left and right:
        if left[0] < right[0]:
            result.append(left.pop(0))
        else:
            result.append(right.pop(0))

    while left:
        result.append(left.pop(0))
    while right:
        result.append(right.pop(0))

    return result

if __name__ == '__main__':
    sList = []
    while len(sList) <= 30000:
        num = random.randint(0, 99)
        sList.append(num)

    start = time.time()
    selectionSort(sList)
    finish = time.time()
    print(f'선택 정렬: {finish - start:.5f} 초')

    start = time.time()
    bubbleSort(sList)
    finish = time.time()
    print(f'버블 정렬: {finish - start:.5f} 초')

    start = time.time()
    insertionSort(sList)
    finish = time.time()
    print(f'삽입 정렬: {finish - start:.5f} 초')

    start = time.time()
    shellSort(sList)
    finish = time.time()
    print(f'쉘 정렬: {finish - start:.5f} 초')

    start = time.time()
    mergeSort(sList)
    finish = time.time()
    print(f'병합 정렬: {finish - start:.5f} 초')
    
    start = time.time()
    quickSort(sList, 0, len(sList) - 1)
    finish = time.time()
    print(f'퀵 정렬: {finish - start:.5f} 초')
