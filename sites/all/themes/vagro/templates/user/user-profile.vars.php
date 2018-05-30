<?php

function vagro_preprocess_user_profile(&$vars)
{
  $vars['username'] = empty($vars['elements']['#account']->realname) ? $vars['elements']['#account']->name : $vars['elements']['#account']->realname;
}