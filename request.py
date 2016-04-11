import requests
url = 'http://localhost:8000/api/v1/sum'
data = ' {"n1": 1.0}'
print "url bien"
print "put"
response = requests.put(url, data=data)
print response
print response.json()	
print "post"
response = requests.post(url, data=data)
print response
print response.json()
print "get"
response = requests.get(url, data=data)
print response
print response.json()
print "delete"
response = requests.delete(url, data=data)
print response
print response.json()
print "url mal"
url = 'http://localhost:8000/ole'
print "put"
response = requests.put(url, data=data)
print response
print "post"
response = requests.post(url, data=data)
print response
print "get"
response = requests.get(url, data=data)
print response
print "delete"
response = requests.delete(url, data=data)
print response
