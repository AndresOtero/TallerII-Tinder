# -*- coding: utf-8 -*-
"""
Created on Mon May 23 07:59:04 2016

@author: ediaz
"""

users=["Andy","Ely","Fede"]

def crear_usuarios():
	r={}
	for user in users:
		mail = user+'@gmail.com'
		intereses = [{'value':'Boca', 'category':'Deporte'},{'value':'Cuba','category':'Viajes'}]
		foto = "photo"
		ubicacion = {'latitude':-34.610510, 'longitude':-58.386391}
		user = {'gcm_registration_id':"aaaaaaaaaa",'name':user,'password': "hashed",'interests':intereses,'location':ubicacion,'alias':user,'age':45,'sex':'H','photo_profile':foto,'email':mail}
		urlGetUsers = 'http://192.168.0.200:8080/users/'
		metadata = {'version':"0.1"}
		r['user'] = user
		r['metadata'] = metadata
		dataUserPost_json = json.dumps(r)
		response = requests.post(urlGetUsers,data=dataUserPost_json)
		print response
import requests
import json



tokenAndy={'user':{'email': 'Andy@gmail.com','password': "hashed" } }
tokenAndy_json=json.dumps(tokenAndy)
tokenEly={'user':{'email': 'Ely@gmail.com','password': "hashed" } }
tokenEly_json=json.dumps(tokenEly)
tokenFede={'user':{'email': 'Fede@gmail.com','password': "hashed" } }
tokenFede_json=json.dumps(tokenFede)
tokens=[tokenAndy_json,tokenFede_json,tokenEly_json]
mensaje={'To':'Ely@gmail.com','message':'Holis'}
mensaje_json=json.dumps(mensaje)
urlToken='http://192.168.0.200:8080/token/singin/'
urlChat='http://192.168.0.200:8080/chat/'
urlChat0='http://192.168.0.200:8080/chat/0/'


print "Sing in "
crear_usuarios()
auth={}
for user in users:
	mail = user+'@gmail.com'
	token={'user':{'email': mail,'password': "hashed" } }
	token_json=json.dumps(token)	
	response = requests.post(urlToken,data=token_json)
	print response
	auth[user]={}
	auth[user]["Authorization"] = response.json()["token"]


print "Get mensajes andy"
response = requests.get(urlChat ,headers=auth["Andy"])
print response
print response.json()
print "Get mensajes Ely"
response = requests.get(urlChat ,headers=auth["Ely"])
print response
print response.json()
print "Get mensajes Chat 0"
response = requests.get(urlChat0 ,headers=auth["Ely"])
print response
print "Mensaje de andy a Ely"
response = requests.post(urlChat ,headers=auth["Andy"] ,data=mensaje_json)
print response
print "Mensaje de fede a Ely"
response = requests.post(urlChat ,headers=auth["Fede"] ,data=mensaje_json)
print response