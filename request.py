# -*- coding: utf-8 -*-

import requests
import json

url = 'http://localhost:8000/users/1121/'
data = { 
"user": { 
"name": "andy", 
"alias": "a user", 
                          "email": "usuario@usuario.com", 
"interests": [{ 
"category": "music/band", 
"value": "radiohead" 
 
   }, { 
"category": "music/band", 
"value": "pearl jam" 
   },{ 
"category": "outdoors", 
"value": "running" 
   } 
                          ], 
                         "location": {  
                               "latitude": "­121.45356", 
                               "longitude": "46.51119" 
                         } 
} 
} 

data_json = json.dumps(data)
print "url bien"
print url
print "post"
response = requests.post(url, data=data_json)
print response
print response.json()
print "get"
response = requests.get(url, data=data_json)
print response
print "put"
response = requests.put(url, data=data_json)
print response
#print response.json()
print "delete"
response = requests.delete(url, data=data_json)
print response
url='http://localhost:8000/users/1121/photo/'
print "\n photo"
print "put"
response = requests.put(url, data=data_json)
print response
print "\n MATCH"
url='http://localhost:8000/match/'
print url
print "post"
response = requests.post(url, data=data_json)
print response
print "get"
response = requests.get(url, data=data_json)
print response
print "\n CHAT"
url='http://localhost:8000/chat/'
print url
print "post"
response = requests.post(url, data=data_json)
print response

