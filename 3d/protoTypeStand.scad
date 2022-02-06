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

//Legs are only needed during prototype phase
translate([0,0,0]) cube([pillar,pillar,height]);
translate([topWidth-pillar,0,0]) cube([pillar,pillar,height]);
translate([topWidth-pillar,topDepth-pillar,0]) cube([pillar,pillar,height]);
translate([0,topDepth-pillar,0]) cube([pillar,pillar,height]);

//Top of the box for reference
translate([0,0,height]) 
difference() {
    cube([topWidth,topDepth,topThick]);
    translate([topWidth/2,topDepth/2,-1]) cylinder(h=topThick+2,d=BigRedButtonD);
    translate([topWidth/4,topDepth/2,-1]) cylinder(h=topThick+2,d=ToggleD);
    translate([topWidth/4,topDepth/4,-1]) cylinder(h=topThick+2,d=WS2812D);
    translate([topWidth/4,topDepth/4-10,-1]) cylinder(h=topThick+2,d=WS2812D);
    translate([topWidth/2,topDepth/2,0])
        for ( i = [0 : 360/numLEDs : 360] ){
            rotate([0, 0, i]) translate([0, WS2812RingD, -1]) cylinder(h=topThick+2,d=WS2812D);
    }
}

