<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8" />
    <title>Webserv - CGI PHP</title>
    <link rel="apple-touch-icon" sizes="180x180" href="/public/favicon/apple-touch-icon.png">
    <link rel="icon" type="image/png" sizes="32x32" href="/public/favicon/favicon-32x32.png">
    <link rel="icon" type="image/png" sizes="16x16" href="/public/favicon/favicon-16x16.png">
    <link rel="manifest" href="/public/favicon/site.webmanifest">
    <link rel="mask-icon" href="/public/favicon/safari-pinned-tab.svg" color="#373e3e">
    <meta name="msapplication-TileColor" content="#ffffff">
    <meta name="theme-color" content="#ffffff">
    <link rel="stylesheet" href="/src/stylesheets/main.css">
</head>

<body class="cgi-page">

<header>
    <div class="container grid">
        <h1 class="uppercase">
            <a href="/index.html">Webserv - CGI PHP</a>
        </h1>
        <ul class="ul-inline">
            <li><a href="/methods/get.html">Get</a></li>
            <li><a href="/methods/post.html">Post</a></li>
            <li><a href="/methods/delete.html">Delete</a></li>
            <li><a href="/php/index.php">CGI</a></li>
        </ul>
    </div>
</header>
<main>
    <div class="container">
        <h2>POST - Upload</h2>
        <p>Envoi de fichier sur le serveur.</p>
        <form action="upload.php" method="POST" enctype="multipart/form-data">
            <div class="form-fields">
                <label for="file">Upload: </label>
                <input type="file" name="the_file" id="file"/>
            </div>
            <input type="submit" class="btn btn--success" value="Envoyer" />
        </form>
    </div>
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