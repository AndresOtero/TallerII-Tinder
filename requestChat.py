# -*- coding: utf-8 -*-
"""
Created on Mon May 23 07:59:04 2016

@author: ediaz
"""


import requests
import json

chat = { "to" : "APA91bHun4MxP5egoKMwt2KZFBaFUH-1RYqx...", "notification" : { "title" : "Nuevo mensaje de Camila", "body" : "Hola, como andas?" }, "data" : { "type" : "2", "chat_room_id" : "123", "message_id" : "12", "message": "Hola, como andas?", "created_at": "2016-mm-dd" } }
dataChatPost_json = json.dumps(chat)

cabecera = {            
            "Content-Type": "application/json",
            "Authorization": "key=AIzaSyAYrHnfzOKfO4y1FxSUK5V-7tuQM4BqnE4"
        }

print "\n CHAT"
url='http://localhost:8000/chat/'
print url
print "post"
print "Va a imprimir lo q tiene dataChatPost_json"
print dataChatPost_json
response = requests.post(url, headers=cabecera,data=dataChatPost_json)