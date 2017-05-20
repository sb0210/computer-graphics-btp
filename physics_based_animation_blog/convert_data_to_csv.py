f = open("all_blogs.txt","r")
f1 = open("all_blogs.csv","w")

got_content = False
for line in f:
	if(line[0]=="*"):
		got_content = False	
		print ""
	if(got_content):
		print line.replace("\n",""),	
	if(line[0:6]=="Date :"):
		print line[7:].replace("\n",""),"##",
	if(line[0:5]=="Tag :"):
		print line[6:].replace("\n",""),"##",
	if(line[0:7]=="Title :"):
		print line[8:].replace("\n",""),"##",
	if(line[0:6]=="Link :"):
		print line[7:].replace("\n",""),"##",
	if(line[0:8]=="Content:"):
		got_content=True			
