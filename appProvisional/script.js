document.addEventListener('DOMContentLoaded', function() {
    // Selecciona todos los sliders
    const sliders = document.querySelectorAll('.slider');

    // Función para actualizar el valor mostrado
    function actualizarValor(e) {
        const slider = e.target;
        const valorId = 'valor_' + slider.id; // Construye el ID del elemento que muestra el valor
        const valorDisplay = document.getElementById(valorId);
        valorDisplay.textContent = slider.value;
    }

    // Añade el evento 'input' a cada slider
    sliders.forEach(function(slider) {
        slider.addEventListener('input', actualizarValor);
    });
});
document.addEventListener("DOMContentLoaded", function() {
    // Dirección IP del ESP32
    const esp32IP = "192.168.0.15";

    // Función para configurar el control de servo
    function setupServoControl(servoId, sliderId, valorId) {
        const slider = document.getElementById(sliderId);
        const valor = document.getElementById(valorId);

        slider.addEventListener("input", function() {
            let angle = slider.value;
            valor.textContent = angle;

            fetch(`http://${esp32IP}/set${servoId}?angle=${encodeURIComponent(angle)}`, {
                method: 'GET'
            })
            .then(response => {
                if (!response.ok) {
                    console.error(`Error al ajustar el ángulo del servo ${servoId}`);
                }
            })
            .catch(error => {
                console.error('Error en la solicitud HTTP:', error);
            });
        });
    }

    // Configurar el control para cada servo
    setupServoControl("BaseServo", "base_brazo", "valor_base_brazo");
    setupServoControl("BrazoServo", "hombro_brazo", "valor_hombro_brazo");
    setupServoControl("CodoServo", "codo_brazo", "valor_codo_brazo");
    setupServoControl("MunecaServo", "muneca_brazo", "valor_muneca_brazo");
    setupServoControl("PinzaServo", "pinza_brazo", "valor_pinza_brazo");
});