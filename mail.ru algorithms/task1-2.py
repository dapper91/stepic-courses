n = int(input())
A = [int(val) for val in input().split()]
B = [int(val) for val in input().split()]

def find_max_pair(A, B):
	partial_max	= []
	max_val, max_ind = A[0], 0

	for ind, val in enumerate(A):
		max_val, max_ind = max((max_val, max_ind), (val, ind), key = lambda pair: pair[0])
		partial_max.append((max_val, max_ind))

	max_sum, i, j = partial_max[0][0] + B[0], 0, 0
	for b_ind, ((a, a_ind), b) in enumerate(zip(partial_max, B)):
		max_sum, i, j = max((max_sum, i, j), (a+b, a_ind, b_ind), key = lambda triplet: triplet[0])

	return i, j

print(*find_max_pair(A, B))