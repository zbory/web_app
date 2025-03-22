function buttonPressed() {
    $.ajax({
        url: 'api/button_press',
        dataType: 'json',
        success: function(response) {
                if (response != "") {
                    $("#pressCounter").text(response.pressCount);
                }
            }
        }).fail(function(xhr, status, error) {
                console.error('AJAX Error:', status, error);
        }
    );
}