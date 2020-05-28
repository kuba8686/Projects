
  <div id="bottomcontenttop"></div>
  <div id="bottomcontent">
	<div class="main">
		<h1>Nasi klienci:</h1></br>
		<?php
		mysql_query("UPDATE topklienci SET los=MD5(RAND())");
		$result = mysql_query("SELECT * FROM topklienci ORDER BY los ASC LIMIT 0, 4");
		while ($row3 = mysql_fetch_array($result)) {
			$photo = "images/realizacje/logo_" . $row3['id_klienta'] . ".png";  
			if (file_exists($photo) === true) {
				echo '
				<div id="logastale">
					<table height="95%" width="95%">
						<tr align="left" valign="bottom">
							<td align="center" valign="bottom"><a href="index.php?view=realizacje_ind&rel_nr='.$row3['id_klienta'].'"><img src="images/realizacje/logo_'.$row3['id_klienta'].'.png" ></a></td>
						</tr>
					</table>
				</div>';
			} else {
				echo '
				<div id="logastale">
				<table height="95%" width="95%">
						<tr align="center" valign="bottom">
							<td align="center" valign="bottom"><b><a href="index.php?view=realizacje_ind&rel_nr='.$row3['id_klienta'].'">';
														$result2 = mysql_query("SELECT id_rel, Reklamodawca FROM realizacje");
							while ($row4 = mysql_fetch_array($result2)) {
								if ($row3['id_klienta'] == $row4['id_rel']) {
									echo $row4['Reklamodawca'];;
								}
							}
														
							echo'</a></b></td>
						</tr>
					</table>
				</div>';
			}
		}
		mysql_query("UPDATE realizacje SET los=MD5(RAND())");
		$result = mysql_query("SELECT * FROM realizacje ORDER BY los ASC LIMIT 0, 2");
		while ($row4 = mysql_fetch_array($result)) {
			$photo = "images/realizacje/logo_" . $row4['id_rel'] . ".png";  
			if (file_exists($photo) === true) {
				echo '
				<div id="logastale">
					<table height="95%" width="95%">
						<tr align="left" valign="bottom">
							<td align="center" valign="bottom"><a href="index.php?view=realizacje_ind&rel_nr='.$row4['id_rel'].'"><img src="images/realizacje/logo_'.$row4['id_rel'].'.png" ></a></td>
						</tr>
					</table>
				</div>';
			} else {
				echo '<div id="logastale">
				<table height="95%" width="95%">
						<tr align="center" valign="bottom">
							<td align="center" valign="bottom"><a href="index.php?view=realizacje_ind&rel_nr='.$row4['id_rel'].'"><b>'.$row4['Reklamodawca'].'</b></a></td>
						</tr>
					</table>
					</div>';
			}
			
		}
	  
			?>
		
			
			
		<div style="clear: both;"></div>	
		<p class="podpis"><a href="index.php?view=klienci">>> Zobacz wszystkich</a></p>
	</div>
  </div>
  <div id="bottomcontentbtm"></div>
  <br>
  <div id="bottomcontenttop"></div>
  <div id="bottomcontent"> 
	<div class="right">
      <h2><a class="tyt" href="index.php?view=realizacje">Ostatnie realizacje</a></h2>
	  <img src="images/03.jpg" alt="" class="pic" width="270" height="60" />
      <p style="text-indent:0cm" class="thumbs"> 
	  <?php
	  $result = mysql_query("SELECT * FROM realizacje ORDER BY kolejnosc ASC LIMIT 0, 6");
	  while ($row = mysql_fetch_array($result)) {
	  //echo ''.$row['Reklamodawca'].'<br>';
	  echo '<a href="index.php?view=realizacje_ind&rel_nr='.$row['id_rel'].'">';
	  
	  if ($row['Spot'] != "") {
		echo '<img src="http://i3.ytimg.com/vi/'.$row['Spot'].'/mqdefault.jpg" width="110" height="80">';
	  } else {
		  echo '<img width="110" height="80" src="images/dowodowe/'.$row['id_rel'].'/T.jpg">';
	  }
	  
	  echo'</a>'; 
	  
	  }
	  ?>
	   <p class="podpis"><a href="index.php?view=realizacje">>> Zobacz wszystkie</a></p>
    </div>
    <div class="middle">
      <h2>O nas</h2>
      <img src="images/02.jpg" class="pic" width="270" height="60" />
	  <p class="ju"><ul>
	  <li>Jeste¶my profesjonaln± agencj± reklamow± oferuj±c± swoim klientom kompleksow± obs³ugê kampanii reklamowych z wykorzystaniem mo¿liwo¶ci jakie daje wielkoformatowa <a href="index.php?view=ekrany_led">reklama na ekranach LED</a>.</li>
<li>Poprowadzimy Twoj± kampanie przez wszystkie etapy - od <a href="index.php?view=spoty">produkcji spotu reklamowego</a> a¿ do zakoñczenia emisji!</li>
</ul>	 </p>

    </div>
    <div class="left">
      <h1><a class="tyt" href="index.php?view=telebimy">Oferta</a></h1>
      <img src="images/01.jpg" alt="" class="pic" width="270" height="60" />
       <p class="ju"><ul>
	   <li>Sprzeda¿ czasu reklamowego na  <a href="index.php?view=telebimy">Telebimach/ekranach LED</a><li>Profesjonalne no¶niki o wymiarach od 15 do 80 m2<li>Tylko najlepsze lokalizacje (min. centrum Szczecina i Gdañska):
	   </ul></p>
	   <p style="text-indent:0cm; text-align:center; " class="thumbs_e">
	  <?php
	  mysql_query("UPDATE Ekrany SET los=MD5(RAND())");
	  $result2 = mysql_query("SELECT * FROM Ekrany ORDER BY los ASC LIMIT 0, 8");
	  while ($row2 = mysql_fetch_array($result2)) {
	  echo '<a href="index.php?view=telebimy&telebim='.$row2['id'].'&woj='.$row2['Województwo'].'"><img title="Telebim Ekran LED '.$row2['Nazwa'].'" src="images/lok/small/'.$row2['id'].'_1.jpg" width="70" height="50"/></a>'; 
	  }
	  ?></p>
	 <p class="podpis"> <a href="index.php?view=telebimy">>> Zobacz wszystkie</a>
    </div>
  