import bs4
from bs4 import BeautifulSoup
import requests

for counter in range(0, 23):
	pageurl = "http://www.asos.com/women/lingerie-nightwear/cat/?cid=6046&page=" + str(counter)
	page = requests.get(pageurl)
	print("Page " + str(counter) + " with URL:" + pageurl)

	# Successful?
	if page.status_code == 200:
		print("Successfully opened webpage.")
		soup = BeautifulSoup(page.content, "html.parser")
		for child in soup.find_all(attrs={"data-auto-id": "productTileImage"}):
			url = child['src']
			i = url.find("?")
			url = url[:i]
			nurl = url + "?$XL$?$XXL$&wid=800&fmt=jpeg&qlt=100,0"
			k = url.rfind("/")
			filename = "O:\\Download2\\" + url[k+1:-6] + ".jpg"
			r = requests.get(nurl)
			with open(filename, "wb") as output:
			  	output.write(r.content)

