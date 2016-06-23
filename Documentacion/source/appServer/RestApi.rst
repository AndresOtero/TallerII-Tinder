RestApi
=======

Para comunicar con el app server se utilizan requests http. Las especificaciones de las requests estan en 
`Especificacion de RestApi <https://docs.google.com/document/d/1XcMEDqwGhejQDGJv3rfjrBiuqx6NyNTbgXmal9zrH7A/edit?usp=sharing>`_

Usuarios
--------
* Obtener  todos los usuarios. Request `get` a `<http://tander.herokuapp.com/users>`_
* Obtener un usuario particular. Request `get` a `<http://dir_appServer/users/user_id>`_
* Alta de un usuario. Request `post` a `<http://dir_appServer/users>`_
* Modificacion de campos de un usuario. Request `put` a `<http://dir_appServer/users/user_id>`_
* Cambio de foto de perfil. Request `put` a `<http://dir_appServer/users/user_id/photo>`_
* Eliminacion de usuario. Request `delete` a `<http://dir_appServer/users/user_id>`_

Match
-----
* El usuario likeo una foto de otro. Request `post` a `<http://dir_appServer/match>`_
* Obtener candidatos para likear. Request `het` a `<http://dir_appServer/match>`_

Token
-----
* Crear un Token. Request `post` a `<http://dir_appServer/token>`_
* Eliminar un Token. Request `delete` a `<http://dir_appServer/token>`_
* Iniciar secion con un token. Request `post` a `<http://dir_appServer/token/singin>`_

Chat
----
* Crear un mensaje. Request `post` a `<http://dir_appServer/chat>`_
* Obtener todos los chats. Request `get` a `<http://dir_appServer/chat>`_
* Obtener todos los mensajes de un chat. Request `get` a `<http://dir_appServer/chat/IdChat-MessageId>`_
* Mandar que hasta un cierto mensaje la conversacion fue vista . Request `post` a `<http://dir_appServer/chat/read>`_
