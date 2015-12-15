def prime_deviders(num):	
	cur = 1
	deviders = []

	while cur <= num:
		cur += 1
		if num%cur == 0:
			deviders.append(cur)		
			num = num/cur
			cur = 1

	return deviders	


for dev in prime_deviders(int(input())):
	print(dev, end=" ")