Manual de usuario
=================
Para comunicar con el shared server se utilizan requests http. Las especificaciones de las requests estan en 
`Especificacion de Api <https://docs.google.com/document/d/144GVnoWe4m9Kgcws2r8ZRZdRQm4i0yN8DmTPEqreVYE/edit?ts=56e5aa7c#>`_

Usuarios
--------
* Obtener  todos los usuarios. Request `get` a `<http://tander.herokuapp.com/users>`_
* Obtener un usuario particular. Request `get` a `<http://tander.herokuapp.com/users/user_id>`_
* Alta de un usuario. Request `post` a `<http://tander.herokuapp.com/users>`_
* Modificacion de campos de un usuario. Request `put` a `<http://tander.herokuapp.com/users/user_id>`_
* Cambio de foto de perfil. Request `put` a `<http://tander.herokuapp.com/users/user_id/photo>`_
* Eliminacion de usuario. Request `delete` a `<http://tander.herokuapp.com/users/user_id>`_


Intereses
---------
* Listado de intereses. Request `get` a `<http://tander.herokuapp.com/interests>`_
* Alta de interes. Request `post` a `<http://tander.herokuapp.com/interests>`_
* Baja de interes. Request `delete` a `<http://tander.herokuapp.com/interests/interest_id>`_
* Modificacion de interes. Request `delete` a `<http://tander.herokuapp.com/interests/interest_id>`_

Categorias
----------
* Listado de categorias. Request `get` a `<http://tander.herokuapp.com/categories>`_
* Alta de categoria. Request `get` a `<http://tander.herokuapp.com/categories>`_
* Baja de categoria. Request `delete` a `<http://tander.herokuapp.com/categories/category_id>`_
* Modificacion de categoria. Request `delete` a `<http://tander.herokuapp.com/categories/category_id>`_

Extras
------
* Eliminacion de todos los usuarios de la base de datos, incluidos sus intereses y sus ubicaciones. Request `delete` a `<http://tander.herokuapp.com/borrarBase>`_
