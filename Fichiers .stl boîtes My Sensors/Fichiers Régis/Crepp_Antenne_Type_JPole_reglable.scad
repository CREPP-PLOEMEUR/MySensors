//  Support Antenne Type J Pole V1
//   réglable
// Par Rpx màj du 5/9/2018

fil=1.2;			// diametre du fil
supp=fil+(2*1);//épaisseur supports

render(convexity = 10) {

difference() {

// Partie pleine
union() {
//Ecart diplole centre
translate([0,0,-2]){
cube(size = [8,3+fil,12], center = false);
}
//Branche diplole inf
//translate([0,0,-30]){
//cube(size = [3,1.5,29], center = false);
//}
//Support diplole inf
//translate([0,0,-25]){
//cube(size = [3,3+fil,3], center = false);
//}
//Branche diplole sup
translate([0,0,(2*fil)+6]){
cube(size = [3,1.5,90], center = false);
}
//Support diplole sup
translate([0,0,(2*fil)+6+70-3]){
cube(size = [3,3+fil,3], center = false);
}
//Support reflecteur
translate([20,0,0]){
cube(size = [supp,(4+2)/2+1,8], center = false);
}
//Support liaison & arrière
translate([0,0,-2]){
cube(size = [23.5,3,8], center = false);
}
translate([0,0,-2]){
cube(size = [23.5,3,12], center = false);
}
translate([20+supp,0,0]){
cube(size = [8,7,8], center = false);
}
}  // Fin union Partie pleine

// Partie Creuse
union() {
//Perforations
// J Branche longue
translate([1,3,-5]){
cube(size = [fil,fil+0.2,100], center = false);
}
// J Branche courte
translate([5,3,-5]){
cube(size = [fil,fil+0.2,40], center = false);
}
//Zone Feed Point
translate([1,3,-1]){
cube(size = [5,fil+0.2,fil], center = false);
}


//DIPOLE horizontal 1
//translate([1,3,2]){
//cube(size = [6.2,fil+0.1,fil], center = false);
//}
//DIPOLE horizontal 2
//translate([1,3,5]){
//cube(size = [6.2,fil+0.1,fil], center = false);
//}
//reflecteur 
translate([1+20,3-0.2,-5]){
cube(size = [fil,fil+0.25,22], center = false);
}
//& marque axe
translate([20,3,3.5]){
cube(size = [1,1,1], center = false);
}
//Creux Bome reflecteur
translate([6,0,2]){
cube(size = [14,5,4], center = false);
}
//Trace
//Creux Support arrière
translate([supp+23,0,0]){
cube(size = [2.4,1.4,8], center = false);
}
translate([supp+23,6-0.3,0]){
cube(size = [2.4,1.4,8], center = false);
}
} // Fin union Partie Creuse

} // Fin difference
} // Fin render


