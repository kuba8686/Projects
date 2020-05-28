<?php
$telebim = empty($_GET['telebim'] ) ? 'telebimy' : 'opis';
include ('views/telebimy/'.$telebim.'.php');
?>