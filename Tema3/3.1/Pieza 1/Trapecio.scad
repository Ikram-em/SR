// Autor: Ikram El Mabrouk Morhnane (UO301848)
// Fecha: 11-11-2025
// Descripción: Módulo que genera un trapecio de pie con agujero central para montaje en la estructura

x_size_small = 45;  
y_size_small = 2;
z_size_small = 4;

module trapecio_de_pie_con_agujero() {
    base_mayor = x_size_small;  // ancho inferior
    base_menor = 20;            // ancho superior
    altura_trapecio = 15;
    extrude_altura = 4;

    desfase = (base_mayor - base_menor) / 2;

    difference() {
        color("lightblue")
        linear_extrude(height = extrude_altura) {
            polygon(points=[
                [desfase, 0],                                 
                [base_mayor - desfase, 0],                    
                [base_mayor, altura_trapecio],                
                [0, altura_trapecio]
            ]);
        }
        translate([base_mayor / 2, altura_trapecio / 2, -1])  
            cylinder(h = extrude_altura + 2, r = 2, $fn=50);
    }
}
//trapecio_de_pie_con_agujero();
