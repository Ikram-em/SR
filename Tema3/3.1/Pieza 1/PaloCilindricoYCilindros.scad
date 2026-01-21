// PaloCilindricoYCilindros.scad
// Autor: Ikram El Mabrouk Morhnane (UO301848)
// Fecha: 11-11-2025
// Descripción: Módulo que genera un palo cilíndrico principal y dos cilindros pequeños a los lados

module PaloCilindricoYCilindros() {

    // Parámetros del cilindro principal
    cilindro_largo = 85;   
    cilindro_radio = 2.5;  

    // Parámetros de los cilindros pequeños
    radio_pequeno = 5;
    grosor_pequeno = 2;
    radio_hueco_pequeno = 2.5;
    distancia_pequenos = 34; // separación desde el eje central

    union() {
       
        // Cilindro principal horizontal
        rotate([90,0,0])
        color("lightblue")
            cylinder(h = cilindro_largo, r = cilindro_radio, $fn=100, center=true);

        // Cilindro pequeño izquierdo
        translate([0, -distancia_pequenos, 0])
            rotate([90,0,0])
            difference() {
                 color("lightblue")
                cylinder(h = grosor_pequeno, r = radio_pequeno, center=true, $fn=100);
                cylinder(h = grosor_pequeno + 2, r = radio_hueco_pequeno, center=true, $fn=100);
            }

        // Cilindro pequeño derecho
        translate([0, distancia_pequenos, 0])
            rotate([90,0,0])
            difference() {
                 color("lightblue")
                cylinder(h = grosor_pequeno, r = radio_pequeno, center=true, $fn=100);
                cylinder(h = grosor_pequeno + 2, r = radio_hueco_pequeno, center=true, $fn=100);
            }
    }
}


