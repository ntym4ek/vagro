<?php

global $user;

$author_photo = $fields['sender_pic']->handler->original_value;
$author_url = '/user/' . $fields['name']->raw;
$author_title = $fields['name']->handler->original_value;
?>

<div class="post-card">
  <header class="post-card-author">
    <?php print $author_photo; ?>
    <div class="post-author-info">
      <h5><a href="<?php print $author_url; ?>"><?php print $author_title; ?></a></h5>
      <div class="post-date"><?php print $post_date; ?></div>
    </div>
  </header>

  <div class="post-card-content">
    <a href="<?php print $post_url; ?>">
      <div><?php print $content['field_text'][0]['#markup']; ?></div>
    </a>
  </div>

  <?php if (!empty($post_image)): ?>
    <div class="post-card-image">
      <a href="<?php print $post_url; ?>">
        <img src="<?php print $post_image; ?>" class="img-responsive" >
      </a>
    </div>
  <?php endif; ?>

  <footer>
  </footer>
</div>