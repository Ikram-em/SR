

// Autor: Ikram El Mabrouk Morhnane (UO301848)
// Fecha: 11-11-2025
// Placa rectangular mediana con dos agujeros alineados


rect_largo = 50;  // Largo en el eje X
rect_ancho = 2;  // Ancho en el eje Y
rect_alto = 1;    // Alto en el eje Z

diametro_agujero_rect = 7; // Diámetro de cada agujero
margen_agujero_x = 10;
margen_agujero_y = 10; // Para centrar la fila de agujeros en Y

module rectangulo_simple_con_agujeros(r_largo, r_ancho, r_alto, d_agujero, m_x, m_y) {
    centro_y = r_ancho / 2; 

    difference() {
        color("lightblue")
            cube([r_largo, r_ancho, r_alto]);
        translate([m_x, centro_y, -1])
            cylinder(h = r_alto + 2, r = d_agujero / 2, $fn = 30);
        translate([r_largo - m_x, centro_y, -1])
            cylinder(h = r_alto + 2, r = d_agujero / 2, $fn = 30);
    }
}


   // rectangulo_simple_con_agujeros();

