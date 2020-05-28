 <div id="bottomcontenttop"></div>
 <div id="bottomcontent">
	<div class="main">
		<h1>Nasi Klienci:</h1>
		<br>
		<?php
		mysql_query("UPDATE realizacje SET los=MD5(RAND())");
		$result = mysql_query("SELECT * FROM realizacje ORDER BY kolejnosc");
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
	</div>
  
  


