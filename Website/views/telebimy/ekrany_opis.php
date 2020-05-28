<?php

echo 

'
<div class="ekran_op">

<a href="index.php?view=telebimy&woj='.$row['Województwo'].'&telebim='.$row['numer'].'">
	<h1>'.$row['Nazwa'].'</h1></a>
			<img height="125" src="images/lok/'.$row['numer'].'_1.jpg"/> <img height="125" src="images/lok/'.$row['numer'].'_2.jpg"/><br>
	      
			
			<b>Lokalizacja:</b> '.$row['Lokalizacja'].'
			<b>Powierzchnia ekranu:</b> '.$row['Powierzchnia ekranu'].'
			<b><br>Natê¿enie w strefie emisji:</b> '.$row['natezenie'].'<br><b>---</b><br>

</div>




'



	;


?>