// Cherry MX keycap holder for laser engraving

cross_x = 4;
cross_y = 1.31;
cross_z = 3.6;
cross_tolerance = 0.2;
plate_z = 2 ;

//versioning
letter_size = 8;
letter_height = 2;
font = "Liberation Sans";
Version = "V1" ;

module letter(l) {
	linear_extrude(height = letter_height) {
		text(l, size = letter_size, font = font, halign = "center", valign = "center", $fn = 16);
	}
}
difference() {
    cube([20,20,plate_z],center=true);
    translate([0,5,plate_z/4]) letter(Version);
}
translate([0,0,plate_z/2+cross_z/2]){
    cube([cross_y-cross_tolerance, cross_x-cross_tolerance, cross_z*2], center=true);
    cube([cross_x-cross_tolerance, cross_y-cross_tolerance, cross_z*2], center=true);
}
