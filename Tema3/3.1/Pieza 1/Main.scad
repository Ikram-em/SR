// main.scad
// Autor: Ikram El Mabrouk Morhnane (UO301848)
// Fecha: 11-11-2025
// Descripción: Montaje final de todas las piezas

include <PlacaGrande.scad>
include <PlacasMedianas.scad>
include <PlacasPequeñas.scad>
include <Rectangulo.scad>
include <PaloCilindricoYCilindros.scad>
include <Rueda.scad>
include <Trapecio.scad>
include <tapasRueda.scad>

module montaje_principal() {
    
    // Placa grande 
    translate([0, 0, 0])
        rectangulo_con_agujeros();

    // Placa mediana 1:
    translate([41, 0, 5])
    rotate([0, 0, 90])  
        placa_con_L_bordes_fuera_y_agujeros();
        
    // Placa mediana 2 
    translate([1, 0, 21])
      rotate([180, 0, 90])    
        placa_con_L_bordes_fuera_y_agujeros();


    // Placas pequeña 1:
    translate([50, 0, 5])   
        rectangulo_simple_con_agujeros(45,20,3,7,11,10);
        
    // Placas pequeña 2:
    translate([50, 40, 4])   
        rectangulo_simple_con_agujeros(45,20,3,7,11,10);

    // Trapecio 1:
    translate([50,56,22])
      rotate([-90, 0, 0]) 
        trapecio_de_pie_con_agujero();
    
    // Trapecio 2:
    translate([50,0,23])
       rotate([-90, 0, 0]) 
        trapecio_de_pie_con_agujero();

    // Cilindro 1:
    translate([70, 30, 16])     
    rotate([0, 90, 0])         
        PaloCilindricoYCilindros();
        
    // Cilindro 2:
    translate([23, 30, 15])     
    rotate([0, 90, 0])         
        PaloCilindricoYCilindros();

    // Bloque con agujero:
    translate([22,30,14])
      rotate([0, 0, 90])
        bloque_con_agujero();

    // Rueda 1 :
    translate([70,68,16])
        rueda();
        
    // Rueda 2:
    translate([24,-8,15])
        rueda();
        
    // Rueda 3 :
    translate([23,68,16])
        rueda();
        
    // Rueda 4:
    translate([70,-8,16])
        rueda();
        
    // TapasRueda 1 :
    translate([70, 22, 16])
      rotate([0, 90, 0])    
        tapasRuedas();

    // TapasRueda 2:
    translate([70, 38, 16])
      rotate([0, -90, 180]) 
        tapasRuedas();
        
      // TapasRueda 3 :
    translate([23, 22, 16])
      rotate([0, 90, 0])    
        tapasRuedas();

    // TapasRueda 4:
    translate([23, 38, 16])
      rotate([0, -90, 180]) 
        tapasRuedas();

}

montaje_principal();
