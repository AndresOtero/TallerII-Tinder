import requests
import json

url = 'http://localhost:8000/users'
data = { 
"user":"andy"
} 

data_json = json.dumps(data)
print "url bien"
print "put"
response = requests.put(url, data=data_json)
print response
print response.json()	
print "post"
response = requests.post(url, data=data_json)
print response
#print response.json()
print "get"
response = requests.get(url, data=data_json)
print response
#print response.json()
print "delete"
response = requests.delete(url, data=data_json)
print response
#print response.json()
print "url mal"
url = 'http://localhost:8000/ole'
print "put"
response = requests.put(url, data=data_json)
print response
print "post"
response = requests.post(url, data=data_json)
print response
print "get"
response = requests.get(url, data=data_json)
print response
print "delete"
response = requests.delete(url, data=data_json)
print response
