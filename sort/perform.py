import random
import time

# start_selection = time.time()
def selectionSort(S) -> None:
    for i in range(len(S)):
        smallest = i
        for j in range(i, len(S)):
            if S[i] > S[j]:
                smallest = j
            S[i], S[smallest] = S[smallest], S[i]

# end_selection = time.time()
# select_Time = end_selection - start_selection

if __name__ == '__main__':
    sList = []
    while len(sList) <= 30000:
        num = random.randint(0, 99)
        sList.append(num)

    # print(f'정렬 전: {sList}')
    start_selection = time.time()
    selectionSort(sList)
    end_selection = time.time()
    # print(f'정렬 후: {sList}')
    print(f"{end_selection - start_selection:.5f}")