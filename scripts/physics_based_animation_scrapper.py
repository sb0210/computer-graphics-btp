from bs4 import BeautifulSoup
import requests
i=0
url = "http://www.physicsbasedanimation.com/2013/01/30/closest-point-turbulence-for-liquid-surfaces/"
while(True):
	response = requests.get(url)
	soup = BeautifulSoup(response.text.encode("utf-8","ignore"),'html.parser')

	content = soup.find(id="wrapper")
	divs = content.find_all("div")

	date = soup.find(class_="postmeta").find("a").text
	tag = soup.find(class_="postcats").find("a").text


	heading = divs[5].find("h1").text
	print "Date :", date.encode("utf-8","ignore")
	print "Tag :", tag.encode("utf-8","ignore"), "\n"
	print "Title :", heading.encode("utf-8","ignore")
	print "Link :", url.encode("utf-8","ignore"),"\n"


	post_text = divs[6].text
	print "Content:"
	print post_text.encode("utf-8","ignore")

	link_to_paper = divs[6].find("a")
	if(link_to_paper!=None):
		link_to_paper_link = link_to_paper["href"]
		title = link_to_paper.text.encode("utf-8","ignore")
		print title, link_to_paper_link.encode("utf-8","ignore")

	print ""
	print "********************************************************"
	print ""
	next_urls = soup.find_all(class_="right")
	if(len(next_urls)==0):
		break
	next_url = next_urls[0].find("a")["href"]
	url=next_url
	i=i+1
