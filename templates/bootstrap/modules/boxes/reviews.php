<?php
/**
 * TomatoCart Open Source Shopping Cart Solution
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License v3 (2007)
 * as published by the Free Software Foundation.
 *
 * @package      TomatoCart
 * @author       TomatoCart Dev Team
 * @copyright    Copyright (c) 2009 - 2012, TomatoCart. All rights reserved.
 * @license      http://www.gnu.org/licenses/gpl.html
 * @link         http://tomatocart.com
 * @since        Version 1.1.8
 * @filesource
*/
?>

<!-- box reviews start //-->

<div class="boxNew">
    <div class="boxTitle"><?php echo osc_link_object($osC_Box->getTitleLink(), $osC_Box->getTitle()); ?></div>
    
    <div class="boxContents boxReview"><?php echo $osC_Box->getContent(); ?></div>
</div>

<!-- box reviews end //-->
