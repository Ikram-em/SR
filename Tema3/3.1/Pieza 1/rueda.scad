// Autor: Ikram El Mabrouk Morhnane (UO301848)
// Rueda pequeña: neumático + llanta reducida
module rueda() {
    grosor = 10;      
    diametro = 40;     
    diam_eje = 35;      
    wheel_r = 17.5;     
    wheel_t = 4.5;    
    center_hole = 7.5; 
    num_holes = 8;
    small_hole = 4.5;  
    hole_radius = 10;  

    //-- Construcción de la rueda
    rotate([90, 0, 0]) {
        // Neumático
        color("black")
        difference() {
            cylinder(r = diametro/2, h = grosor, $fn = 100, center=true); 
            cylinder(r = diam_eje/2, h = 3*grosor, $fn = 20, center=true);
        } 

        // Llanta
        color("silver")
        difference() {
            cylinder(r = wheel_r, h = wheel_t, $fn = 100, center=true);
            cylinder(h = wheel_t + 2, d = center_hole, $fn = 80, center=true);

            for(i = [0 : 360/num_holes : 360 - 360/num_holes]) {
                rotate([0, 0, i])
                    translate([hole_radius, 0, 0])
                        cylinder(h = wheel_t + 2, d = small_hole, $fn = 40, center=true);
            }
        }
    }
}

//rueda();

