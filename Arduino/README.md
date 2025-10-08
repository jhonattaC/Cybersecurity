**Evil Portal - ESP32 Google Login Phishing**



⚠️ **Aviso Legal:** Este projeto é destinado exclusivamente para fins educacionais e de teste de segurança em ambientes controlados e com autorização prévia. O uso malicioso ou não autorizado desta ferramenta pode violar leis de privacidade e direitos autorais.



📋 **Descrição**

Este projeto transforma um ESP32 em um portal falso (evil portal) que simula a página de login do Google para capturar credenciais. Ele cria um Access Point Wi-Fi com uma interface web que replica a aparência da página oficial de login do Google, permitindo a coleta de e-mails e senhas.



🛠️ **Recursos**

* Cria um Access Point Wi-Fi aberto chamado "WiFi\_Publico"
* Interface web responsiva que replica a página de login do Google
* Captura de credenciais (e-mail e senha) via formulário POST
* Redirecionamento DNS para qualquer domínio acessado
* Feedback visual de sucesso após o envio do formulário



⚙️ **Componentes Necessários**

* ESP32 (NodeMCU, WROOM, ou similar)
* Arduino IDE com suporte ao ESP32
* Bibliotecas: WiFi, WebServer, DNSServer



📦 **Instalação**





1. Instale a Arduino IDE (versão 1.8.19 ou superior)



2\. Adicione o ESP32 à Arduino IDE:

* Vá em Arquivo > Preferências
* Adicione esta URL no campo "URLs Adicionais para Gerenciador de Placas":

&nbsp;  https://dl.espressif.com/dl/package\_esp32\_index.json

* Vá em Ferramentas > Placa > Gerenciador de Placas
* Procure por "ESP32" e instale



3\. Instale as bibliotecas necessárias (geralmente já incluídas com o ESP32):



* WiFi
* WebServer
* DNSServer



4\. Conecte o ESP32 ao computador via cabo USB



5\. Selecione a placa correta em Ferramentas > Placa



6\. Selecione a porta COM em Ferramentas > Porta



7\. Compile e faça upload do código



▶️ **Uso**

* Após o upload, abra o Monitor Serial (´Ferramentas > Monitor Serial`) com baud rate 115200
* O ESP32 iniciará automaticamente o Access Point "WiFi\_Publico"
* Conecte-se ao Wi-Fi "WiFi\_Publico" (sem senha)
* Abra qualquer site no navegador - você será redirecionado automaticamente para a página falsa de login
* As credenciais inseridas serão exibidas no Monitor Serial



📡 **Funcionamento**

* SSID do AP: WiFi\_Publico
* Senha do AP: Nenhuma (aberto)
* IP do AP: Geralmente 192.168.4.1 (exibido no serial)
* Porta DNS: 53
* Porta HTTP: 80



🔐 **Segurança**

* As credenciais capturadas são:



* Exibidas no Monitor Serial do ESP32
* Não são armazenadas permanentemente
* Não são transmitidas pela internet



📝 **Personalização**

* Você pode modificar os seguintes elementos no código:



* Nome do Access Point (linha 12): const char\* ssid = "WiFi\_Publico";
* Página HTML de phishing (variável loginPage)
* Mensagens de sucesso
* Estilos CSS\*



🧪 **Teste de Segurança**

* Para testar em ambiente controlado:



* Configure o ESP32 em rede isolada
* Conecte dispositivos de teste ao AP
* Tente fazer login na página falsa
* Verifique as credenciais no Monitor Serial
* Desative o dispositivo após os testes



📚 **Aprendizado**

* Este projeto demonstra:



* Vulnerabilidades de redes Wi-Fi abertas
* Técnicas de engenharia social
* Importância da verificação de certificados SSL
* Necessidade de redes Wi-Fi protegidas



⚠️ **Responsabilidade**

* O autor não se responsabiliza por:



* Uso indevido desta ferramenta
* Violação de privacidade de terceiros
* Danos causados pelo uso malicioso
* Qualquer atividade ilegal realizada com este código



📄 **Licença**

Este projeto é distribuído para fins educacionais. O uso deve seguir as leis locais e regulamentações de privacidade.

