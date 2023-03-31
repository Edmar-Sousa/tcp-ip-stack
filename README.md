# tcp-ip-stack
Uma implementação de uma pilha tcp-ip, no espaço de usuário. Este projeto 
serve de aprendizado para programação de sistemas. <br />
O objetivo é implementar as camadas da pilha TCP/IP, enlace, rede, transporte e aplicação.

## check list
- [x] Ler Frame Ethernet
- [x] Analizar Frame Ethernet
- [x] Analizar Pacote ARP
- [ ] Protocolo IP
- [ ] Protocolo ICMP
- [ ] Protocolo TCP

## Como executar
```bash
# No terminal do linux clone o projeto para sua maquina
git clone https://github.com/Edmar-Sousa/tcp-ip-stack.git

# Entre no diretório
cd tcp-ip-stack

# Execute o comando para gerar o executavel
make

# Execute o programa
sudo main

# Em um outro terminal gere trafego ARP com o comando
arping -I tap0 10.0.0.6
```

## Author
- Edmar Sousa. <br><br>
[![linkedin](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/edmar-sousa-9666b0201/)
[![github](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/Edmar-Sousa)
