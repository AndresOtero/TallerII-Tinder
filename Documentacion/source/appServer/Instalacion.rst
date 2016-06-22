Instalacion
===========
Para la instalacion se realizaron una serie de scripts para poder correrlo además de un repositorio de docker, los scripts son los siguientes:

* Para instalar los paquetes necesarios para correr el servidor
	``$ ./beforeinstall.sh``
* Para compilar el proyecto y sus pruebas
	``$ ./build.sh``
* Para correr test unitarios
	``$ ./Test.sh``
* Para correr la aplicacion
	``$ ./Tinder.sh``
* Para correr los tests de integracion con el Shared Server
	``$ ./requests.py``