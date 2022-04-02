//  Boitier Passerelle MySensors   v2
// du 13/7/2017
lar=80;
prof=80;
haut=22;
ep=2;

render(convexity = 10) {




difference() {

// Partie pleine
union() {


//Fond
translate([-(lar/2),-prof/2,0]){
cube(size = [lar,prof+35,ep], center = false);
}
//Parois verticales
//Gauche
translate([-(lar/2),-prof/2,0]){
cube(size = [ep,prof+35,haut], center = false);
}
//Antenne horizontale
translate([-(lar/2),prof/2+35,0]){
cube(size = [ep+13,ep,12], center = false);
}
// Batterie paroi
translate([-(lar/2),(-prof/2)+22,0]){
cube(size = [lar,ep,haut], center = false);
}
//Droite
translate([(lar/2),-prof/2,0]){
cube(size = [ep,prof,haut], center = false);
}
//Arriere
translate([-(lar/2),(prof/2)-2,0]){
cube(size = [lar,ep,haut], center = false);
}
//Avant
translate([-(lar/2),-(prof/2),0]){
cube(size = [lar,ep,haut], center = false);
}

//Supportplaque  Gauche
translate([-(lar/2)+52-38,-(prof/2)+27+16+1,ep]){
cylinder(h = 5, r = 1.5, $fn=20, center = false);
}
//Supportplaque AV 
translate([-(lar/2)+52,-(prof/2)+27+1,ep]){
cylinder(h = 5, r = 3.5, $fn=20, center = false);
}
//Supportplaque AR Gauche pour passerelle
translate([-(lar/2)+10,(prof/2)-10,ep]){
cylinder(h = 5, r = 3.5, $fn=20, center = false);
}
//Supportplaque AR 
translate([-(lar/2)+52,-(prof/2)+27+34+1,ep]){
cylinder(h = 5, r = 3.5, $fn=20, center = false);
}




}

// Partie Creuse

union() {

//Perforations

//Suppression Fond & Supports antennes
translate([-(lar/2),prof/2,0]){
cube(size = [lar,40,ep+22], center = false);
}
//Fond fente Antenne 1
translate([-(lar/2)+5,prof/2+25,0]){
cube(size = [12,5,ep], center = false);
}
//Paroi Gauche fente Antenne 2
translate([-(lar/2),prof/2+25,haut/2+1]){
cube(size = [ep,12,5], center = false);
}
//Antennefente horizontale Antenne 3
translate([-(lar/2)+ep+3,prof/2+35,ep]){
cube(size = [10,ep,5], center = false);
}

//PerfSupportplaque Gauche 
//translate([-(lar/2)+23,-(prof/2)+7,3]){
//cylinder(h = 8, r = 1.5, $fn=20, center = false);
//}
//PerfSupportplaque AV Droit
translate([-(lar/2)+52,-(prof/2)+27+1,ep]){
cylinder(h =  8, r = 1.5, $fn=20, center = false);
}
//PerfSupportplaque AR Gauche
translate([-(lar/2)+10,(prof/2)-10,ep]){
cylinder(h =  8, r = 1.5, $fn=20, center = false);
}
//PerfSupportplaque AR Droit
translate([-(lar/2)+52,-(prof/2)+27+34+1,ep]){
cylinder(h =  8, r = 1.5, $fn=20, center = false);
}

//Perf Fixation Gauche & Droite
translate([-(lar/2)+11,-(prof/2)+52,0]){
cylinder(h =  8, r = 1.5, $fn=20, center = false);
}
translate([-(lar/2)+11,-(prof/2)+52,1]){
cylinder(h =  8, r = 3, $fn=20, center = false);
}
translate([-(lar/2)+71,-(prof/2)+52,0]){
cylinder(h =  8, r = 1.5, $fn=20, center = false);
}
translate([-(lar/2)+71,-(prof/2)+52,1]){
cylinder(h =  8, r = 3, $fn=20, center = false);
}




//Découpes Passages Fils Cloisons
// Batterie
//translate([-(lar/2)+10,-(prof/2)+22-.5,12]){
//cube(size = [5,10,10], center = false);
//}
// Cable nRF24
translate([-(lar/2)+41,(prof/2),12]) rotate ([90,0,0]){
cylinder(h =  8, r = 1.5, $fn=20, center = false);
//cube(size = [3,10,12], center = false);
}
// Perf fixation support antenne
translate([-(lar/2)+10,(prof/2)-2,10]){
cube(size = [3,10,12], center = false);
}


//Suppression bloc batterie
translate([-(lar/2),-prof/2,0]){
cube(size = [lar+2,22,ep+22], center = false);
}



//PerfFermetureBoitier AV Gauche
//translate([-(lar/2)+2+14-1.5,-(prof/2)+2+1.5,-.1]){
//cylinder(h = 5, r = 1.5, $fn=20, center = false);
//}
//PerfFermetureBoitier AV Droit
//translate([-(lar/2)+lar-22+1.5,-(prof/2)+2+1.5,-.1]){
//cylinder(h =  5, r = 1.5, $fn=20, center = false);
//}
//PerfFermetureBoitier AR Gauche
//translate([-(lar/2)+2+14-1.5,-(prof/2)+prof-3.5,-.1]){
//cylinder(h =  5, r = 1.5, $fn=20, center = false);
//}
//PerfFermetureBoitier AR Droit
//translate([-(lar/2)+lar-22+1.5,-(prof/2)+prof-3.5,-.1]){
//cylinder(h =  5, r = 1.5, $fn=20, center = false);
//}
//Découpes Avant
//Audio
//translate([-(lar/2)+18+1+28-4,-(prof/2)+-.1,12]){
//cube(size = [8,3,12], center = false);
//}
//Ch1
//translate([-(lar/2)+18+1+65-5,-(prof/2)+-.1,12]){
//cube(size = [10,3,15], center = false);
//}
//Ch2
//translate([-(lar/2)+18+1+83-5,-(prof/2)+-.1,12]){
//cube(size = [10,3,15], center = false);
//}
//Bouton M/A
//translate([-(lar/2)+lar-17,-(prof/2)+-.1,10]){
//cube(size = [13,3,20], center = false);
//}
//Découpe Droite pour Pile
//translate([-(lar/2)+lar-2.1,-(prof/2)+37,3]){
//cube(size = [3,45,35], center = false);
//}
//Perfos Attache Pile1
//translate([-(lar/2)+lar-2.1,-(prof/2)+33,20]){
//rotate([0, 90,0]){
//cylinder(h =  5, r = 2, $fn=20, center = false);
//}}
//Perfos Attache Pile2
//translate([-(lar/2)+lar-2.1,-(prof/2)+prof-5,20]){
//rotate([0, 90,0]){
//cylinder(h =  5, r = 2, $fn=20, center = false);
//}}

//Découpes Passages Fils Cloisons
//Hautparleur
//translate([-(lar/2)+16-0.1,-(prof/2)+75,26]){
//cube(size = [3,10,10], center = false);
//}
//Pile
//translate([-(lar/2)+120-0.1,-(prof/2)+70,26]){
//cube(size = [3,10,10], center = false);
//}
//Bouton M/A
//translate([-(lar/2)+120-0.1,-(prof/2)+15,26]){
//cube(size = [3,10,10], center = false);
//}





}
}

}
