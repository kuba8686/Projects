<?php

//po³±czenie z baz±

include_once("resources/init.php") ;

//podstawowe
$telebimy = 'Nasze telebimy ';
$firma = 'eliteLED.pl';
$max = '45';   //liczba ekranów w bazie danych

$tytol = empty($_GET['view'] ) ? 'index' : $_GET['view'].''; 
$tytol2 = empty($_GET['telebim'] ) ? 'nic' : $_GET['telebim'].'';
$promocje = empty($_GET['promocje'] ) ? 'promocje' : $_GET['promocje'];
$woj = empty($_GET['woj'] ) ? 'wszystkie' : $_GET['woj'];
$rel_nr = empty($_GET['rel_nr'] ) ? '' : $_GET['rel_nr'];
//promocje

switch ($promocje) {
case 'szczecin': $t_promocje = 'Szczecin kompleksowo!';break;

}

//województwa

switch ($woj) {
case 'zachodniopomorskie': 		$t_woj = 'woj. Zachodniopomorskie';	break;
case 'pomorskie': 				$t_woj = 'woj. Pomorskie';			break;
case 'dolnoslaskie': 			$t_woj = 'woj. Dolno?l?skie';		break;
case 'kujawsko': 				$t_woj = 'woj. Kujawsko-Pomorskie';	break;
case 'lubelskie': 				$t_woj = 'woj. Lubelskie';			break;
case 'lubuskie': 				$t_woj = 'woj. Lubuskie';			break;
case 'lodzkie': 				$t_woj = 'woj. £ódzkie';			break;
case 'malopolskie': 			$t_woj = 'woj. Ma³opolskie';		break;
case 'mazowieckie': 			$t_woj = 'woj. Mazowieckie';		break;
case 'opolskie': 				$t_woj = 'woj. Opolskie';			break;
case 'podkarpackie': 			$t_woj = 'woj. Podkarpackie';		break;
case 'podlaskie': 				$t_woj = 'woj. Podlaskie';			break;
case 'slaskie': 				$t_woj = 'woj. ¦l±skie';			break;
case 'swietokrzyskie': 			$t_woj = 'woj. ¦wiêtokrzyskie';		break;
case 'warminsko': 				$t_woj = 'woj. Warmiñsko-Mazurskie';break;
case 'wielkopolskie': 			$t_woj = 'woj. Wielkopolskie';		break;
case 'wszystkie': 				$t_woj = 'Wszystkie ekrany';		break;
case 'top':						$t_woj = 'Ekrany TOP';				break;

}



//zmiana tytu³ów ekranow
$podtytol2 = '';
if (isset($_GET['telebim']) === true) {
$result = mysql_query("SELECT Nazwa FROM Ekrany WHERE id='{$tytol2}'");
$row = mysql_fetch_array($result);
$podtytol2 = $row['Nazwa'];
}
if (isset($_GET['rel_nr']) === true) {
$result = mysql_query("SELECT Reklamodawca FROM realizacje WHERE id_rel='{$rel_nr}' ORDER BY kolejnosc DESC LIMIT 0, 1000");
$row = mysql_fetch_array($result);
$podtytol = $row['Reklamodawca'];
}
if (isset($_GET['promocje']) === true) {
$podtytol2 = $t_promocje;
}
if (isset($_GET['woj']) === true && isset($_GET['telebim']) === false) {
$podtytol2 = $t_woj;
}
if (isset($_GET['mailing1006']) === true) {
$podtytol2 = 'Telebim Ekran LED Szczecin Plac ¯o³nierza - Oferta';
}



//tytu³y podstron


//definicja emaili
$email_k = 'reklama@eliteled.pl'; //formularz kontaktowy
$email_n = 'newsletter@eliteled.pl'; //newsletter
$email_o = 'reklama@eliteled.pl'; //oferta na ekran
$email_m = 'reklama@eliteled.pl'; //mailing




include ('header.php');
if ($view=='index') {
include ('adv.php');
}

$nazwa_pliku = 'views/led/'.$view.'.php';

if (file_exists($nazwa_pliku)) {
    include ('views/led/'.$view.'.php');
} else {
	echo ' <div id="bottomcontenttop"></div><div id="bottomcontent"><div class="main"><p>Strona o podanym adresie nie istnieje</p></div>';
}



include ('footer.php');


?>