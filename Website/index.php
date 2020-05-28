
<?php




$controller = 'led';
$view = empty($_GET['view'] ) ? 'index' : $_GET['view'];

//ini_set( 'display_errors', 'On' ); 
//error_reporting( E_ALL );

include_once("resources/init.php");



include ('views/layouts/'.$controller.'.php');


?>