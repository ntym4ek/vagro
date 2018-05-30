<?php

/**
 * определить получателя Записи
 *
 * два типа получателей: Пользователь и Группа
 * пользователь может отправить себе, другому пользователю и группе
 * группа отправляет только себе
 *
 * определение выполняется по текущему расположению на сайте (по пути)
 *
 * @return array - массив с типом и ID получателя (контекста)
 */
function _get_post_context()
{
  $uid = $GLOBALS['user']->uid;

  // отправка себе Пользователю
  $pages = ['stream', 'user', 'user/' . $uid];
  if ($page_match = _check_pages_match($pages)) {
    return array(
      'rectype' => 'user',
      'recid' => $uid,
    );
  }

  // отправка другому Пользователю
  if (arg(0) == 'user' && is_numeric(arg(1)) && arg(1) != $uid) {
    return array(
      'rectype' => 'user',
      'recid' => arg(1),
    );
  }

  // todo отправка Группе


  // если ничего не подошла, вернуть контекст по умолчанию
  return array(
    'rectype' => 'user',
    'recid' => $uid,
  );
}