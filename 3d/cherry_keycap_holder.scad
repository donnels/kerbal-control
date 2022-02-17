cross_x = 4;
cross_y = 1.31;
cross_z = 3.6;
cross_tolerance = 0.2;
plate_z = 2 ;

cube([20,20,2],center=true);
translate([0,0,plate_z/2+cross_z/2]){
    cube([cross_y-cross_tolerance, cross_x-cross_tolerance, cross_z*2], center=true);
    cube([cross_x-cross_tolerance, cross_y-cross_tolerance, cross_z*2], center=true);
}
