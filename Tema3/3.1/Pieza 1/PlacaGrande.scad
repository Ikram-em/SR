// Autor: Ikram El Mabrouk Morhnane (UO301848)
// Fecha: 11-11-2025
// Placa rectangular con agujeros en rejilla

placagrande_largo = 95;       // Longitud total de la placa (eje X)
placagrande_ancho = 60;       // Ancho total de la placa (eje Y)
placagrande_alto = 5;         // Grosor o altura de la placa (eje Z)

placagrande_filas = 4;                  // Número de filas de agujeros
placagrande_columnas = 4;               // Número de columnas de agujeros
placagrande_diametro_agujero = 5;       // Diámetro de cada agujero

placagrande_margen_x = 10;              // Margen izquierdo y derecho
placagrande_margen_y = 10;              // Margen superior e inferior

placagrande_area_x = placagrande_largo - 2 * placagrande_margen_x;
placagrande_area_y = placagrande_ancho - 2 * placagrande_margen_y;

placagrande_espaciado_x = placagrande_area_x / (placagrande_columnas - 1);   // Distancia entre agujeros en X
placagrande_espaciado_y = placagrande_area_y / (placagrande_filas - 1);      // Distancia entre agujeros en Y


module rectangulo_con_agujeros() {
    difference() {
        color("lightblue")
        cube([placagrande_largo, placagrande_ancho, placagrande_alto]);

        for (i = [0:placagrande_columnas - 1]) {
            for (j = [0:placagrande_filas - 1]) {
                translate([
                    placagrande_margen_x + i * placagrande_espaciado_x,   
                    placagrande_margen_y + j * placagrande_espaciado_y,    
                    -1                             
                ])
                cylinder(
                    h = placagrande_alto + 2,                 
                    r = placagrande_diametro_agujero / 2,      
                    $fn = 30                       
                );
            }
        }
    }
}

//translate([-placagrande_largo/2, -placagrande_ancho/2, 0])
  //  rectangulo_con_agujeros();




