a, b = map(int, input().split())
r = a - b
if a < b:
    r = b - a
print(r)