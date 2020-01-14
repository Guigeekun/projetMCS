# projetMCS
doc:
https://docs.google.com/document/d/1VsM6Zfl9sbjXiDXxwkaqvveIs2nQSCHjpigMlbZlnlA/edit
workflow:
https://docs.google.com/drawings/d/1KGbCR4jeErHqSzMvok1op0EM3-G_UHkV78crcK9QEdI/edit?usp=sharing

# Langage :
Pour ce projet nous utiliserons le langage C

# Déroulement d’une partie :
le plateau est constitué de 7 colonnes et d’une infinité de lignes (ou alors on limite ?)
chaque joueur à tour dans rôle choisi une colonne dans laquelle mettre un jeton qui se place à l’endroit le plus bas disponible de la colonne.
Un joueur gagne la partie s’il possède 4 jetons alignés (diagonal incluse).

# Serveur :
Le serveur doit d’abord attendre la connection de deux joueurs pour les mettre en communication, il désigne un ’host’ et un ‘client’ à qui il transmet l’ip et le port de l’host
ensuite le serveur peut recréer une communication en attendant d’autre joueur.

# Client :
Un client (le premier à s’être connecté) est désigné comme ‘Host’ il lancera le mode serveur 
le deuxième client lancera le mode client.
L’host crée un canal d’écoute en attendant la connection du client, le client se connecte avec les infos transmises par le serveur( adresse IP et port).
La partie peut commencer:
les deux joueurs affichent le plateau, le joueur désigné comme ‘Host’ joue en premier.  Pour placer un jeton le joueur doit entrer le numéro de la colonne voulue. Une fois le coup joué  ‘l’Host’ vérifie les conditions de victoire. Si elles se sont pas remplies la partie continue jusqu’à ce qu’elles le soient. Lorsque les conditions sont remplies le joueur dont ce n’est pas le tour  voit dans un premier temps le plateau de jeu ( pour voir le coup qui lui a fait perdre la partie )  ainsi que la notification de défaite.

Une fois la partie terminée ‘l’Host ‘ ferme la socket d’écoute et le client quitte l’application!;

# Note : 
        dans la doc server.c sera nommé le serveur de matchmaking
        le premier client connecté sera nommé l'host
        le second client sera nommé le client