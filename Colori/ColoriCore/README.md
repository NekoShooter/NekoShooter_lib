<div align="center" >
<h1> 🎨 ColoriCore/ ⚙️ </h1>
<h4>conglomerado de varias librerias para el tratamiento de datos de tipo color</h4><br/>
  <a href="https://github.com/NekoShooter?tab=repositories&q=c&type=&language="><img src="https://i.ibb.co/1Q10GFX/C.png" alt="C" width='50'></a>
  <br/><br/>
  <a href= #><img src="https://i.ibb.co/tBHCqK5/colori.png" alt="Colori" width="200"></a> 
  
  <br/><br/></div>  
  
  ## Colori\_\_rgb\_\_.h
  
 ` union c_rgb ` 
 la variable pilar, almacena distintos tipos de datos usando el mismo espacio de memoria (5 bytes) por todo  
    
  
 miembro | indice | valor 
  --- | --- | ---
  rgb | _R\_ | asigna o retorna el valor Rojo  
  rgb | _G\_ | asigna o retorna el valor Verde  
  rgb | _B\_ | asigna o retorna el valor Azul  
  rgb | _A\_ | asigna o retorna el valor Alfa  
  rgb | _F\_ | asigna o retorna la familia de la que proviene el color  
  id |   | el valor decimal del color en RGB  
  id_a |   | el valor decimal del color en RGBA
  info |   | la informacion completa incluye RGBA y su familia  
    
   
 ` c_rgb *nuevo_rgb(short tam) ` asigna un espacio de memoria para c_rgb  
    
    
 ` void liberar(c_rgb *rgb_aEliminar) ` libera el espacio de memoria de c_rgb  
    
    
 ` c_rgb *complemento(const c_rgb *original,uChar estilo) ` 
 toma el color **original** y devuelve el color complementario segun el **estilo** indicado - _ejem RGB\_Style o RYB\_Style_  
    
    
` c_rgb *adyasente(const c_rgb *original, coloridx posicion,uChar estilo) ` toma el color **original** y devuelve el color primario segun su **posicion** -_ejem AdyasenteDER o AdyasenteIZQ_ y el **estilo** indicado - _ejem RGB\_Style o RYB\_Style_  
   
   
 ` c_rgb *contiguo(const c_rgb *original,coloridx posicion,uChar estilo) ` toma el color **original** y devuelve el color secundario segun su **posicion** -_ejem ContiguoDER o ContiguoIZQ_ y el **estilo** indicado - _ejem RGB\_Style o RYB\_Style_  
    
    
 ` c_rgb *circulo_cromatico(const c_rgb *rgb_original,coloridx seccion, uChar estilo) ` 
 con el color **original** devuelve toda la gama de colores del circulo cromatico _primarios secundario ternarios_ segun el **estilo** indicado - _ejem RGB\_Style o RYB\_Style_  
    
    
 ` c_rgb *mezclar_colores(const c_rgb *ColorA, const c_rgb *ColorB) ` 
 mezcla los colores A y B como si de pintura se tratase y devuelve el color combinado  
    
    
  ## ColoriMath.h  
  

 ` c_rgb nivelacion_luminica(const c_rgb * ColorA,const c_rgb * ColorB) ` 
 tomando al ColorA y al ColorB genera un color que toma los valores de ColorB pero con la intensidad luminica de ColorA   
    
    
  ` c_rgb nivel_de_luminicencia(c_rgb Color,short intencidad); ` 
 toma como base el Color para aplicar una intencidad ya sea para hacerlo mas brillante o mas oscuro   
    
    
 ` short brillo_y_sombra(const c_rgb *color, c_rgb *Brillo, c_rgb *Sombra, double Nivel_Brillo, double Nivel_Oscuro) ` 
 toma el color **original** y devuelve el mismo color uno con mas brillo y el otro mas oscuro segun se indique el nivel de estos, retorna COLORI_OK si es exitoso y COLORI_ERROR si fallo   
    
    
 ` short dividir_tono (short Tono, short *Claro, short *Oscuro, double Nivel_Brillo, double Nivel_Oscuro) ` 
 toma el tono sea Rojo, Verde, Azul (rgb) para tener un punto de referencia para generar un tono claro y oscuro que seran pasados a \*Claro y \*Oscuro. En los niveles de brillo y oscuridad se determina la cantidad de brillo y sombra que se desea tener por tono de color de forma independiente, retorna COLORI_OK si es exitoso y COLORI_ERROR si fallo  
    
    
 ` c_rgb * suma_de_color(const c_rgb * origen, const c_rgb * destino, short desplazamiento) ` 
 se debe considerar la posicion del color para poder usarla, en una representacion grafica los colores forman un circulo cuyos angulos representarian los colores por lo cual sabiendo su posicion es posible sumarlos y mezclarlos para generar nuevos colores, el color menor va en \*origen y el mayor en \*destino en ese orden se asignaria un desplazamiento a **DERECHA** en caso de contrario seria **IZQUIERDA**, si pertenecen a la misma gama no importa el orden, el desplazamiento seria al **CENTRO**   
    
    

 ` void mover_rgb(c_rgb *crgb, uChar tipo_de_movimiento) ` 
desplaza los valores de R G B **DERECHA IZQUIERDA** o **ROTAR** segun sea nesesario para la operacion que se desea realizar    
    
    
 ` void convertir_a_inverso(c_rgb *original) ` 
al igual que los numeros reales donde 1/x es el inverso de x, para los colores existe algo parecido y esta funcion convierte un color a su color inverso  
    
    
 ` c_rgb *inverso(const c_rgb *original) ` 
toma un color y retorna su color inverso  
    
    
 ` c_rgb *tercio(const c_rgb *original,uChar orientacion) ` 
tomando la idea grafica de que los colores podrian estar dentro de un circulo o esfera esta funcion segun su orientacion retorna los colores de herencia luminica mas fuertes en pocas palabras sus colores mas cercanos a 60 grados dependiendo de su orientacion **IZQUIERDA** (180 grados) o **DERECHA** (60 grados)     
    
    
 ` c_rgb *sexto(const c_rgb *original,uChar orientacion) ` 
misma idea pero esta retorna los colores intermedios entre sus colores mas cercanos o colores a 30 grados, dependiendo de su orientacion **IZQUIERDA** (270) o **DERECHA** (30)  
    
    
  ` void buscar_familia(c_rgb *_rgb_) ` 
busca y asigna la familia a la que pertenece el color  
    
    
  ` void definir_limite_ascendente(uShort refencia, uChar *limite_min, uChar *limite_max) ` 
funcion que define los limites del tono dominante es decir asta que punto un color Rojo deja de ser Rojo y pasa a ser Naranja para eso se toma el tono dominante y se definen sus limites de este para determinar a su familia -_ejem para R(rojo) dominate donde limite_min > de G(verde) o B(azul) sigue siendo R(rojo) pero para limite_min < G o B si < limite_max para G es naranja y para B purpura caso contrario si limite_max < G o B, para G sera amarillo y para B sera magenta   
    
    
  ` void definir_limite_desendente(uShort refencia, uChar *limite_min, uChar *limite_max) ` 
misma idea pero para los tonos inferiores, pero esta funcion se descarto ya que ***definir_limite_ascendente()*** genera el mismo resultado solo hay que cambiar el tono dominate por el tono medio o el tono bajo para determinar los colores combinados tipo ***phtalos cadmios y cobaltos***
    
    
   ` coloriFamilia rgbSort(const c_rgb * Crgb,uChar* idx_max, uChar *idx_med, uChar * idx_min) ` 
asigna los valores de los indices maximos, medios y minimos del RGB para su tratamiento posterior, retorna el tono dominante   
    
    
  ` coloriFamilia purezaRGB(const c_rgb *original) ` 
analiza la pureza de un color es decir cuanto mas diferencia entre el tono dominante de los tonos medio y bajos la posibilidad de que el tono dominate sea la familia real es mas alta y esta funcion determina eso retorna C_NEUTRO (gris) si no puede determinar su pureza y C_ROJO, C_VERDE o C_AZUL en caso contrario  
    
    
  ## ColoriBasic.h  
  

  ` long  rgb_a_int(unsigned  long r,unsigned int g,  unsigned short b) ` 
unifica en un solo valor a R G y B  
    
    
 ` short rgb_a_hex(unsigned short r,unsigned short g,unsigned short b,char *Hexadecimal, short dimencion) ` 
 se obtiene la cadena de texto con el valor en hexadecimal de los valores R G y B retorna COLORI_OK si se tuvo exito y COLORI_ERROR si algo fallo   
    
    
  ` short rgb_a_css(unsigned short r,unsigned short g,unsigned short b,char *CSS) ` 
 lo mismo pero esta ves en su notacion de 3 hexadecimales mas comunmente usado en CSS retorna COLORI_OK si se tuvo exito y COLORI_ERROR si algo fallo  
    
    
 ` short int_a_css(long Valor,char *CSS) ` 
 toma un valor decimal y lo transforma a su notacion CSS cabe aclarar que el array debe de ser de tamaño minimo de 4 char, retorna COLORI_OK si se tuvo exito y COLORI_ERROR si algo fallo   
    
    
 ` short int_a_rgb(long Valor,unsigned short *r,unsigned short *g,unsigned short *b) ` 
 toma un valor decimal y lo reparte a sus contrapartes R G y B, retorna COLORI_OK si se tuvo exito y COLORI_ERROR si algo fallo  
    
    
 ` short int_a_hex(long Valor,char *Hexadecimal,short longitudHexa) ` 
toma un valor decimal y lo comvierte a una cadena de caracteres, la longitud del array y el tamaño del valor decimal determinara la cantidad de hexadecimales que tendra, retorna COLORI_OK si se tuvo exito y COLORI_ERROR si algo fallo   
    
    

 ` long  hex_a_int(const char *Hexadecimal) ` 
convierte un hexadecimal escrito en una cadena de texto a un numero entero, puede incluir o no "#" venir en mayuscula o minusculas no importa, retorna el valor si se tuvo exito y COLORI_ERROR si algo fallo    
    
    
 ` short hex_a_rgb(const char *Hexadecimal,short *r,short *g,short *b) ` 
convierte un hexadecimal escrito en una cadena de texto a los valores R G B, retorna COLORI_OK si se tuvo exito y COLORI_ERROR si algo fallo  
    
    
 ` short hex_a_css(const char *Hexadecimal, char *CSS) ` 
convierte un hexadecimal escrito en una cadena de texto a un hexadecimal escrito CSS, retorna COLORI_OK si se tuvo exito y COLORI_ERROR si algo fallo  
    
    
 ` long  css_a_int(const char *CSS) ` 
convierte un hexadecimal CSS a una representacion decimal, retorna el valor si se tuvo exito y COLORI_ERROR si algo fallo     
    
    
 ` short css_a_rgb(const char *CSS ,short *r,short *g,short *b) ` 
convierte un hexadecimal CSS a su parte R G B, retorna COLORI_OK si se tuvo exito y COLORI_ERROR si algo fallo  
    
    
  ` short css_a_hex(const char *CSS,char *Hexadecimal) ` 
convierte un hexadecimal CSS a su notacion hexadecimal completo, retorna COLORI_OK si se tuvo exito y COLORI_ERROR si algo fallo   
    
    
    
###### puede que existan algunas excepciones en los colores ya que la teoria del color bueno es eso una teoria no es algo concreto trate de hacer mi mejor trabajo investigando y desarrollando el algoritmo, de momento asta que no encuentre una ecuacion matematica que sustente esto es probable que aparescan estas excepciones, he hecho lo posible por minimizarlas y asta el momento parece ser que el funcionamiento es el esperado pero asta no haber corroborado cada color de forma independiente no estare seguro  
   
   
   ###### COLORICONST.h
Constante | Valor | significado 
  --- | --- | ---
  COLOR_MAX | 0xffffffff | El valor maximo de un color RGBa  
  BLANCO | 0xffffff | el valor hexadecimal del color blanco  
  NEGRO | 0 | el valor hexadecimal del color negro  
  COLORI_OK | 1 | notifica si la ejecucion de una funcion fue exitosa  
  COLORI_ERROR | -1 | notifica si ocurrio un error en la ejecucion de una funcion  
  CONST_ARTE | 2.0 | por curioso que paresca una constante que sirve para casi todo  
  CENTRO | 0 | forma para indicar que se quiere el punto medio -_ejem funcion_ ***suma_de_color()***
  DERECHA  | 1 | indica el movimiento a la derecha de los valores -_ejem funcion_ ***mover_rgb()***  
  IZQUIERDA  | 2 | movimiento a la izquierda de los valores -_ejem funcion_ ***mover_rgb()*** 
  ROTAR | 3 | rota los valores -_ejem funcion_ ***mover_rgb()***    
  RGB_Style | 0x17 | indica la opcion de una paleta basada en el sistema RGB  
  RYB_Style | 0x0 | indica la opcion de una paleta basada en el sistema RYB  
  coloriFamilia | enum | indica la familia perteneciente de un color -_ejem verde, rojo, azul etc.._   
  coloridx | enum | indica el tipo de composion -_ejem contiguo,secundario,ternarios._ Funciona tambien como indices para localizar una composicion especifica en un array de colores