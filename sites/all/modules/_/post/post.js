(function ($) {
    Drupal.behaviors.post = {
        attach: function (context, settings) {


            // ------------------------------- Форма  ----------------------------------------------
            // спрятать кнопки до фокуса на тексте
            $('.post-form').once(function(){
                var $message = $('.post-form textarea').val();
                if ($message === '') $('.post-form .form-actions').hide();
                $('.post-form textarea[name="message"]').focusin(function() {
                    $('.post-form .form-actions').show();
                });
            });
        }
    };
})(jQuery);