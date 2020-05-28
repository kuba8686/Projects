  <div id="bottomcontenttop"></div>
  <div id="bottomcontent">
   <?php
   //polaczenie do bazy danych
   $rel_nr = empty($_GET['rel_nr'] ) ? '' : $_GET['rel_nr'].''; 
		$result = mysql_query("SELECT * FROM realizacje WHERE id_rel='{$rel_nr}' ORDER BY kolejnosc DESC LIMIT 0, 1000");
				$row = mysql_fetch_array($result);	

		// KONIEC
		?>
    <div class="main">
      <h2><a href="index.php?view=realizacje">Realizacje</a> > <?php echo ''.$row['Reklamodawca'].' ('.$row['Czas'].')'   ?></h2>
     <p>
	<table width="100%">
	<?php
	
	echo '
<tr>
	<td width="440">';
	
	if ($row['Spot'] != "") {
		echo '<iframe width="420" height="300" src="http://www.youtube.com/embed/'.$row['Spot'].'?rel=0" frameborder="0" allowfullscreen></iframe><br><br></td>';	
	} else {
		echo '<a href="images/dowodowe/'.$row['id_rel'].'/T.jpg"><img width="420" height="300" src="images/dowodowe/'.$row['id_rel'].'/T.jpg"></a><br><br></td>';
	}
	
	
	
	echo '
	<td ALIGN=left vALIGN=top>'; 
	
	
	
	$photo = "images/realizacje/logo_" . $row['id_rel'] . ".png";  
	if (file_exists($photo) === true) {
		if ($row['www']!= "") {
				echo '<a target="_blank" href="http://'.$row['www'].'">';
			}
		echo '<img title="'.$row['Reklamodawca'].'" src="images/realizacje/logo_'.$row['id_rel'].'.png" height="50"><br></a><br>';
		
	}
	
	echo'
	
	
	<b>Reklamodawca:<br></b> '.$row['Reklamodawca'].'<br>';
	
	if ($row['www']!= "") {
	
		echo '<a target="_blank" href="http://'.$row['www'].'">'.$row['www'].'</a></br></br>';
	
	}
	
	echo'
	<b>Lokalizacja kampanii:<br></b> '.$row['Lokalizacja'].'<br>
	<b>Termin kampanii:<br></b> '.$row['Czas'].'<br>
	<b>D³ugo¶æ spotu:<br></b> '.$row['dlugosc'].'<br>
	
	<b>Ekrany:<br></b>';
	$result_e = mysql_query("SELECT * FROM tab_l WHERE id_rel='{$row['id_rel']}'");
	
		while ($row_e = mysql_fetch_array($result_e)) {
		
		$result_e2 = mysql_query("SELECT * FROM Ekrany WHERE id='{$row_e['id_ek']}' ORDER BY Nazwa ASC");
		$row_e2 = mysql_fetch_array($result_e2);
		echo '<a href="index.php?view=telebimy&woj='.$row_e2['Województwo'].'&telebim='.$row_e2['numer'].'">'.$row_e2['Nazwa'].'<br>';
		}
		
	
	
	
	
	echo '</td>';
	
	
	
	
echo'</tr>';
	
	
	


?>
</table>
</p>
<?php
if ($row['fotkidowodowe_il']!= 0) {
	$ile = $row['fotkidowodowe_il'];
	echo '<p><b>Zdjêcia z realizacji kampanii:</b></p><br>';
		for ($i = $ile; $i>0; $i--) {
				echo '<a href="images/dowodowe/'.$row['id_rel'].'/'.$i.'.jpg"><img src="images/dowodowe/'.$row['id_rel'].'/'.$i.'.jpg" width="110" height="80"></a>&nbsp';
		
		}
	
		
}
?>
<p><a href="index.php?view=realizacje">Pozosta³e realizacje</a></p>
    </div>
  

