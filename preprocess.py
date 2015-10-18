import re
import sys

keywords = []
operators = []
delimiters = []
headers = []
loops = ['for', 'while', 'do']

def create(filename):
	list_x = []
	with open(filename) as f:
		for w in f:
			w = w.replace('\n','')
			list_x.append(w)
	return list_x

keywords = create('keywords_c++.txt')
operators = create('operators_c++.txt')
delimiters = create('delimiters_c++.txt')
headers = create('headers_c++.txt')

fw = open('sample_out.cpp','w')
t = ''
variables = []

with open(sys.argv[1]) as f:
	for line in f:
		i = 0
		while i < len(line):
			c = line[i]
			if c in operators or c in delimiters:
					fw.write(c)

			elif c.isdigit():
				fw.write(c)

			elif c.isalpha():

				while c.isalpha():
					t += c
					i += 1
					c = line[i]

				th = '<'+t+'>'
				if t in loops:
					fw.write('LOOP')

				elif t in keywords:
					#print("keyword written ",t)
					fw.write(t+' ')

				elif th in headers:
					#print("header file written ",th)
					fw.write(t)

				else:
					#print("t not written ",t)
					variables.append(t)
					x = variables.index(t)
					fw.write('V'+str(x)+' ')

				t = ''
				i -= 1
			i += 1
		fw.write('\n')
