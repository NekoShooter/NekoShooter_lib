<div align="center" >
<h1> 🎨 ColoriColor/ 🖌 </h1>
<h4>ColoriColor y Colori_rgb</h4><br/>
  <a href="https://github.com/NekoShooter?tab=repositories&q=cpp&type=&language="><img src="https://i.ibb.co/hd3yP7D/C.png" alt="C++" width='50'></a>
  <br/><br/>
  <a href= #><img src="https://i.ibb.co/2Zr1sTY/colori-2.png" alt="Colori" width="200"></a> 
  
  <br/><br/></div>  
  
  ## ColoriRGB.h
  
 ` class Colori_rgb ` 
 la clase base de ColoriColor, usa c\_rgb como su variable pilar  
    
  
 carga de inicio de la clase | valores  
  --- | --- |
  **Colori\_rgb**() | **void** 
  **Colori\_rgb**(_const unsigned long long &Info_) | **c\_rgb.info**   
  **Colori\_rgb**(_const unsigned short &r, const unsigned short &g, const unsigned short &b,const unsigned short &a=0xff_) | **R G B A**  
  **Colori\_rgb**(_const c\_rgb &RGB_) | **c\_rgb** 
    
   
 #### public:  
    
 ` void cambiarRGBA(const unsigned short &r, const unsigned short &g, const unsigned short &b,const unsigned short &a) ` cambia de un solo golpe a **R G B A**  
    
 ` void cambiarRGB(const unsigned short &r,const unsigned short &g,const unsigned short &b) ` cambia de un solo golpe a **R G B**  
    
 ` void cambiarID(const unsigned int &ID_Color) ` 
 cambia el id que es la forma comprimida de obtener el **RGB**:  _c\_rgb variable.id_  
    
` void cambiarID_A(const unsigned int &ID_A_Color) ` cambia el id_a que es la forma comprimida de obtener el **RGBA**:  _c\_rgb variable.id\_a_  
   
 ` void cambiarInfo(const unsigned long long &Info) ` cambia la info que es la forma comprimida de obtener **RGBA** y su **familia**:  _c\_rgb variable.info_  
    
 ` void cambiarR(const unsigned short &r) ` 
 cambia el tono Rojo  
    
 ` void cambiarG(const unsigned short &g) ` 
 cambia el tono Verde  
    
 ` void cambiarB(const unsigned short &b) ` 
 cambia el tono Azul  
    
 ` void cambiarA(const unsigned short &a) ` 
 cambia el valor Alfa  
    
 ` void cambiarC_rgb(const c_rgb &_rgb) ` 
 cambia todos los valores de **c\_rgb**  
    
 ` inline bool esNull() ` 
 si la clase no tiene nada dentro retornara **true** caso contrario **false**  
    
 ` const char* html() ` 
 retorna su representacion en **hexadecimal** de **RGB** en un array de char que crea su memoria y le asigna los caracteres por lo que no hay que abusar por que es costosa  
    
 ` const char* html_a() ` 
 retorna su representacion en **hexadecimal** de **RGBA** en un array de char que crea su memoria y le asigna los caracteres por lo que no hay que abusar por que es costosa  
    
 ` const char* css() ` 
 retorna su representacion en **hexadecimal** corta de **RGB** usado normalmente en **CSS** en un array de char que crea su memoria y le asigna los caracteres por lo que no hay que abusar por que es costosa  
    
 ` inline unsigned int id() ` 
 retorna **c\_rgb v.id** la informacion de **RGB**  
    
 ` inline unsigned int id_a() ` 
 retorna **c\_rgb v.id\_a** la informacion de **RGBA**  
    
 ` inline unsigned long long info() ` 
 retorna **c\_rgb v.info** la informacion del color **RGBA** y **familia**  
    
 ` inline unsigned short r() ` 
  retorna **c\_rgb v.RGB[\_R\_]**, el valor del color **ROJO**  
    
 ` inline unsigned short g() ` 
   retorna **c\_rgb v.RGB[\_G\_]**, el valor del color **VERDE**  
    
 ` inline unsigned short b() ` 
 retorna **c\_rgb v.RGB[\_B\_]**, el valor del color **AZUL**  
    
 ` inline unsigned short a() ` 
  retorna **c\_rgb v.RGB[\_A\_]**, el valor **ALFA**  
    
 ` inline unsigned char famila() ` 
 retorna **c\_rgb v.RGB[\_F\_]**, la **Familia** del color  
    
 ` inline const c_rgb * crgb() ` 
 retorna **c\_rgb**  
    
 ` void asignarFamilia(bool) ` 
 al asignarle el valor true busca la familia del color y la deja activa, la razon de por que la opcion de busqueda de familia es opcional es para evitar un coste computacional inecesario  
    
#### protected:  
    
` void limpiarhex() ` 
 libera el espacio de memoria del array char que es usado para retornar en las funciones *html(), html_a() y css()* de manera manual  
    
 ` bool cambioRealizado(bool hecho = false) ` 
Este metodo funciona como un medio de comunicacion entre Colori\_rgb con sus clases hijas al asignarle un valor true se indica que hubo un cambio y al ser ejecutado por la clase hija sin la nesecidad de pasarle algun parametro retornara un valor verdadero si hubo un cambio o false en caso contrario, con esto la clase hija podra hacer las operaciones correspondientes que necesite  
    
    
#### private:  
    
` void inicializar() ` 
 inicialisas las variables que contiene la clase  
    
 ` void limpiar() ` 
 libera toda la memoria  
    
 ` void asignarMemoria() ` 
 asigna la memoria a las variables que la necesiten  
    
 ` void __cambio(const unsigned char &rgb,const unsigned short &valor) ` 
 verifica y cambia los tonos de forma independiente de la variable c_rgb al asignarle el indice y el valor correspondiente 
    
    
    
    
  ## ColoriColor.h  
  

 ` class ColoriColor ` 
 hereda de la clase Colori\_rgb, por defecto tiene la busqueda de familia activada para el uso de sus funciones mas importantes  
    
  
 carga de inicio de la clase | valores  
  --- | --- |
  **ColoriColor**() | **void** 
  **ColoriColor**(_const Colori\_rgb &\_rgb_) | **Colori_rgb** 
  **ColoriColor**(_const unsigned long long &Info_) | **c_rgb.info**   
  **ColoriColor**(_const unsigned short &r, const unsigned short &g, const unsigned short &b,const unsigned short &a=0xff_) | **R G B A**  
  **ColoriColor**(_const c\_rgb &RGB_) | **c_rgb**    
  **ColoriColor**(_const std::string &hex_) | **string**  
  
   
   
  #### public:  
    
  ` void cambiarHexa(std::string hex) ` 
 cambia el valor de la variable por medio de el valor escrito en hexadecimal   
    
    
 ` void aligerar(bool limpiar_completamente = true) ` 
libera el espacio de memoria de la variable pero sin tocar el valor principal o un valor especifico que pueda contener -_ejem el respaldo del color, el color resultante de una suma o el mitico array del circulo cromatico etc._ al pasarle false como parametro  
    
    
 ` void restablecer() ` 
tras haberle hecho cambios con sus operadores a la variable esta funcion restablece a la variable a su valor original liberando asi toda la memoria utilizada   
    
    
 ` void cambiarBrillo(double nivel_de_brillo) ` 
 cambia el brillo por un tono mas oscuro o mas brillante valor max de entrada (1 y -1) valor minimo (0)  
    
   
 ` enum coloriMOD ` 
conjunto de valores utilizado para indicar distintos metodos a utilizar en funciones que necesiten de estas   
    
    
 ` const ColoriColor * CirculoCromatico(unsigned short parte_de_circulo, coloriMOD estilo = MOD_RYB, coloriMOD Modo = MOD_FULL) ` 
retorna el circulo cromatico completo o solo la faccion que se desee, para el primer parametro puede usarse ColoriCore/coloridix para un mejor manejo y claridad de lo que se esta pidiendo del color, el parametro estilo puede aceptar el estilo clasico para artistas tradicionales RYB o RGB artistas digitales, el Modo salida puede activarse en MOD_UNITARIO si no se desea asignar la memoria para crear todo el circulo cromatico y solo se desea obtener una parte de el. MOD_FULL es perfecto para usar en bucles ya que crea todo el circulo de un solo golpe y puede ser iterado por medio del primer parametro sin el peligro de excederse del indice ya que retornara nullptr en caso de hacerlo, tambien puede extraer el array al pasarle como primer parametro el enum coloridx {Todo}    
    
    
 ` ColoriColor& operator + ` 
suma los colores y devuelve el color mezclado  
    
    
 ` void operator = ` 
se le puede asignar de forma directa un string, un id/id_a/info en decimal o una variable c_rgb  
    
    
 ` bool operator == ` 
compara su similitud con otro ColoriColor, Colori\_rgb, c\_rgb o notacion decimal _info_, --_NOTA: de momento es extremadamente estricto pero quizas en el futuro lo deje ser mas flexible y que solo sea necesario ver si el color sea el mismo sin importar los demas parametros como alfa, estoy en conflicto ya que no se si sea algo conveniente_     
    
    
 ` bool operator != ` 
si es diferente es true  
    
  ` ColoriColor& operator ++() ` 
auto incremeta su brillo  
    
  ` ColoriColor& operator --() ` 
auto decrementa su nivel de brillo   
    
    
#### private:  
    
  ` enum excepciones ` 
conjunto de valores que determinan la seccion de memoria que no sera eliminada  
   
  ` void liberartmp() ` 
libera la memoria temporal  
   
   
###### la variable Colori\_rgb fue pensada para ser mas rapida que ColoriColor y poder acceder a funcionalidades basicas de convercion y adquisicion de datos, por otro lado ColoriColor fue pensada para el uso de operaciones con colores con simplemente declarar una variable y hacer la operacion pertinente, las ventajas de ambas variables es que sus datos son faciles de exportar atraves de hilos o en un bus de datos, ademas de ser livianas (40 bits) para la cantidad de datos que tienen que usar