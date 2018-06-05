<?php

function vagro_preprocess_flag(&$vars)
{
  // добавить кнопке классы bootstrap
  $vars['flag_classes_array'] = array_merge($vars['flag_classes_array'], array('btn', 'btn-primary'));
}