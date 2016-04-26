#############################################################
# Archivo Dockerfile 
# Basado en una imagen de Ubuntu
#############################################################

# Establece la imagen de base a utilizar para Ubuntu
FROM ubuntu

# Establece el autor (maintainer) del archivo
MAINTAINER tandermatch

# Actualización de la lista de fuentes del repositorio de aplicaciones por defecto
RUN apt-get update

# Instalar Cmake
RUN apt-get install -y cmake

# Instalar git
RUN apt-get install -y git

# Puerto para exponer (por defecto: 11211)
EXPOSE 11211

# Establece el usuario para ejecutar el demonio Memcached
USER daemonApplServer

# Establece el punto de entrada para los binarios de Memcached
ENTRYPOINT applServer
