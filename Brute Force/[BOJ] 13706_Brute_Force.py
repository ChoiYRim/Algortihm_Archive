n = int(input())
 
 
def binary_search(target):
    start = 1
    end = target
    while start <= end:
        mid = (start + end) // 2
        if mid ** 2 == target:
            return mid
        elif mid ** 2 > target:
            end = mid - 1
        else:
            start = mid + 1
    return None
 
 
print(binary_search(n))
