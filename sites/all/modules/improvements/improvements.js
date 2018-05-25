(function ($) {
  Drupal.behaviors.improvements = {
    attach: function (context, settings) {
      // Text format confirmation
      $('.filter-wrapper .filter-list', context).each(function () {
        var $select = $(this);

        if ($select.data('value')) {
          return;
        }

        $select.data('value', this.value);

        $select.change(function () {
          var oldValue = $select.data('value');
          if (oldValue == 'raw_html' && oldValue != this.value) {
            if (!confirm('Смена формата может привести к потере форматирования и изменению html кода. Вы действительно хотите сменить формат?')) {
              this.value = oldValue;
            }
          }
          $select.data('value', this.value);
        });
      });

      // Tab indent
      $('.text-format-wrapper .form-textarea', context).once('tab-indent').keydown(function (e) {
        if(e.keyCode === 9) {
          var textarea = this;
          var selectionStart = textarea.selectionStart;
          var selectionEnd = textarea.selectionEnd;

          textarea.value = textarea.value.substring(0, selectionStart) + "\t" + textarea.value.substring(selectionEnd);
          textarea.selectionStart = textarea.selectionEnd = selectionStart + 1;
          e.preventDefault();
        }
      });

      // Fix reCaptcha on AJAX forms
      if ('grecaptcha' in window && context !== document) {
        $('.g-recaptcha:empty', context).each(function () {
          grecaptcha.render(this, $(this).data());
        });
      }
    }
  };

  // Add new progress type
  if (Drupal.ajax) {
    var ajaxBeforeSend = Drupal.ajax.prototype.beforeSend;
    var ajaxSuccess = Drupal.ajax.prototype.success;
    var ajaxError = Drupal.ajax.prototype.error;

    Drupal.ajax.prototype.beforeSend = function(xmlhttprequest, options) {
      ajaxBeforeSend.apply(this, arguments);
      if (this.progress.type == 'class') {
        this.progress.targetElement = $(this.progress.target);
        this.progress.targetElement.addClass(this.progress.class);
      }
    };

    Drupal.ajax.prototype.success = function(response, status) {
      ajaxSuccess.apply(this, arguments);
      if (this.progress.type == 'class') {
        this.progress.targetElement.removeClass(this.progress.class);
      }
    };

    Drupal.ajax.prototype.error = function(xmlhttprequest, uri, customMessage) {
      ajaxError.apply(this, arguments);
      if (this.progress.type == 'class') {
        this.progress.targetElement.removeClass(this.progress.class);
      }
    };
  }
})(jQuery);
