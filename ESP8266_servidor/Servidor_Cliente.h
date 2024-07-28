
//==================================================================================
//                                   FrontEnd
//==================================================================================

String Pagina =  R"====(<!doctypehtml><html lang=en><meta charset=UTF-8><meta content="width=device-width,initial-scale=1"name=viewport><title>ESP8266 Server Checking</title><style>html{font-family:'Segoe UI',tahoma,Geneva,Verdana,sans-serif;background:#000;background:linear-gradient(to right,#5b5757,#000);display:inline-block;text-align:center}body{margin:0 auto;max-width:600px;padding-bottom:25px;display:flex;align-items:center;justify-content:center;height:100vh}h1{text-decoration:underline;font-size:2.7rem;color:#0a21ee;border-radius:8px;background:repeating-linear-gradient(-45deg,rgba(0,0,0,.7) 1px,rgba(246,255,0,.5) 10px)}h4{font-family:Arial,sans-serif;font-size:20px;margin:0;padding:0;display:flex;align-items:center;justify-content:center;height:15vh;color:#000}.contenedor{background-color:#fff;padding:20px;border-radius:8px;box-shadow:0 0 10px rgba(0,0,0,1.5)}.espacio_contenedor{position:relative;margin-top:20px;display:flex;flex-direction:column;align-items:center;justify-content:center;max-width:600px}#valor_distancia{margin-left:10px;margin-right:10px;height:33px;font-weight:700;color:#007bff}.rango{font-size:20px}.btn{position:relative;top:-36em;background-color:transparent;--c:#F3CE5E;color:var(--c);font-size:15px;border:.3em solid var(--c);border-radius:1.9em;width:9em;height:3em;text-transform:uppercase;font-weight:700;font-family:sans-serif;letter-spacing:.1em;text-align:center;line-height:1em;overflow:hidden;z-index:1;transition:.5s;margin:-4em;content:📤}.btn span{position:absolute;width:25%;height:100%;background-color:var(--c);transform:translateY(150%);border-radius:50%;left:calc((var(--n) - 1) * 25%);transition:.5s;transition-delay:calc((var(--n) - 1) * .1s);z-index:-1}.btn:hover{--c:#FDA8CF;color:#000}.btn::after{content:"📤";font-size:30px;transition:.5s}.btn:hover::after{font-size:medium;content:"Actualizar"}.btn:hover span{transform:translateY(0) scale(2)}.btn span:nth-child(1){--n:1}.btn span:nth-child(2){--n:2}.btn span:nth-child(3){--n:3}.btn span:nth-child(4){--n:4}</style><div class=contenedor><h1 class=titulo>Fisgon Parking Monitoring</h1><div class=espacio_contenedor><h4 class=display id=dist1>Parqueadero 1: <span class=display id=valor_distancia1>---</span> Cm</h4><output class=rango id=rango_valP1>40</output><br><input id=rangoP1 max=450 min=2 oninput="rango_valP1.value=value"type=range value=40><h4 class=display id=dist2>Parqueadero 2: <span class=display id=valor_distancia2>---</span> Cm</h4><output class=rango id=rango_valP2>40</output><br><input id=rangoP2 max=450 min=2 oninput="rango_valP2.value=value"type=range value=40><div><button class=btn onclick=Pagina2()><span></span><span></span><span></span><span></span></button></div></div></div><script>let ejecutar = false;
        const tiempoAgotado = 5000;
        const dist1 = document.getElementById('valor_distancia1');
        const dist2 = document.getElementById('valor_distancia2');
        const elementoRango1 = document.getElementById('rangoP1');
        const elementoRango2 = document.getElementById('rangoP2');

        elementoRango1.addEventListener('click', cambiarDistancia1);
        elementoRango2.addEventListener('click', cambiarDistancia2);


        function actualizarDistancia1(processTemp){
            if(ejecutar){
                console.log("La actualización del sensor 1 ya se está ejecutando. No se permiten llamadas concurrentes.");
                return;
            }

            ejecutar = true;

            return new Promise((resolve, reject) => {
                let xhr = new XMLHttpRequest();

                xhr.onreadystatechange = () => {
                    if(xhr.readyState === 4){ //Hecho = 4
                        if(xhr.status === 200) {
                            console.log("Respuesta del servidor para distancia 1:", xhr.responseText);
                            dist1.innerText = xhr.responseText;
                            resolve();
                        }else{
                            reject("Error al obtener distancia 1:", xhr.statusText);
                        }
                        ejecutar = false;
                    }           
                }
                xhr.open('GET', "/Sensor1")
                xhr.send();
            });            
        }

        function actualizarDistancia2(processTemp){
            if(ejecutar){
                console.log("La actualización del sensor 2 ya se está ejecutando. No se permiten llamadas concurrentes.");
                return;
            }

            ejecutar = true;

            return new Promise((resolve, reject) => {
                let xhr = new XMLHttpRequest();

                xhr.onreadystatechange = () => {
                    if (xhr.readyState === 4) { //Hecho = 4
                        if(xhr.status === 200) {
                            console.log("Respuesta del servidor para distancia 2:", xhr.responseText);
                            dist2.innerText = xhr.responseText;
                            resolve();
                        }else{
                            reject("Error al obtener distancia 2:", xhr.statusText);
                        }
                        ejecutar = false;
                    }
                }
                xhr.open('GET', "/Sensor2")
                xhr.send();
            });            
        }

        async function actualizarDistancias(){
            try {
                await actualizarDistancia1();
                await actualizarDistancia2();                

            } catch (error) {
                console.error(error);
            }
        }

        function cambiarDistancia1(){
            const elementoRango1 = document.getElementById('rangoP1');
            console.log("Cambiando distancia del sensor a " + elementoRango1.value + " para el parqueadero 1");
            consultaGET("http://%ip/nivel1?valor=" + elementoRango1.value);
        }

        function cambiarDistancia2(){
            const elementoRango2 = document.getElementById('rangoP2');
            console.log("Cambiando distancia del sensor a " + elementoRango2.value + " para el parqueadero 2");
            consultaGET("http://%ip/nivel2?valor=" + elementoRango2.value);
        }

        function Pagina2(){
            window.location.href = "/actualizacion";
        }

        function consultaGET(consulta){
            const Http = new XMLHttpRequest();
            console.log(`Consultando  ${consulta}`)
            Http.open("GET", consulta);
            Http.send();

            Http.onreadystatechange = (e) =>{
                console.log(Http.status);
                console.log(Http.responseText);
            };
        }

        document.addEventListener('DOMContentLoaded', () => {
            console.log('Página cargada!');
            setInterval(actualizarDistancias, tiempoAgotado);
        });</script>)====";

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

String Pagina2 = R"====(<!doctypehtml><html lang=en><meta charset=UTF-8><meta content="width=device-width,initial-scale=1"name=viewport><title>ESP8266 Server Update</title><style>html{font-family:'Segoe UI',tahoma,Geneva,Verdana,sans-serif;background:#000;background:linear-gradient(to right,#5b5757,#000);display:inline-block;text-align:center}body{margin:0 auto;max-width:400px;padding-bottom:25px;display:flex;align-items:center;justify-content:center;height:100vh}input{color:#000;text-align:center;font-size:24px;margin-top:20px;border-radius:8px}.contenedor{background-color:#fff;padding:20px;border-radius:8px;box-shadow:0 0 10px rgba(0,0,0,1.5);z-index:5}.espacio_contenedor{position:relative;margin-top:20px;min-width:300px;max-width:600px}.browser{padding:15px;width:100%;overflow:hidden;box-sizing:border-box}.updater{color:#000;margin-top:-4px}.textbox{margin-top:-5px}#btn{background:#fff;border:0;font-family:Montserrat,sans-serif;font-size:30px;font-weight:lighter;letter-spacing:1px;font-weight:600;width:100%;height:100%;border-radius:75px}#btn2{background:#fff;border:0;font-family:Montserrat,sans-serif;font-size:20px;font-weight:lighter;letter-spacing:1px;font-weight:500}.btn2{margin-top:10px;text-align:center;display:flex;align-items:center;justify-content:center;position:relative;margin:20px auto;width:200px;height:50px;background:#fff;border-radius:75px;transition:1s box-shadow;box-shadow:0 0 10px rgba(0,0,0,.5)}.btn2:hover{box-shadow:0 5px 35px 0 rgba(0,0,0,.1)}.btn2:hover::after,.btn2:hover::before{display:block;content:'';position:absolute;width:200px;height:50px;background:#fda8cf;border-radius:75px;z-index:-1;animation:1s clockwise infinite}.btn2:hover:after{background:#f3ce5e;animation:2s counterclockwise infinite}.btn{text-align:center;display:flex;align-items:center;justify-content:center;position:relative;margin:20px auto;width:250px;height:100px;background:#fff;border-radius:75px;transition:1s box-shadow;box-shadow:0 0 10px rgba(0,0,0,.5)}.btn:hover{box-shadow:0 5px 35px 0 rgba(0,0,0,.1)}.btn:hover::after,.btn:hover::before{display:block;content:'';position:absolute;width:250px;height:100px;background:#fda8cf;border-radius:75px;z-index:-1;animation:1s clockwise infinite}.btn:hover:after{background:#f3ce5e;animation:2s counterclockwise infinite}@keyframes clockwise{0%{top:-5px;left:0}12%{top:-2px;left:2px}25%{top:0;left:5px}37%{top:2px;left:2px}50%{top:5px;left:0}62%{top:2px;left:-2px}75%{top:0;left:-5px}87%{top:-2px;left:-2px}100%{top:-5px;left:0}}@keyframes counterclockwise{0%{top:-5px;right:0}12%{top:-2px;right:2px}25%{top:0;right:5px}37%{top:2px;right:2px}50%{top:5px;right:0}62%{top:2px;right:-2px}75%{top:0;right:-5px}87%{top:-2px;right:-2px}100%{top:-5px;right:0}}.interno .btn3{position:relative;top:-33em;background-color:transparent;--c:#F3CE5E;color:var(--c);font-size:15px;border:.3em solid var(--c);border-radius:1.9em;width:9em;height:3em;text-transform:uppercase;font-weight:700;font-family:sans-serif;letter-spacing:.1em;text-align:center;line-height:1em;overflow:hidden;z-index:1;transition:.5s;margin:-4em}.interno .btn3 span{position:absolute;width:25%;height:100%;background-color:var(--c);transform:translateY(150%);border-radius:50%;left:calc((var(--n) - 1) * 25%);transition:.5s;transition-delay:calc((var(--n) - 1) * .1s);z-index:-1}.interno .btn3:hover{--c:#FDA8CF;color:#000}.interno .btn3:hover span{transform:translateY(0) scale(2)}.interno .btn3 span:nth-child(1){--n:1}.interno .btn3 span:nth-child(2){--n:2}.interno .btn3 span:nth-child(3){--n:3}.interno .btn3 span:nth-child(4){--n:4}</style><div class=contenedor><div class=espacio_contenedor><div class=textbox><input id=usuario placeholder=Usuario></div><div class=textbox><input id=password placeholder=Contraseña type=password></div><div class=btn2 id=btn2><button id=btn2>Verificar</button></div><form action=/actualizar class=browser enctype=multipart/form-data method=POST><input type=file name=update><br><div class=btn><input id=btn type=submit class=updater value=Cargar></div></form><div class=interno><div><button class=btn3 onclick=Pagina1()>⮌ <span></span><span></span><span></span><span></span></button></div></div></div></div><script>const btn = document.getElementById("btn");
    const btn2 = document.getElementById("btn2");
    btn.setAttribute("disabled", "");
    btn2.addEventListener("click", Verificar);
    
    function Verificar(){
      
      const usuario = document.getElementById("usuario");
      const password = document.getElementById('password');
      const usuarioV = "admin";
      const passwordV = "admin";

      if(usuario.value.localeCompare(usuarioV, 'en', {sensitivity: 'base'}) === 0  && password.value.localeCompare(passwordV, 'en', {sensitivity: 'base'}) === 0){
        btn.disabled = false;
        alert("Bienvenido master");
      
      }else{
        btn.disabled = true;
        alert("Usuario o contraseña incorrecto");
      }
    }

    function Pagina1(){
      window.location.href = "/";
    }


    function consultaGET(consulta){
      const Http = new XMLHttpRequest();
      console.log(`Consultando  ${consulta}`)
      Http.open("GET", consulta);
      Http.send();

      Http.onreadystatechange = (e) =>{
        console.log(Http.status);
        console.log(Http.responseText);
      };
    }</script>)====";

/***************************************************************************************************************************************/
/***************************************************************************************************************************************/
/***************************************************************************************************************************************/
void paginaInicio(){
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/html", Pagina);
}

void PaginaActu() {
  server.sendHeader("Connection", "close");
  server.send(200, "text/html", Pagina2);
}

void ActualizarPaso1() {
  server.sendHeader("Connection", "close");
  server.send(200, "text/plain", (Update.hasError()) ? "Fallo al actualizar" : "OK");
  ESP.restart();
}

void ActualizarPaso2() {
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    Serial.setDebugOutput(true);
#if defined(ESP8266)
    WiFiUDP::stopAll();
#endif
    Serial.printf("Actualizanddo: %s\n", upload.filename.c_str());
    uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
    if (!Update.begin(maxSketchSpace)) {
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (Update.end(true)) {
      Serial.printf("Actualización Exitosa: %u\nReiniciando...\n", upload.totalSize);
    } else {
      Update.printError(Serial);
    }
    Serial.setDebugOutput(false);
  } else {
    Serial.printf("Problema con la Actualización, revise la conexión; Estado=%d\n", upload.status);
  }
  yield();
}

void mensajeError() {
  String mensaje = "<h1>404</h1>";
  mensaje += "Pagina No encontrada</br>";
  mensaje += "Intenta otra pagina</br>";
  server.send(404, "text/html", mensaje);
}


void Dispositivo1(){
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", String(dist_sen1));
}

void funcionNivel1() {

  if (server.hasArg("valor")) {
    Valor1 = server.arg("valor");
    Nivel1 = atoi(Valor1.c_str());
    Serial << "Cambiando nivel " << Nivel1 << "\n";
  }
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Nivel Cambiado");
}

void Dispositivo2(){
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", String(dist_sen2));
}

void funcionNivel2() {

  if (server.hasArg("valor")) {
    Valor2 = server.arg("valor");
    Nivel2 = atoi(Valor2.c_str());
    Serial << "Cambiando nivel " << Nivel2 << "\n";
  }
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "Nivel Cambiado");
}

//==================================================================================
//                                    BackEnd
//==================================================================================

void EnvioUDP(){
  String ip = Udp_receiving.remoteIP().toString();

  if(ip == "192.168.4.4"){
    paquete2.distanciaCambio = Nivel1;
    IPAddress Ip_Cliente1  (192, 168, 4, 4);

    if(Udp_sending.beginPacket(Udp_sending.remoteIP(), Udp_sending.remotePort())){
      Udp_sending.write((byte *)&paquete2, sizeof(Paquete_UDP2));
      Udp_sending.endPacket();
      Serial << "Paquete enviado a " << ip << "\n";
    }else{
      Serial.println("Error al enviar el paquete\n");
    }
    
    ip = "";
    
  }else if (ip == "192.168.4.3"){
    
    paquete2.distanciaCambio = Nivel2;
    IPAddress Ip_Cliente2 = (192, 168, 4, 3);

    if(Udp_sending.beginPacket(Udp_sending.remoteIP(), Udp_sending.remotePort())){
      Udp_sending.write((byte *)&paquete2, sizeof(Paquete_UDP2));
      Udp_sending.endPacket();
      Serial << "Paquete enviado a " << ip << "\n";
    }else{
      Serial.println("Error al enviar el paquete\n");
    }
    
    ip = "";
    
  }else{
    Serial.println("Estación no conectada o IP no configurada");
  }
}

void LectorUDP(){
  //Si hay información disponible leerá el paquete
  int tamanoPaquete = Udp_receiving.parsePacket();

  if (tamanoPaquete){
    Serial << "\nPaquete de tamaño " << tamanoPaquete << " recibido\n";
    Serial << "De: " << Udp_receiving.remoteIP() << ", puerto: " << Udp_receiving.remotePort() << "\n";

    int len = Udp_receiving.read((byte *)&paquete, sizeof(Paquete_UDP));
    if (len > 0) {
      char* incomingPacket = new char[sizeof(Paquete_UDP)];
      incomingPacket[len] = 0;
    }

    Serial.println("Contenido: ");
    Serial << "ID: " << paquete.id << "\n" << "Estado: " << paquete.sended << "\n";

    if(paquete.id == 1){
      dist_sen1 = paquete.distancia;
      Serial << "Sensor 1: " << dist_sen1 << " cm" << "\n";
      
    }else if(paquete.id == 2){
      dist_sen2 = paquete.distancia;
      Serial << "Sensor 2: " << dist_sen2 << " cm" << "\n";
    }
  }else{
    Serial.println("Error al recibir paquete. Tamaño del paquete incorrecto.");
  }
  //EnvioUDP();
}
