(function ($, Drupal, window, document, undefined) {

    Drupal.behaviors.gard = {
        attach: function (context, settings) {

            // Autoexpand textarea
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
        }
    }
})(jQuery, Drupal, this, this.document);