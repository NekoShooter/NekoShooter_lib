<div align="center" >
<h1> 🐱 GitiCore/ 🐠 </h1>
<h4>una libreria de manejo de bits</h4><br/>
  <a href="https://github.com/NekoShooter?tab=repositories&q=c&type=&language="><img src="https://i.ibb.co/1Q10GFX/C.png" alt="C" width='50'></a>
  <br/><br/>
  <a href= #><img src="https://i.ibb.co/Qb8TVqf/giti.png" alt="Giti" width="200"></a> 
  
  <br/><br/>

  </div>  
  
  ## Giti.h
  
 ` short aBytes(unsigned long *_int, unsigned char nBits) ` 
 el primer parametro toma un entero y le quita el numero de bits en nBits y lo retorna, _hay que usar una copia del entero para no afectar el valor original._  
 
    
 ` short charHexAint4bits(const char *_char) ` toma un solo caracter que representara un hexa y devuelve un entero  
    
    
 ` short intAhex(unsigned long _int, char *Hexadecimal, unsigned short longitudHexa, unsigned char hashtag) ` 
 el primero toma un **entero** que sera convertido a hexadecimal y el segundo toma un **array de char** al cual insertarle los caracteres que representan el hexadecimal, el tercero sera la **longitud del array** introducido, por lo que hay que asignar la memoria primero, el tercero y ultimo funciona como un **booleano** para insertarle un '#' al principio de la cadena algo estandar en cuanto a la sintaxis de los colores  
    
    
` long hexAint(const char *Hexadecimal) ` toma un arreglo de caracteres que representan un hexa y devuelve su forma decimal, PD: puede contener "#" si se lo desea  
   
   
###### Aun hay algunas funciones que se estan construyendo para compresion de datos y que espero hacer funcionar he integralas mas adelante   
   
   ###### GITICONTS.h
Constante | Valor | significado 
  --- | --- | ---
  VALIDO | 1 | notifica SI un valor es valido  
  INVALIDO | 0 | notifica si un valor NO es valido  
  GITI_OK | 1 | notifica si la operacion de una funcion fue exitosa  
  GITI_ERROR | -1 | notifica si ocurrio un error en la ejecucion de una funcion  
  True | 1 | una alternativa en C para true como valor booleano  
  False | 0 | una alternativa en C para false como valor booleano  
  BOOL | unsigned char | forma para emular un bool  
  Indefinido | 0 | para inicializar una variable sin valor  
  NO_INVERTIR | 0 | para uso de funciones que requieran no invertir como una opcion  
  INVERTIR | 1 | para uso de funciones que requieran invertir como una opcion   
  GITI_OPCION | unsigned char | una variable que otorge una opcion a una funcion (NO_INVERTIR, INVERTIR etc etc..)  
  uChar | unsigned char | un short cut para no ser tan larga los inputs de las funciones  
  cuChar | const unsigned char |   
  uShort | unsigned short |   
  cuShort | const unsigned short |   
  uInt | unsigned int |   
  uLong | unsigned long |   
 