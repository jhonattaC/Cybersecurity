**Keylogger**

Aviso importante:

Ele foi criado para fins de estudo sobre captura de eventos do teclado e práticas de segurança. Não use este código em computadores de terceiros, redes públicas, ou sem o consentimento explícito e informado de todos os proprietários/usuários. O uso indevido pode ser ilegal e causar sérios problemas criminais.

**Objetivos de aprendizagem**

* Entender captura de eventos do teclado em Python.
* Aprender a estruturar um pequeno projeto Python.
* Conhecer riscos de privacidade e técnicas para mitigá-los.
* Praticar testes em ambiente isolado e seguro.

**Requisitos**

- VScode (ou outros IDES)
- Python 3.14
- Dependências listadas: biblioteca pynput

**Como o código funciona**

1. Um listener captura eventos de teclado (teclas pressionadas).
2. Os eventos são registrados em uma variável/estrutura de dados.
3. O projeto originalmente demonstra o envio periódico desses registros por e‑mail.
4. A extensão .pyw do nosso código, executa sem que o usuário perceba.

**Execução:**

1. Rodando o script

```Bash
Python .\keylogger_email
```

2. Abra bloco de notas ou apps de mensagens, digite diversas letras, números, etc...

3. Abra o gmail e verifique o log registrado na caixa de entrada, o código foi configurado para receber log a cada 60 segundos no e-mail.

**Boas práticas e mitigação (tema defensivo)**

* Para proteger usuários, prefira soluções que detectem keyloggers (antivírus, EDR) e políticas organizacionais (controle de aplicações, whitelisting).
* Eduque usuários sobre engenharia social e práticas de segurança (senhas, 2FA).
* Se seu objetivo for pesquisa de segurança, use frameworks e ambientes reconhecidos (laboratórios isolados, ferramentas de pentest com consentimento).
