(function ($, Drupal, window, document, undefined) {

    Drupal.behaviors.gard = {
        attach: function (context, settings) {

            // ------------------------------- Autoexpand textarea ----------------------------------------------------
            // Applied globally on all textareas with the "autoExpand" class
            $(document)
                .one('focus.autoExpand', 'textarea.autoExpand', function () {
                    var savedValue = this.value;
                    this.value = '';
                    this.baseScrollHeight = this.scrollHeight;
                    this.value = savedValue;
                })
                .on('input.autoExpand', 'textarea.autoExpand', function () {
                    var minRows = this.getAttribute('data-min-rows') | 0, rows;
                    this.rows = minRows;
                    rows = Math.ceil((this.scrollHeight - this.baseScrollHeight) / 16);
                    this.rows = minRows + rows;
                });


            // ------------------------------- Popovers --------------------------------------------------------------
            // содержимое можно задать атрибутом data-content родительского элемента или динамически в js
            // т.к. в атр. некоторое содержимое не положить, будем подставлять при наведении, если есть соответсвующий
            // элемент с контентом
            $(".popover-button").each(function(i, obj) {
                $(this).popover({
                    html: true,
                    content: function() {
                        $content = $(this).parent().find('.popover-container');
                        return $content.html();
                    }
                });
            });
        }
    }
})(jQuery, Drupal, this, this.document);