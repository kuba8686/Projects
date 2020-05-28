
<?php
echo 
	'<td width="280" valign="top" align="left">';
	
if ($row['Promocja'] == 'ssz') {
	echo '<b><font size="2px" color="red">POLECANE: </font></b>';
}

	
echo 	
	'<a href="index.php?view=telebimy&woj='.$row['wojewodztwo'].'&telebim='.$row['numer'].'">
	<h3>'.$row['Nazwa'].' - '.$row['Powierzchnia ekranu'].'</h3></a>';
	
if ($row['Promocja'] == 'ssz') {
	echo '<center><img align="center" height="80" src="images/bezposr_small.jpg"><br><br></center>';
}
	
	echo'
	
			<a href="index.php?view=telebimy&woj='.$row['wojewodztwo'].'&telebim='.$row['numer'].'"><img title="Telebim Ekran LED '.$row['Nazwa'].'" width="424" height="320" src="images/lok/small/'.$row['numer'].'_1.jpg"/></a>
	      
		<font size="1px">
			<b>Lokalizacja:</b> '.$row['Miasto'].'<br>'.$row['Lokalizacja'].'<br>
			<b>Powierzchnia ekranu:</b> '.$row['Powierzchnia ekranu'].'
			<b><br>Natê¿enie w strefie emisji:</b><br>'.$row['natezenie'].'
			</font>
	
			
	</td>';
			?>