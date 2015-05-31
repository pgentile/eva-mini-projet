**Topologie du réseau :** en étoile.

# Les messages #

## Initialisation ##

  * `TIME_IS time` : l'heure du serveur, envoyée à un client qui se connecte
  * `YOUR_ID_IS id` : ID du client assigné par le serveur
  * `CONNECT_ME` : demande de connexion au serveur d'un client

## Informations serveur et clients ##

  * `ARE_YOU_ALIVE` : le serveur demande à un client s'il est en vie.
  * `I_AM_ALIVE client_id` : le client est encore en vie, et l'annonce au serveur.

## Gestion des entités ##

  * `I_NEED_ALL_ENTITIES` : un client demande aux autres clients de lui envoyer toutes les entités présentes.
  * `GET_ENTITY_ID` : demande d'un ID pour une entité
  * `ENTITY_ID_IS entity_id` : réponse du serveur qui transmet au client un ID pour une entité
  * `ADD_ENTITY client_id entity_id time position speed acceleration` : ajout d'une entité par un client, transmise au serveur, puis aux autres clients
  * `REMOVE_ENTITY client_id entity_id` : supression d'une entité, transmise au serveur, puis aux autres clients

## Correction de trajectoire ##

  * `CORRECT client_id entity_id time position speed acceleration` : correction de la trajectoire d'un client

## Formats de données ##

`position`, `speed` et `acceleration` sont des vecteurs 3D, de la forme suivante : `X-Y-Z`.