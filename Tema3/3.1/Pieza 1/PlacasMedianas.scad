// Autor: Ikram El Mabrouk Morhnane (UO301848)
// Placa con L en los bordes y rejilla de agujeros

largo = 60;     
ancho = 40;     
alto = 3;       
filas = 2;
columnas = 4;
diametro_agujero = 7;   

margen_x = 8;
margen_y = 8;

area_x = largo - 2 * margen_x;
area_y = ancho - 2 * margen_y;

espaciado_x = area_x / (columnas - 1);
espaciado_y = area_y / (filas - 1);

// Parámetros para la L hacia arriba y afuera
altura_L = 3; 
ancho_L = 1;    
grosor_L = 1; 

// ==========================
// Módulo placa con L y agujeros (idéntica, solo cambia tamaño)
// ==========================
module placa_con_L_bordes_fuera_y_agujeros() {
    difference() {
        union() {
            // Color azul para toda la placa
            color("lightblue")
            union() {
                // Base con agujeros
                cube([largo, ancho, alto]);

                // L en borde frontal (Y=0)
                translate([0, 0, alto]) {
                    cube([largo, grosor_L, altura_L]);
                    translate([0, -ancho_L, altura_L - grosor_L])
                        cube([largo, ancho_L, grosor_L]); 
                }

                translate([0, ancho - grosor_L, alto]) {
                    cube([largo, grosor_L, altura_L]);
                    translate([0, grosor_L, altura_L - grosor_L])
                        cube([largo, ancho_L, grosor_L]);
                }
            }
        }

        // Agujeros en la base
        for (i = [0 : columnas - 1]) {
            for (j = [0 : filas - 1]) {
                translate([
                    margen_x + i * espaciado_x,
                    margen_y + j * espaciado_y,
                    -1
                ])
                cylinder(
                    h = alto + 2,
                    r = diametro_agujero / 2,
                    $fn = 30
                );
            }
        }
    }
}

//placa_con_L_bordes_fuera_y_agujeros();

