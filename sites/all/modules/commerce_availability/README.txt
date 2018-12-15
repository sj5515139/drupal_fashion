/**
 * README for Commerce Availability
 *
 * @link: http://drupal.org/project/commerce_availability (project page)
 *
 */

The Commerce Availability module is a booking system for rental products. 
It provides an easy way of using a datetime picker field on a line item 
to show and change states automatically of an availability calendar field 
in a type of a Drupal Commerce's product variation.

This version is based on 7.x-4.1 version of availability_calendar module 
and tested with Drupal Commerce Kickstart 2 distribution.


Features
--------
- Adds a new "blocked" state to the default availability calendar states.
- Updates states when the checkout is completed, a product is added or removed
from the cart, and when an order expires or its status changes.
- Adds the datetime field for the event day in the commerce_line_item_table
view of commerce_line_item module.
- Adds a rule action to delete states on expired orders. It requires the
commerce_cart_expiration module.
- Hides quantity field in Commerce add to cart confirmation and Shopping cart
form views, and doesn't allow more than one same product in the cart.
- Offers configuration to extend shipping management on days off and holidays.
Whether the first or last day of the shipment period is holiday or a day off,
the module adds a extra day to extend shipping management.
- Adds a new "offline" status order for manual editing in orders management.
- Modifies orders management view to show the event day and allows adding days 
event from the orders management for order lines manually entered.


Integration with Drupal and contrib modules
------------------------------------------
You only need to add:
- A datetime popup field in a line item
- An availability calendar field in a type of a Drupal Commerce's product 
variation.


Settings
--------
admin/config/system/commerce-availability


Dependencies
-----------
availability_calendar
date
date_popup
editableviews
commerce_cart
commerce_line_item
commerce_cart_expiration
