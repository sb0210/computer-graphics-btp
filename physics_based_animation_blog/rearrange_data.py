f = open("file.csv",'r')
for line in f:
	data = line.split("##")
	print data[2],"##",data[4].replace("\n",""),"##",data[0],"##",data[1],"##",data[3]