h, m = map(int, input().split(':'))
h = 0 if h + 1 == 24 else h + 1
print('{0}:{1}'.format(h, m))