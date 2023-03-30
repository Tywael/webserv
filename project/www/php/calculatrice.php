<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8" />
    <title>Webserv - POST</title>
    <link rel="apple-touch-icon" sizes="180x180" href="/public/favicon/apple-touch-icon.png">
    <link rel="icon" type="image/png" sizes="32x32" href="/public/favicon/favicon-32x32.png">
    <link rel="icon" type="image/png" sizes="16x16" href="/public/favicon/favicon-16x16.png">
    <link rel="manifest" href="/public/favicon/site.webmanifest">
    <link rel="mask-icon" href="/public/favicon/safari-pinned-tab.svg" color="#373e3e">
    <meta name="msapplication-TileColor" content="#ffffff">
    <meta name="theme-color" content="#ffffff">
    <link rel="stylesheet" href="/src/stylesheets/main.css">
</head>

<body class="post-page">

<header>
    <div class="container grid">
        <h1 class="uppercase">
            <a href="/index.html">Webserv - POST</a>
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
        <h2>POST - CGI</h2>
        <form method="post" action="/php/calculatrice.php">
        		<input type="number" name="num1" required>
        		<select name="operation" required>
        			<option value="add">+</option>
        			<option value="subtract">-</option>
        			<option value="multiply">*</option>
        			<option value="divide">/</option>
        		</select>
        		<input type="number" name="num2" required>
        		<input type="submit" value="Calculate">
        	</form>


        	<?php
        	if ($_SERVER["REQUEST_METHOD"] == "POST") {

                    	if(isset($_GET['num1']) && isset($_GET['num2']) && isset($_GET['operation'])){
                    		$num1 = $_GET['num1'];
                    		$num2 = $_GET['num2'];
                    		$operation = $_GET['operation'];

                    		switch($operation){
                    			case "add":
                    				$result = $num1 + $num2;
                    				break;
                    			case "subtract":
                    				$result = $num1 - $num2;
                    				break;
                    			case "multiply":
                    				$result = $num1 * $num2;
                    				break;
                    			case "divide":
                    				if($num2 == 0){
                    					echo "Cannot divide by zero";
                    				} else {
                    					$result = $num1 / $num2;
                    				}
                    				break;
                    			default:
                    				echo "Invalid operation";
                    				break;
                    		}

                    		if(isset($result)){
                    			echo "Result: " . $result;
                    		}
                    	}
        	}
        	?>

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
