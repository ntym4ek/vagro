(function ($) {
    Drupal.behaviors.post = {
        attach: function (context, settings) {


            // ------------------------------- Форма  ----------------------------------------------
            // спрятать кнопки до фокуса на тексте
            $('.post-form').once(function(){
                var $message = $('.post-form textarea').val();
                if ($message === '') $('.form-actions').hide();
                $('textarea[name="message"]').focusin(function() {
                    $('.form-actions').show();
                });
            });
        }
    };
})(jQuery);