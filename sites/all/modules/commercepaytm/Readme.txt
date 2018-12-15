
Payment Module : Paytm
*****************************
   
	 Paytm - Simplifying payments in India 
		
		Our aim is to solve the payment pain points for eCommerce in India.
		
**************************************************************************************		

An installation procedure for the module:
   
		- Get a merchant account from Paytm
		- Unzip the contents of the module (or upload the unzipped folder named commercepaytm) at
		   ../sites/all/modules/commerce/modules/payment/
		- Enable the module at ../admin/build/modules
		- open ../sites/all/modules/commerce/modules/payment/commercepaytm/posttopaytm.php and  ../sites/all/modules/commerce/modules/payment/commerce_paytm/response.php .Then, enter
		  your secret key in both the files.
		- Enable Paytm as a payment method
		- Enter your Paytm Merchant id and Secret key, set the Paytm payment mode 
		   to Live(Value = 1) or Test(Value = 0) and save the changes.
		
		


