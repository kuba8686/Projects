  <div id="bottomcontenttop"></div>
  <div id="bottomcontent">
   <?php
   //polaczenie do bazy danych
		$result = mysql_query("SELECT * FROM realizacje ORDER BY kolejnosc ASC LIMIT 11, 100");
		$zl_rel = 0;			

		// KONIEC
		?>
    <div class="main">
      <h1>Realizacje archiwalne</h1>
     <p>
	<table width="100%">
	<?php
	while ($row = mysql_fetch_array($result)) {
	if($zl_rel<=150) {
		echo '

		<tr height="175">
		<td ALIGN=left vALIGN=top width="220"><a href="index.php?view=realizacje_ind&rel_nr='.$row['id_rel'].'"><img src="http://i3.ytimg.com/vi/'.$row['Spot'].'/mqdefault.jpg" width="210" height="150"></a><br><br></td>	
		<td ALIGN=center vALIGN=middle width="130">
		';
		if ($row['www']!= "") {

		echo '<a target="_blank" href="http://'.$row['www'].'">';

		}
		$photo = "images/realizacje/logo_" . $row['id_rel'] . ".png";  
		if (file_exists($photo) === true) {
			$image = $photo;
			echo '<img title="'.$row['Reklamodawca'].'" src="'.$image.'" width="100"></td>';
		} else {
			echo '</td>';
		}
		echo '
		<td ALIGN=left vALIGN=top >

		<b>Reklamodawca:<br></b> '.$row['Reklamodawca'].' <a href="index.php?view=realizacje_ind&rel_nr='.$row['id_rel'].'">--></a><br>
		<b>Lokalizacja kampanii:<br></b> '.$row['Lokalizacja'].'<br>
		<b>Czas kampanii:<br></b> '.$row['Czas'].'<br>
		<b>D��ugo�� spotu:<br></b> '.$row['dlugosc'].'<br></td>
		<td ALIGN=left vALIGN=top><b>Ekrany:<br></b>';
		$result_e = mysql_query("SELECT * FROM tab_l WHERE id_rel='{$row['id_rel']}'");

		while ($row_e = mysql_fetch_array($result_e)) {

		$result_e2 = mysql_query("SELECT * FROM Ekrany WHERE id='{$row_e['id_ek']}' ORDER BY Nazwa ASC");
		$row_e2 = mysql_fetch_array($result_e2);
		echo '<a href="index.php?view=telebimy&woj='.$row_e2['Wojew�dztwo'].'&telebim='.$row_e2['numer'].'">'.$row_e2['Nazwa'].'<br>';
		}







		echo '</td>
		</tr>';
	}
	$zl_rel = $zl_rel + 1;	
}
?>
</table>
</p>
<p><a href="index.php?view=realizacje">Zobacz najnowsze lokalizacje</a></p>
    </div>

