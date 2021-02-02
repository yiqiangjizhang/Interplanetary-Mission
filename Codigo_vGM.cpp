/*PROGRAMA PARA DETERMINAR EL RADIO DEL PERIAPSIS DEL ENCUENTRO CON JUPITER 
PARA QUE EL AFELIO ED LA ORBITA DE SALIDA SEA IGUAL AL RADIO DE LA ORBITA DE SATURNO*/


#include <iostream>
#include <cmath>
#include <iomanip> //setprecision
#include <stdio.h>
#include <fstream>


#define PRECISION 6


using namespace std;




void tabla(double n, double m);
double f(double x);


int main()
{

	//INICIO DEL PROGRAMA
	
  	
	printf("\nCALCULO DEL RADIO DEL PERIAPSIS MEDIANTE METODO DE BISECCION\n\n");
	cout<< setprecision(PRECISION);
	
	
	
	cout<<"Ingrese el intervalo inicial [n,m]"<<endl;
	
	double n,m,tolerancia;
	
	cout<<"\nn = ";
	cin>>n;
	cout<<"m = ";
	cin>>m;
	
	tabla(n,m);

   	cout << "\nEscoja el intervalo adecuado" << endl;
  	cout << "\nn = ";
   	cin >> n;
   
   cout << "m = ";
   cin >> m;
   
   double xr; // punto medio del intervalo n,m
   
   if (f(n)*f(m)>0){
   	
   cout << "\nNo se puede aplicar el metodo de la biseccion\n";
   cout << "porque f(" << n << ") y f(" << m << ") tienes el mismo signo" << endl;
      
   } else {
   	
   	  cout << "Tolerancia = ";
      cin >> tolerancia;
      
	  
	  cout << "\nn\tm\tx\tf(n)\t\tf(m)\t\tf(x)\n" << endl; // encabezado de la tabla	
     
	 // bucle del método
	  do {
         
		 xr = (n + m) / 2.0;
		 
         cout << n << "\t" << m << "\t" << xr << "\t"; // imprimimos los valores
         cout << f(n) << "\t" << f(m) << "\t" << f(xr) << endl;

         // Vemos si cumple o no cumple
         if (fabs(f(xr)) <= tolerancia) { // xr sería la raiz de f    // fabs es la funcion valor absoluto
         
            cout << "\n\nPara una tolerancia " << tolerancia << " la raiz de f es " << xr << endl;
            break; // para romper bucle
            
         } else {
            
			// hay que remplazar a n o m
            
			if (f(xr) * f(n) > 0) { // si la imagen de f(xr) y f(n) tienen el mismo signo
               n = xr; // remplazamos la variable n
            } else if (f(xr) * f(m) > 0) {
               m = xr;
            }
         }
         
      } while (1);
   }
   
   
   
   
   
   
   
   

    cin.get();
	cin.get();
	return 0; 	
}




//Código de las Acciones

#define INTERVALOS 10 
void tabla(double n, double m)
{
	int puntos = INTERVALOS + 1; //si tenemos 10 intervalos, el numero de puntos sera los intervalos más 1
	
	double ancho = (m-n) / INTERVALOS; // el ancho de los intervalos
	
	cout << "\n";
	cout<<"\n\tx\tf(x)\n "; //para mostrar la tabla
	for (int i=0; i<puntos; i++){
		
		cout<<"\t"<< n << "\t" << f(n) <<endl; // donde a es el valor del punto y f(a) su imagen
		n = n + ancho;
		
	}
		
	}

double f(double x)
{
	// valor que me tiene que devolver la funcion
	// nuestra funcion es: ra=((pow(h2,2))/(mu_Sol*(1-e2)));
	
	
	//Datos y constantes de los astros en SI
	double G=6.67*pow(10,-11);
	double Masa_Sol=1.9891*pow(10,30); // 1,9891*10^30
	double mu_Sol=G*Masa_Sol;
	
	double rorbJup=778412010000;
	double rorbT=149597870700; // = 1 UA
	double rorbSat=1426725400;
	
	double rJup=69911000;
	double rT=6371000;
	double rSat=58232000;
	
	double muJup;
	double Masa_Jup=1.898*pow(10,27);
	muJup=G*Masa_Jup;
	
	// Parámetros de la elipse
	
	double e=0.7015;
	double a=501152866845;
	double theta=163.6144056409079; // grados
	double h=5.811241928693205*pow(10,15);
	
	
	double vtheta=7465.509080073424;
	double vradial=4517.935474540212;
	
	double vJuptan;
	//función velocidad orbital Jupiter (órbita circular)
	vJuptan=sqrt(mu_Sol/rorbJup);
	
	double v_infmenos_rad=4517.935474540212;
	double v_infmenos_tan;
	v_infmenos_tan=vtheta-vJuptan;
	double v_infmenos;
	v_infmenos=sqrt(pow(v_infmenos_rad,2)+pow(v_infmenos_tan,2)); //módulo de v_infmenos
	
	
	// <<< Parametros durante flyby | FUNCIONES >>>
	
	double rpi; // INCÓGNITA
	
	
	//excentricidad trayectoria hiperbolica
	double e1; 
	e1=1+((pow(v_infmenos,2)*rpi)/muJup);
	
	//delta=angulo de giro
	double delta;
	delta=2*asin(1/e1);
	
	//vinfmas=velocidad de la nave despues del flyby
	double v_infmas_rad;
	double v_infmas_tan;
	v_infmas_rad=(cos(delta)*v_infmenos_rad-sin(delta)*v_infmenos_tan);
	v_infmas_tan=(sin(delta)*v_infmenos_rad+cos(delta)*v_infmenos_tan);
	double v_infmas;
	v_infmas=sqrt(pow(v_infmas_rad,2)+pow(v_infmas_tan,2)); //módulo de v_infmas
	
	//v2=nueva velocidad de la elipse
	double v2;
	double v2_rad;
	double v2_tan;
	v2_rad=v_infmas_rad;
	v2_tan=v_infmas_tan+vJuptan;
	v2=sqrt(pow(v2_rad,2)+pow(v2_tan,2)); //módulo de v_2
	
	//Energía de la elipse tras flyby (tiene que ser NEGATIVO)
	double epsilon2;
	epsilon2=(pow(v2,2)/2)-mu_Sol/rorbJup;
	
	//h2=momento angular 2
	double h2;
	h2=rorbJup*v2_tan;
	
	//a2=apoapsis 2 de la nueva elipse
	double a2;
	a2=-mu_Sol/(2*epsilon2);
	
	//excentricidad 2 de la nueva elipse
	double e2;
	//e2=sqrt(1-(pow(h2,2))/(a2*mu_Sol));
	e2=-1*((pow(h2,2)/(mu_Sol*rorbJup))-1);
	
	
	//Finalmente, imponemos que rafelio=rorbSat, la cual dependerá de nuestra rpi
	double ra; //rafelio
	ra=((pow(h2,2))/(mu_Sol*(1-e2)));
	//ra= a2*(1+e2); // otra posible manera
	
	
	return ra-rorbSat;
	//return exp(-1 * x) - cos(3 * x) - 0.5; // es una funcion cualquiera de prueba 
	
}
