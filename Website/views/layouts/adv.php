 <head>
 <link rel="stylesheet" href="css/global3.css">
	
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.5.1/jquery.min.js"></script>
	<script src="js/slides.min.jquery.js"></script>
	<script>
		$(function(){
		
			$('#slides').slides({
				preload: true,
		
				preloadImage: 'img/loading.gif',
				play: 5000,
				pause: 2500,
				hoverPause: true,
				animationStart: function(current){
					$('.caption').animate({
						bottom:-35
					},100);
					if (window.console && console.log) {
						// example return of current slide number
						console.log('animationStart on slide: ', current);
					};
				},
				animationComplete: function(current){
					$('.caption').animate({
						bottom:0
					},200);
					if (window.console && console.log) {
						// example return of current slide number
						console.log('animationComplete on slide: ', current);
					};
				},
				slidesLoaded: function() {
					$('.caption').animate({
						bottom:0
					},200);
				}
				 
	
			});
		});
	</script>
</head>
<body>
	<div id="container">
		<div id="example">
			<a href="index.php?view=promocja_szczecin"><img src="img/new-ribbon.png" width="130" height="130" id="ribbon"></a>
			<div id="slides">
				<div class="slides_container">
					 <?php
		$result = mysql_query("SELECT * FROM Ekrany WHERE id='{$tytol2}'");
		$row = mysql_fetch_array($result);
		if (isset($_GET['telebim']) === true){

			 if ($row['Promocja'] == 'sz') {
			echo '<div class="slide">
						<a href="index.php?view=telebimy&telebim='.$row['numer'].'&woj='.$row['Województwo'].'"><img src="images/slideshow/'.$row['numer'].'.png" width="580" height="270" title="Telebim Ekran LED '.$row['Nazwa'].', '.$row['Powierzchnia ekranu'].'"></a>
						<div class="caption" style="bottom:0">
							<p>Telebim Ekran LED > '.$row['Nazwa'].', '.$row['Powierzchnia ekranu'].'</p>
						</div></div>';
			
			
			
			
			
			
			
			}
			}

		$zliczanie = 1;
		
		$result = mysql_query("SELECT * FROM Ekrany WHERE Promocja='sz' OR Promocja='ssz' ORDER BY RAND() LIMIT 4");
		while ($row = mysql_fetch_array($result)) {
		echo '<div class="slide">
						<a href="index.php?view=telebimy&telebim='.$row['numer'].'&woj='.$row['wojewodztwo'].'"><img src="images/slideshow/'.$row['numer'].'.png" width="580" height="270" title="Telebim Ekran LED '.$row['Nazwa'].', '.$row['Powierzchnia ekranu'].'"></a>
						<div class="caption" style="bottom:0">
							<p>Telebim Ekran LED > '.$row['Nazwa'].', '.$row['Powierzchnia ekranu'].'</p>
						</div></div>';
		}
		$tytol2 = empty($_GET['telebim'] ) ? 'nic' : $_GET['telebim'].'';
		
		?>
	
					
					
					
				
			
			
				
				</div>
				
			</div>
			<a href="index.php?view=telebimy"><img src="img/example-frame.png" width="898" height="341" title="Reklama na ekranach LED" id="frame"></a>
			  
		</div>

	</div>
</body>
 <link rel="stylesheet" href="css/style.css">