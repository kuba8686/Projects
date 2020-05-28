  <div id="bottomcontenttop"></div>

    <div id="bottomcontent">
	
	<h1>Pomiary z ARDUINO</h1>
	<br>
<?php
if (isset($_GET['ilosc'])) {
	$il = $_GET['ilosc'];
} else {
	$il = 30;
}


$result = mysql_query("SELECT * FROM arduino ORDER BY data  DESC  LIMIT 0, {$il}"); ?>
	

	<?php
	$zliczanie = 1;
	while ($row = mysql_fetch_array($result)) {
		echo '    ><b> ';
		echo $zliczanie;
		echo '</b> < <b>';
		echo $row['data'];
		echo '  </b>Temp.:<b> ';
		echo $row['temp'];
		echo '\'C  </b>Wilg.:<b> ';
		echo $row['wilg'];
		echo '%  </b>Jas.:<b> ';
		echo $row['jas'];
		echo '%  </b>IP:<b> ';
		echo $row['ip'];
		echo '  </b><br>';
		$zliczanie++;
	}
	
$result = mysql_query("SELECT ip FROM arduino ORDER BY data  DESC  LIMIT 0, 1"); 
while ($row = mysql_fetch_array($result)) {
		echo '<a href="http://';
		echo $row['ip'];
		echo '">ARDUINO SSRV</a>';
		
	}
?>

