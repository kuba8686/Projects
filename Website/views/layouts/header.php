<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<?php  ini_set("default_charset","UTF-8"); ?>


<head>
<?php

switch ($tytol) {

case 'index': $podtytol = ''; break;
case 'aktualnosci': 	$podtytol = 'Aktualno¶ci'; break;
case 'telebimy': 	$podtytol = 'Nasze Telebimy'; break;
case 'spoty': 		$podtytol = 'Spoty Reklamowe'; break;
case 'ekrany_led': 	$podtytol = 'Reklama na Ekranach LED'; break;
case 'kontakt': 	$podtytol = 'Kontakt'; break;
case 'promocje': 	$podtytol = 'Promocje'; break;
case 'mailing':		$podtytol = 'Oferta';break;
case 'wspolpraca':	$podtytol = 'Wspó³praca';break;
case 'realizacje':	$podtytol = 'Realizacje';break;
case 'promocja_szczecin':	$podtytol = 'Oferta Pakietowa';break;
case 'oferta_email':	$podtytol = 'Oferta';break;
case 'mailing1006':	$podtytol = 'Telebim Ekran LED Szczecin Plac ¯o³nierza - Oferta';break;
case 'mailing2208':	$podtytol = 'Szczecin Plac ¯o³nierza - Oferta';break;
case 'realizacje_old': $podtytol = 'Realizacje Archiwalne'; break;
case 'klienci': $podtytol = 'Nasi klienci'; break;

}


if (isset($_GET['telebim']) === true) {
$result = mysql_query("SELECT Nazwa FROM Ekrany WHERE id='{$tytol2}'");
$row = mysql_fetch_array($result);
$t_tytol = 'Telebim Ekran LED '.$row['Nazwa'].' - eliteLED.pl - Reklama na Telebimach i Ekranach LED';
}
else {
$t_tytol = ''.$podtytol.' - eliteLED.pl - Reklama na Telebimach i Ekranach LED';
}
if ($tytol === 'index') {
$t_tytol = 'eliteLED.pl - Reklama na Telebimach i Ekranach LED';
}
echo '<title>'.$t_tytol.'</title>';
?>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
<meta name="description" content="Nowoczesna reklama na ekranach LED" />
  <meta name="keywords" content="reklama, telebimy, ekrany led, ekrany diodowe, ekrany ledowe, szczecin, spot reklamowy" />
<link rel="stylesheet" type="text/css" href="css/style.css" media="all" />
</head>
<body>

<div id="fb-root"></div>
<script>(function(d, s, id) {
  var js, fjs = d.getElementsByTagName(s)[0];
  if (d.getElementById(id)) return;
  js = d.createElement(s); js.id = id;
  js.src = "//connect.facebook.net/pl_PL/sdk.js#xfbml=1&version=v2.9";
  fjs.parentNode.insertBefore(js, fjs);
}(document, 'script', 'facebook-jssdk'));</script>

<?php 
ini_set("default_charset","ISO-8859-2");
if ($_SERVER['REMOTE_ADDR'] != '77.88.154.19') {
		include_once("analyticstracking.php");
	}
	//include_once("analyticstracking.php");
 ?>
<div id="wrapper">
  <div id="header">

     <div id="hright">
	 
	 <a href="https://www.facebook.com/eliteledpl/"><img width="30" height="30" src="images/fb.png"></a>
	 <a href="https://www.youtube.com/eliteLEDpl"><img width="64" height="30" src="images/yt.png"></a>
      <div id="hrighttop">
        <p><b>+48 505 02 07 02 reklama@eliteled.pl</b></p>
		 </div>
      <div id="menu">
        <ul>
			
          <li><a href="index.php">Home</a> |</li>
          <li><a href="index.php?view=telebimy">Telebimy</a> |</li>
          <li><a href="index.php?view=realizacje">Realizacje</a> |</li>
		  <li><a href="index.php?view=klienci">Nasi Klienci</a> |</li>
          
	      <li><a href="index.php?view=kontakt">Kontakt</a></li>

        </ul>
      </div>
    </div>
   <a href="index.php">
   <div id="title">
		
       <p>Nowoczesna Reklama na Ekranach LED</p>
    </div>
	</a>
  </div>