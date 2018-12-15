<?php include('checksum.php'); ?>
<?php include('encdec_paytm.php'); ?>

<?php
	$secret = 'CFAp7zjqKvJI&yt@';    // put your secret key here
	$post_variables = Array(
		"MID" =>  $_POST['MID'],
		"ORDER_ID" =>  $_POST['ORDER_ID'],
		"CUST_ID" => $_POST['CUST_ID'],
		"TXN_AMOUNT" => $_POST['TXN_AMOUNT'],
		"CHANNEL_ID" =>  $_POST['CHANNEL_ID'],
		"INDUSTRY_TYPE_ID" =>  $_POST['INDUSTRY_TYPE_ID'],
		"WEBSITE" =>  $_POST['WEBSITE'],
    );
	if($_POST['CALLBACK_MODE'] == '1')
	{
		$post_variables["CALLBACK_URL"] = $_POST['CALLBACK_URL'];
	}
	//$all = Checksum::getAllParams();

	//var_dump($post_variables);
		//error_log("AllParams : ".$all);
		error_log("Secret Key : ".$secret);
	//$checksum = Checksum::calculateChecksum($secret, $all);
	$checksum = getChecksumFromArray($post_variables, $secret);

?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>paytm</title>
<script type="text/javascript">
function submitForm(){
			var form = document.forms[0];
			form.submit();
		} 
</script>
</head>
<body onload="javascript:submitForm()">
<center>
<table width="500px;">
	<tr>
		<td align="center" valign="middle">Do Not Refresh or Press Back <br/> Redirecting to paytm</td>
	</tr>
	<tr>
		<td align="center" valign="middle">
		<?php if($_POST['MODE']==1)
		{
			$paytm_url = 'https://secure.paytm.in/oltp-web/processTransaction';
		}
		else
		{
			$paytm_url = 'https://pguat.paytm.com/oltp-web/processTransaction';
		}?>
			<form action="<?php echo $paytm_url; ?>" method="post">
				<?php
				
					echo  "<input type='hidden' name='MID' value='". $_POST['MID'] ."'/>";
					echo  "<input type='hidden' name='ORDER_ID' value='". $_POST['ORDER_ID']."'/>";
					echo "<input type='hidden' name='WEBSITE' value='".  $_POST['WEBSITE'] ."'/>";
					echo "<input type='hidden' name='INDUSTRY_TYPE_ID' value='".  $_POST['INDUSTRY_TYPE_ID'] ."'/>";
					echo "<input type='hidden' name='CHANNEL_ID' value='".  $_POST['CHANNEL_ID'] ."'/>";
					echo "<input type='hidden' name='TXN_AMOUNT' value='". $_POST['TXN_AMOUNT'] ."'/>";
					echo "<input type='hidden' name='CUST_ID' value='". $_POST['CUST_ID'] ."'/>";
					echo  "<input type='hidden' name='txnDate' value='".  $_POST['txnDate'] ."'/>";
					echo  "<input type='hidden' name='CHECKSUMHASH' value='".  $checksum ."'/>";
					if($_POST['CALLBACK_MODE'] == '1')
					{
						echo  "<input type='hidden' name='CALLBACK_URL' value='".  $_POST['CALLBACK_URL'] ."'/>";
					}
				?>
			</form>
		</td>

	</tr>

</table>

</center>
</body>
</html>
