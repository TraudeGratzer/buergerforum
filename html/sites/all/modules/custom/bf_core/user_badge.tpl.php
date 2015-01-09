<?php
/**
 * @file
 * Provides view for nav bar user badge.
 *
 * $picture - Markup of the user's profile picture.
 * $realname - Real name field. Defaults to unique name if unavailable.
 * $name - Unique user name.
 * $links - Array of useful links.
 *    'dashboard' - Link to the user's page.
 *    'edit_profile' - Link to edit user's profile.
 *    'logout' - Logout link.
 */
?>

<?php if (user_is_logged_in()): ?>
<div id="oa-user-badge">
  <div class="dropdown btn-group pull-right">
    <div class="dropdown-toggle btn clearfix pull-right user-badge <?php print $btn_class; ?>" id="user-badge-dropdown" data-toggle="dropdown">
        <?php print $realname; ?>
        <?php print $picture; ?>
    </div>
    <div class="dropdown-menu" role="menu" aria-labelledby="section-dropdown">
      <ul>
        <li><?php print l(t('Profile'), $links['dashboard']); ?></li>
        <li><?php print l(t('Edit profile'), $links['edit_profile']); ?></li>
        <li><?php print l(t('Log out'), $links['logout']); ?></li>
      </ul>
    </div>
  </div>
</div>
<?php else: ?>
  <script type="text/javascript">
    (function($) {
      $( document).ajaxStart(function( event, xhr, settings ) {
        var global = 0;
        $.ajax({url: Drupal.settings.basePath + 'is_user', success: function (data) {
          if (data) {
            if (data>0) {
              document.location.href = Drupal.settings.basePath;
              window.alert=function(){return false;}
            }
          }
        }
        });
      });
    }(jQuery));
  </script>
  <div>
    <a href="<?php print $login; ?>" class="btn <?php print $btn_class; ?>"><?php print t('Login'); ?></a>
  </div>
<?php endif; ?>
