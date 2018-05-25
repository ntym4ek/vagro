<?php

class DrupalH1MetaTag extends DrupalTextMetaTag {
  public function getElement(array $options = array()) {
    $element = array();
    if ($value = $this->getValue($options)) {
      $GLOBALS['improvements']['page_title'] = $value;
    }
    return $element;
  }
}
