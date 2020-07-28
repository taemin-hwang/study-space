family = ['mother', 'father', 'gentleman']

print(family)
len(family)
family.remove('gentleman')
print(family)



prime = [2, 3, 7, 11]
print("Original ", prime)

prime.append(5)
print("Append 5 ", prime)

prime.sort()
print("Sort ", prime)

del prime[3]
print("Delete 3rd element ", prime)

#list append, insert(id, val), extend(append_list)
prime.insert(1, 5)
prime.extend([1, 2, 3, 4])
print(prime)