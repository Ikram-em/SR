// Autor: Ikram El Mabrouk Morhnane (UO301848)
// Fecha: 11-11-2025
// Bloque con agujero horizontal

// ==========================
// Parámetros del bloque
// ==========================
bloque_largo = 60;
bloque_ancho = 16;
bloque_alto = 12;

// Parámetros cilindro
cilindro_radio = 3;
cilindro_largo = bloque_largo + 15;

// ==========================
// Módulo bloque con agujero horizontal
// ==========================
module bloque_con_agujero() {
    difference() {
        color("lightblue")
            cube([bloque_largo, bloque_ancho, bloque_alto], center=true);
        rotate([0, 90, 0])
            cylinder(h = cilindro_largo, r = cilindro_radio, $fn = 100, center=true);
    }
}

//bloque_con_agujero();
