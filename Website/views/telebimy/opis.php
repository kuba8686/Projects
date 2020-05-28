	  <?php //if ($_GET['telebim']=='3') { header('Location: www.wp.pl'); } ?>


  <div id="bottomcontenttop"></div>
  <div id="bottomcontent">
   
    <div class="main">
      <h2>
	  <?php 
//polaczenie do bazy danych
		$result = mysql_query("SELECT * FROM Ekrany WHERE numer='{$tytol2}'");
		$row = mysql_fetch_array($result);
		// KONIEC
// zag³êbienie w stronie


$tytol2 = empty($_GET['telebim'] ) ? 'nic' : $_GET['telebim'].'';
$spr = mysql_query("SELECT count(nazwa) AS ilosc FROM Ekrany WHERE numer='{$tytol2}'");
					$spr_row = mysql_fetch_array($spr); 
					$spr_ek=$spr_row['ilosc'];
					if ($spr_ek == 0) {
					 header('Location: index.php');
					}
if (isset($_GET['view']) === true) {
	if (isset($_GET['promocje']) === true) {
				echo '<b> > <a href="index.php?view='.$view.'">'.$podtytol.'</a></b> > '.$podtytol2.'';
	}
				
				
	if (isset($_GET['woj']) === true) {
			if (isset($_GET['telebim']) === true) {
				echo '<b><a href="index.php?view='.$view.'">'.$podtytol.'</a></b> > '.$row['Nazwa'].'';
				} 
			if (isset($_GET['telebim']) === false) {
				echo '<b> > <a href="index.php?view='.$view.'">'.$podtytol.'</a></b> > '.$t_woj.'';
				}
	}
	if (isset($_GET['promocje']) === false) {
		if (isset($_GET['woj']) === false) {
			if (isset($_GET['telebim']) === false) {
					echo '> '.$podtytol.'';
					
			}
		}
	}
	

	
}

if ($_GET['telebim'] == '1' || $_GET['telebim'] == '5') {
	echo ' <table align="center">
	<tr align="center">
		
		<td align="center" ><img src="images/bez_posrednikow.png" alt="" width="100%" class="pic" /></td>
	</td>
</table>	';
} else {

?>


</h2>
    <table>
	<tr>
		<td align="center" width="282"><img src="images/01.jpg" alt="" class="pic" width="270" height="60" /></td>
		<td align="center" width="282"><img src="images/02.jpg" alt="" class="pic" width="270" height="60" /></td>
		<td align="center" width="282"><img src="images/03.jpg" alt="" class="pic" width="270" height="60" /></td>
	</td>
</table>		

	  <?php }
	// PROMOCJA NA SZCZECIN
	//if ($row['Promocja'] == 'sz') {
	//
	//echo  '<p style="text-align:center"><a href="index.php?view=promocja_szczecin"><img align="center" src="images/pr2.png" title="Reklama Szczecin" class="pic" width="580" height="60" /></a></p>';
	//}
		echo '<h1 class="ope">Reklama Telebim Ekran LED '.$row['Nazwa'].'</h1>'; 
		?>
		
		


		
		
		<?php

if (isset($row['ilosc zdjec']) === false) {
	$zliczaj = '2';
} else {
$zliczaj = $row['ilosc zdjec'];
}
$zliczaj_r = '1';
while ($zliczaj_r<=$zliczaj)  {
echo '<a href="images/lok/'.$tytol2.'_'.$zliczaj_r.'.jpg" title="Telebim Ekran LED '.$row['Nazwa'].' - Zdjêcie '.$zliczaj_r.'" rel="lightbox[galeria]">
			<img width="49%" src="images/lok/small/'.$tytol2.'_'.$zliczaj_r.'.jpg"></a>';
$zliczaj_r++;
}


?>	
		
		
		
		<p><b>Miasto: </b><?php echo ''.$row['Miasto'].' ('.$t_woj.')'; ?></p>
			<p><b>Lokalizacja: </b><?php echo $row['Lokalizacja']; ?></p>
			<p><b>Powierzchnia ekranu: </b><?php echo $row['Powierzchnia ekranu']; ?></p>
			<p><b>Natê¿enie w strefie emisji: </b><?php echo $row['natezenie']; ?></p>
			<p><b>Opis: </b><?php echo $row['Opis']; ?></p>
			<p><a href="<?php echo $row['Google'];?>" target="_blank"/>Zobacz lokalizacjê ekranu w Google Maps</a></p>
	<br>		
	
	<p>Pozosta³e Ekrany:</p>

	<table width="100%">
<tr>
<td width="50%" valign="top">
       <?php	
$result2 = mysql_query("SELECT * FROM Ekrany WHERE numer!='{$tytol2}' ORDER BY nazwa ASC");
		$row = mysql_fetch_array($result2);
		$nnn = $row[2];
		$nnn2 = $row[1];
		echo '<a href="index.php?view=telebimy&woj='.$row['wojewodztwo'].'&telebim='.$nnn2.'">'.$nnn.'</a><br>';
		while ($row = mysql_fetch_array($result2)) {
		echo '<a href="index.php?view=telebimy&woj='.$row['wojewodztwo'].'&telebim='.$row['numer'].'">'.$row['Nazwa'].'</a><br>';
		
		}
		
		?></td>
<td align="right" valign="top"><b>Jeste¶œ zainteresowany wykonaniem spotu reklamowego?!<br>Zobacz <a href="index.php?view=spoty">tutaj.</a></b>

		
		
		  




</td>
</tr>

</table>


	

			

    </div>
