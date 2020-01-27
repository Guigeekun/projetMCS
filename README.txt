# projetMCS
doc:
https://docs.google.com/document/d/1VsM6Zfl9sbjXiDXxwkaqvveIs2nQSCHjpigMlbZlnlA/edit
workflow:
https://docs.google.com/drawings/d/1KGbCR4jeErHqSzMvok1op0EM3-G_UHkV78crcK9QEdI/edit?usp=sharing

# Usage :
Compilez les sources :
        `gcc client.c -o client`
        `gcc server.c -o server`
        `./server`
        `./client {ip address (ex:127.0.0.1)} {port}`
        `./client {ip address (ex:127.0.0.1)} {port}`
Le port est modifiable via PORT_SVC dans shared.h, fixé à 7000 par defaut
Le port PORT_SVC+1 sera utilisé par l'host
L'adresse est modifiable via INADDR_SVC dans shared.h, fixé à 127.0.0.1 par defaut

## Doxygen :
Ce projet utilise Doxygen http://www.doxygen.nl/
Utilisez        `doxygen configdox` pour générer la doc.
Si Doxygen n'est pas installé, utilisé      `sudo apt-get install doxygen`

## Langage :
Pour ce projet nous utiliserons le langage C

## Déroulement d’une partie :
le plateau est constitué de 7 colonnes et de 5 lignes
chaque joueur, à tour dans rôle choisi une colonne dans laquelle mettre un jeton qui se place à l’endroit le plus bas disponible.
Un joueur gagne la partie s’il possède 4 jetons alignés (diagonales incluses).

## Serveur :
Le serveur doit d’abord attendre la connection de deux joueurs pour les mettre en communication, il désigne un ’host’ et un ‘client’ à qui il transmet l’ip de l’host
ensuite le serveur peut recréer une communication en attendant d’autre joueur.

## Client :
Un client (le premier à s’être connecté) est désigné comme ‘Host’ il lancera le mode serveur.
le deuxième client lancera le mode client.
L’host crée un canal d’écoute en attendant la connection du client, le client se connecte avec les infos transmises par le serveur(adresse IP).
La partie peut commencer:
les deux joueurs affichent le plateau, le joueur désigné comme ‘Host’ joue en premier.  Pour placer un jeton le joueur doit entrer le numéro de la colonne voulue. Une fois le coup joué  ‘l’Host’ vérifie les conditions de victoire. Si elles se sont pas remplies la partie continue jusqu’à ce qu’elles le soient. Lorsque les conditions sont remplies le joueur dont ce n’est pas le tour voit dans un premier temps le plateau de jeu puis un message de défaite.

Une fois la partie terminée ‘l’Host ‘ ferme la socket d’écoute et le client quitte l’application!;

## Note : 
        dans la doc server.c sera nommé le serveur de matchmaking
        le premier client connecté sera nommé l'host
        le second client sera nommé le client
