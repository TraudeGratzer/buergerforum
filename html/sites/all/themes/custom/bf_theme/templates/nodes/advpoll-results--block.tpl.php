<?php

/**
 * @file
 * Default template for wrapping bar results - includes count of votes.
 *
 * Variables available:
 * - $nid: The nid of the poll
 * - $cancel_form: Provides a form for deleting user's votes when they have 
 *   permission to do so.
 * - $bars: The output of all styled bars displaying votes.
 * - $total: Total number of votes.
 * - $voted: An array indicating which unique choice ids were selected by the user.
 *
 */
?>
<div class="poll" id="advpoll-<?php print $nid; ?>">

    <?php print $bars; ?>
    <?php print $cancel_form; ?>
</div>
