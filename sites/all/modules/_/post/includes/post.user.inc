<?php


/**
 * функция, возвращающая информацию о сущности User для post_entity_load
 * @return array
 */
function user_post_info($id)
{
  $sen_img_uri = $sen_name = $sen_url = '';
  if ($account = user_load($id)) {
    $sen_img_uri = $account->picture->uri;
    $sen_name = $account->realname;
    $sen_url = url('user/' . $account->uid);
  }

  return array(
    'sen_name' => $sen_name,
    'sen_img_uri' => $sen_img_uri,
    'sen_url' => $sen_url,
  );
}

/**
 * функция, возвращающая по id сущности массив id пользователей, имеющих права на действие
 * @return array of int
 */
function user_entity_access($id, $op = NULL)
{
  // сам пользователь имеет права на все действия
  return array($id);
}
