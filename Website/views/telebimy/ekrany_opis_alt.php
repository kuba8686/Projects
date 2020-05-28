
<?php
echo 
	'<td width="285" valign="top" align="left">
	<table>
	<tr height="80">
	<a href="index.php?view=telebimy&woj='.$row['Województwo'].'&telebim='.$row['numer'].'">
	<h3>'.$row['Nazwa'].'</h3></a></tr>
	
			<a href="index.php?view=telebimy&woj='.$row['Województwo'].'&telebim='.$row['numer'].'"><img title="Telebim Ekran LED '.$row['Nazwa'].'" width="280" height="200" src="images/lok/'.$row['numer'].'_1.jpg"/></a>
	      
		<font size="1px">
			<b>Lokalizacja:</b> '.$row['Miasto'].'<br>'.$row['Lokalizacja'].'<br>
			<b>Powierzchnia ekranu:</b> '.$row['Powierzchnia ekranu'].'
			<b><br>Natê¿enie w strefie emisji:</b><br>'.$row['natezenie'].'
			</font>
	</table>
			
	</td>';
			?>