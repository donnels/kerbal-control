$fn=360;
// mm for slyrs box
topWidth=117;
topDepth=106;
topThick=2;
pillar=4;
height=40;
BigRedButtonD=22;
ToggleD=12;
WS2812D=4;
WS2812RingD=18;
numLEDs=12;
letter_size = 4;
letter_height = topThick/2;
font = "Liberation Sans";

module letter(l) {
	linear_extrude(height = letter_height) {
		text(l, size = letter_size, font = font, halign = "center", valign = "center", $fn = 16);
	}
}

//Legs are only needed during prototype phase
translate([0,0,0]) cube([pillar,pillar,height]);
translate([topWidth-pillar,0,0]) cube([pillar,pillar,height]);
translate([topWidth-pillar,topDepth-pillar,0]) cube([pillar,pillar,height]);
translate([0,topDepth-pillar,0]) cube([pillar,pillar,height]);

//Top of the box for reference
translate([0,0,height]) 
difference() {
    cube([topWidth,topDepth,topThick]);
    // Big red Button
    translate([topWidth/2,topDepth/2,-1]) cylinder(h=topThick+2,d=BigRedButtonD);
    // toggle switch
    translate([topWidth/4,topDepth/2,-1]) cylinder(h=topThick+2,d=ToggleD);
    // disarmed LED
    translate([topWidth/4,topDepth/4,-1]) cylinder(h=topThick+2,d=WS2812D);
    // Armed LED
    translate([topWidth/4,topDepth/4-10,-1]) cylinder(h=topThick+2,d=WS2812D);
    //text
    translate([topWidth/4-15,topDepth/4-10,(topThick/2)+.5]) letter("Armed");
    translate([topWidth/4-15,topDepth/4,(topThick/2)+.5]) letter("DisArmed"); 
    //LED ring
    translate([topWidth/2,topDepth/2,0])
        for ( i = [0 : 360/numLEDs : 360] ){
            rotate([0, 0, i]) translate([0, WS2812RingD, -1]) cylinder(h=topThick+2,d=WS2812D);
    }
}


