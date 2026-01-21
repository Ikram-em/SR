// Autor: Ikram El Mabrouk Morhnane (UO301848)
// Fecha: 11-11-2025
// Descripción: Una sola tapa con agujero ciego interno 

module tapasRuedas() {

    radio_pequeno = 5;
    grosor_pequeno = 4;        
    radio_agujero_ciego = 2;  
    profundidad_agujero = 2;   
    distancia_pequenos = 34;  

    translate([0, -distancia_pequenos, 0])
        rotate([90,0,0])
        color("lightblue")
        difference() {
            cylinder(h = grosor_pequeno, r = radio_pequeno, center=true, $fn=100);
            translate([0,0,-grosor_pequeno/2])
                cylinder(h = profundidad_agujero, r = radio_agujero_ciego, center=false, $fn=80);
        }
}

//tapasRuedas();
