<?php

/**
 * @file
 * Used to display a welcome message when a webform is accessed using an encrypted query string.
 *
 * This file may be renamed "secure_prepopulate_welcome_[nid].tpl.php" to target a
 * specific webform on your site. Or you can leave it
 * "secure_prepopulate_welcome.tpl.php" to affect all webforms on your site.
 *
 * Available variables:
 * - $values: An array of key/value pairs that were passed in via query string.
 * - $nid: The nid of the node for which the values apply.
 */

?>
<div id="welcome-back">
  Welcome back <?php print $values['first_name']; ?>. Not <?php print $values['first_name']; ?>? <?php print l('Click here', 'secure-prepopulate/not-me/' . $nid); ?>
</div>
