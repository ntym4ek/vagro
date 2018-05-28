(function ($) {
    Drupal.behaviors.post = {
        attach: function (context, settings) {

            // вставка отзывов в popup
            $(".post-actions-button").each(function(i, obj) {
                $(this).popover({
                    html: true,
                    content: function() {
                        return $('.post-actions-container').html();
                    }
                });
            });

            $('.post-form').once(function(){
                $('.form-actions').hide();
                $('textarea[name="message"]').focusin(function() {
                    $('.form-actions').show();
                });
            });
        }
    };
})(jQuery);