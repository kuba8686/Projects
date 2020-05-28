

  <div id="bottomcontenttop"></div>
  <div id="bottomcontent">
   
    <div class="main">
  
	  <?php 
	  ini_set("default_charset","ISO-8859-2");
	  $spr_id == $_GET['telebim'];
	 
//polaczenie do bazy danych
		
		
		
	
		$result = mysql_query("SELECT * FROM Ekrany WHERE numer='{$tytol2}'");
		$row = mysql_fetch_array($result);
		
		// KONIEC
// zag³êbienie w stronie
$tytol2 = empty($_GET['telebim'] ) ? 'nic' : $_GET['telebim'].'';

if (isset($_GET['view']) === true) {
	if (isset($_GET['promocje']) === true) {
	
	}
				
				
	if (isset($_GET['woj']) === true) {
	
	
			if (isset($_GET['telebim']) === true) {
					 
					
				
				
				echo '<b><h2><a href="index.php?view='.$view.'">'.$podtytol.'</a><a href="index.php?view='.$view.'&woj='.$woj.'">TEST TEST</a></b>> '.$row['Nazwa'].'</h2>';
				} 
			if (isset($_GET['telebim']) === false) {
				echo '<b><h2><a href="index.php?view='.$view.'">'.$podtytol.'</a></b> > '.$t_woj.'</h2>';
				}
	}
	if (isset($_GET['promocje']) === false) {
		if (isset($_GET['woj']) === false) {
			if (isset($_GET['telebim']) === false) {
					echo '<h1>'.$podtytol.'</h1>';
					
			}
		}
	}
	

	
}

?>



  </div></div>   <div id="bottomcontentbtm"></div>
<div id="bottomcontenttop"></div>
    <div id="bottomcontent">
   
    <div class="main">
   
	<?php
if (isset($_GET['woj']) === false) {
	$result = mysql_query("SELECT count(nazwa) AS ilosc FROM Ekrany");
	$row = mysql_fetch_array($result); 
	$zliczanie=$row['ilosc'];
	}
if ($woj=='top') {
	$result = mysql_query("SELECT count(nazwa) AS ilosc FROM Ekrany WHERE Promocja='sz' OR Promocja='nsz'");
	$row = mysql_fetch_array($result); 
	$zliczanie=$row['ilosc'];

}
if (isset($_GET['woj']) === true && $woj!='top') {
	$result = mysql_query("SELECT count(nazwa) AS ilosc FROM Ekrany WHERE Województwo='{$woj}'");
	$row = mysql_fetch_array($result); 
	$zliczanie=$row['ilosc'];
	}
	
if (isset($_GET['woj']) === true) {
echo '<h2>'.$t_woj.' ('.$zliczanie.'):</h2>';
}
if ($zliczanie == '0') {
echo '<p>Brak ekranów w tym województwie w naszej bazie.</p>';
}

?>	
		  

<?php


//zliczanie



$tytol2 = '1';



	
?>
<?php  
//promocja szczecin

if ($woj == 'wszystkie' || $woj == 'top') {

//echo '<p style="text-align:center"><a href="index.php?view=promocja_szczecin"><img src="images/pr2.png" alt="" class="pic" width="580" height="60" /></a></p>';
$zl_ek = 0;

while ($zl_ek<=6){
	echo '<table bgcolor="#fff499" width="100%" align="center"><tr>';
	$result = mysql_query("SELECT * FROM Ekrany WHERE Promocja='ssz' ORDER BY id ASC LIMIT {$zl_ek}, 2");
	while ($row = mysql_fetch_array($result)) {
	include ('views/telebimy/ekrany_opis_alt_pr.php');
	}
	echo '
	</tr>
	</table>';
	$zl_ek = $zl_ek+2;;
	}
$zl_ek = 0;

while ($zl_ek<=6){
	echo '<table width="100%" align="center"><tr>';
	$result = mysql_query("SELECT * FROM Ekrany WHERE Promocja='sz' OR Promocja='sz' ORDER BY id ASC LIMIT {$zl_ek}, 2");
	while ($row = mysql_fetch_array($result)) {
	include ('views/telebimy/ekrany_opis_alt_pr.php');
	}
	echo '
	</tr>
	</table>';
	$zl_ek = $zl_ek+2;;
	}
$zl_ek = 0;
	
while ($zl_ek<=6){
	echo '<table width="100%" align="center"><tr>';
	$result = mysql_query("SELECT * FROM Ekrany WHERE Promocja='nsz' ORDER BY id ASC LIMIT {$zl_ek}, 2");
	while ($row = mysql_fetch_array($result)) {
	include ('views/telebimy/ekrany_opis_alt_pr.php');
	}
	echo '
	</tr>
	</table>';
	$zl_ek = $zl_ek+2;;
	}
$zl_ek = 0;
}

$zl_ek = 0;
while ($zl_ek<=$zliczanie){
	echo '<table><tr>';
	
	$result = mysql_query("SELECT * FROM Ekrany WHERE wojewodztwo='{$woj}' ORDER BY nazwa ASC LIMIT {$zl_ek}, 3");
	while ($row = mysql_fetch_array($result)) {
	include ('views/telebimy/ekrany_opis_alt.php');
	
	
	}
		
	echo '
	</tr>
	</table>';
	$zl_ek = $zl_ek+3;;
	}
	
	
	?>
	
	
	<?php
	
	
	
	
	
	?>
		
		
		


    </div>
