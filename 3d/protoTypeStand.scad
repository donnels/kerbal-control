$fn=360;
// mm for slyrs box
topWidth=117;
topDepth=106;
topThick=2;
pillar=4;
height=46;
BigRedButtonD=22;
ToggleD=12;
WS2812D=4;
WS2812RingR=42/2;
numLEDs=12;
//versioning
letter_size = 10;
letter_height = topThick/2;
font = "Liberation Sans";
Version = "V 0.3" ;

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
    translate([topWidth/6,topDepth/2-6,-1]) cylinder(h=topThick+2,d=ToggleD);
    // disarmed LED
    translate([topWidth/6,topDepth/4,-1]) cylinder(h=topThick+2,d=WS2812D);
    // Armed LED
    translate([topWidth/6,topDepth/4-10,-1]) cylinder(h=topThick+2,d=WS2812D);
    //text
    translate([topWidth/2-10,topDepth-10,(topThick/2)+.5]) letter(Version);
    //LED ring
    translate([topWidth/2,topDepth/2,0])
        for ( i = [0 : 360/numLEDs : 360] ){
            rotate([0, 0, i]) translate([0, WS2812RingR, -1]) cylinder(h=topThick+2,d=WS2812D);
    }
}

//add a right side with holes for rotary encoders or wait?
// wait?
// the side will have two rotary encoders
// one for Throttle and one for timewarp
// add Leds on the top ( + / toggle-Key / - ) 
// 3 LEDS for each encoder 

module ringHolder() {
    //module for led ring holder - DRAFT
    holderH=2;
    holderOutD=42;
    holderInD=32;
    holderFence=1;
    holderFenceOutD=holderOutD+holderFence;
    holderFenceInD=holderInD-holderFence;
    difference() {
        //holder ring
        difference () {
            cylinder(h=holderH+holderFence,d=holderFenceOutD);
            translate([0,0,-1]) cylinder(h=holderH+holderFence+2,d=holderFenceInD);
        }
        //led ring for subtraction
        translate([0,0,holderFence+1]) difference () {
            cylinder(h=holderH,d=holderOutD);
            translate([0,0,-1]) cylinder(h=holderH+2,d=holderInD);
        }
    }
}
//draft for now
//ringHolder();