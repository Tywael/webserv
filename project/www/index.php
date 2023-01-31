<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <title>Webserve</title>
    <link rel="apple-touch-icon" sizes="180x180" href="public/favicon/apple-touch-icon.png">
    <link rel="icon" type="image/png" sizes="32x32" href="public/favicon/favicon-32x32.png">
    <link rel="icon" type="image/png" sizes="16x16" href="public/favicon/favicon-16x16.png">
    <link rel="manifest" href="public/favicon/site.webmanifest">
    <link rel="mask-icon" href="public/favicon/safari-pinned-tab.svg" color="#373e3e">
    <meta name="msapplication-TileColor" content="#ffffff">
    <meta name="theme-color" content="#ffffff">
    <link rel="stylesheet" href="src/stylesheets/main.css">
</head>
<body>

<header>
    <div class="container">
        <h1 class="uppercase">
            <a href="/index.html">Webserv - Testing page</a>
        </h1>
    </div>
</header>

<main>
    <section class="container">
        <p>
            HTTP/1.1 <a href="https://fr.wikipedia.org/wiki/Hypertext_Transfer_Protocol">(Hypertext Transfer
            Protocol)</a> est un protocole sans état.
        </p>
        <p>
            Cela signifie que le serveur ne garde aucune information sur les requêtes précédentes. Cela permet
            d'augmenter la sécurité et la rapidité du serveur.
        </p>
        <p>

            Cependant, cela peut poser des problèmes pour les applications qui nécessitent de garder des informations
            sur les requêtes précédentes.

            <br/>Pour cela, le protocole HTTP propose des cookies.
        </p>
        <p>
            Ceci est une page de test pour le projet Webserv. Les tests suivants sont disponibles :
        </p>
    </section>
    <section class="container">
        <ul>
            <li>
                <p class="text-info">
                    <a href="/methods/get.html" class="blue">GET</a><br/> Est utilisé pour récupérer des informations à partir du serveur
                    donné en utilisant un URI donné. Les requêtes utilisant GET ne doivent récupérer que des données et
                    n'ont aucun autre effet sur les données.
                </p>
            </li>
            <li>
                <p class="text-info">
                    <a href="/methods/post.html" class="green">POST</a><br/> Est utilisé pour envoyer des données au serveur, par exemple,
                    des informations sur les clients, le téléchargement de fichiers, etc. à l'aide de formulaires HTML.
                </p>
            </li>
            <li>
                <p class="text-info">
                    <a href="/methods/delete.html" class="red">DELETE</a><br/> Est utilisé pour supprimer la ressource spécifiée.
                </p>
            </li>
        </ul>
    </section>
</main>

<footer>
    <div class="container">
        <p>&#169;2023 - Webserv -</p>
        <ul class="authors">
            <li><a href="https://github.com/BolleCola">BolleCola</a></li>
            <li><a href="https://github.com/Tywael">Tywael</a></li>
            <li><a href="https://github.com/MarJC5">MarJC5</a></li>
        </ul>
    </div>
</footer>

</body>
</html>
