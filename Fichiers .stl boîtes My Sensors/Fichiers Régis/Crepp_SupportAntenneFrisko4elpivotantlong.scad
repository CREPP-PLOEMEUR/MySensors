// Support Antenne Frisko 4 ou 2 éléments pivotant long
// du 16/7/2017
lardip=53.5;    //largeur dipole
disref=20;		//distance reflecteur
larref=58;		//largeur reflecteur
epdip=4;       //écart brins dipole
fil=0.9;			// diametre du fil
supp=fil+(2*1);//épaisseur supports

render(convexity = 10) {




difference() {

// Partie pleine
union() {


//Support horizontal
translate([-5,-2,0]){
cube(size = [37,11,3], center = false);
}
//Support vertical
translate([27,-2,3]){
cube(size = [1.9,11,40], center = false);
}
//Renfort Support vertical
translate([28.9,2.5,3]){
cube(size = [3,2,33], center = false);
}


}

// Partie Creuse

union() {

//Perforations

//Creux Support vertical
translate([27,1,36]){
cube(size = [2,5,7], center = false);
}
//Trou Support horizontal
translate([0,3.5,0]){
//cube(size = [2,5,7], center = false);
cylinder(h = 3, d = 4, $fn=20, center = false);
}



}

}
}


