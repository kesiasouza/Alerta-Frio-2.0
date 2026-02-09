# Alerta Frio 2.0: Sistema IoT Interativo para Gestão de Perdas

Sistema embarcado de monitorização térmica e alerta em tempo real, desenvolvido para mitigar perdas financeiras e desperdício de alimentos na cadeia de frio do setor varejista. Este projeto foi realizado como requisito do curso de Formação Inicial e Continuada (FIC) em Sistemas Embarcados da residência tecnológica **EmbarcaTech (IFMA)**.

## 🚀 Funcionalidades
- **Monitorização em Tempo Real:** Leitura constante de temperatura para deteção de falhas de refrigeração.
- **Protocolo MQTT:** Comunicação bidirecional via Wi-Fi para envio de alertas instantâneos para dispositivos móveis.
- **Interface Interativa (HMI):** - Visualização de status no display OLED: "Aguardando", "Alerta" e "Alerta Visto".
  - Botão de Urgência para operadores de caixa.
  - Botão de Confirmação para equipas de manutenção.
- **Notificações Remotas:** Integração com aplicações cliente MQTT para gestão à distância.

## 🛠️ Hardware e Tecnologias
- **Microcontrolador:** Raspberry Pi Pico W (RP2040).
- **Sensores e Periféricos:** - Sensor de Temperatura.
  - Display OLED SSD1306 (via I2C).
  - Buzzer (Alerta sonoro) e Push-buttons.
- **Comunicação:** Wi-Fi utilizando o protocolo MQTT (Broker Mosquitto).
- **Linguagem:** C (Raspberry Pi Pico SDK).

## 📂 Estrutura do Repositório
- `/src`: Código-fonte principal do firmware.
- `/docs`: Relatório técnico detalhado em PDF.
- `/assets`: Imagens e esquemas do projeto.

## 👩‍💻 Autor
- **Késia Lais dos Santos Souza**
- Orientação: Danúbia Soares Pires e Orlando Donato Rocha.

---
*Projeto desenvolvido no Instituto Federal do Maranhão (IFMA) - Campus São Luís Monte Castelo.*
