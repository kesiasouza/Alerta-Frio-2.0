
#include "pico/stdlib.h"
#include "hardware_handler.h"
#include "config.h"
#include "mqtt_config.h"
#include <stdio.h>

// Os 4 estados possíveis do nosso sistema
typedef enum {
    ESTADO_AGUARDANDO,
    ESTADO_ANALISANDO,
    ESTADO_ALERTA_ATIVO,
    ESTADO_ALERTA_CONFIRMADO
} SystemState;

int main() {
    // Inicialização
    stdio_init_all();
    hardware_init();
    
    // Conexão Wi-Fi e MQTT
    if (cyw43_arch_init()) { return -1; }
    cyw43_arch_enable_sta_mode();
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000)) { return -1; }
    mqtt_iniciar();
    
    SystemState estado_atual = ESTADO_AGUARDANDO;
    hardware_oled_exibir("AlertaFrio", "Aguardando...");

    while (true) {
        cyw43_arch_poll(); // Mantém a rede funcionando
        
        // A cada loop, verifica se um comando 'ACK' chegou do app
        if (mqtt_comando_ack_recebido()) {
            if (estado_atual == ESTADO_ALERTA_ATIVO) {
                hardware_oled_exibir("Alerta Visto!", "A caminho...");
                estado_atual = ESTADO_ALERTA_CONFIRMADO;
            }
        }

        switch (estado_atual) {
            case ESTADO_AGUARDANDO:
                if (hardware_botao_presenca_pressionado()) {
                    estado_atual = ESTADO_ANALISANDO;
                }
                break;
            
            case ESTADO_ANALISANDO:
                hardware_oled_exibir("Analisando...", "");
                sleep_ms(500); // Pausa para o usuário ver a mensagem
                float temperatura, umidade;
                if (hardware_ler_sensor(&temperatura, &umidade)) {
                    if (temperatura < TEMPERATURA_LIMIAR) {
                        hardware_oled_exibir("ALERTA:", "ITEM FRIO!");
                        hardware_led_set(true); // LIGA O LED VERMELHO
                        char msg_alerta[50];
                        sprintf(msg_alerta, "Alerta de item frio: %.1f C", temperatura);
                        mqtt_publicar(TOPICO_ALERTA, msg_alerta);
                        estado_atual = ESTADO_ALERTA_ATIVO;
                    } else {
                        hardware_oled_exibir("Item nao e frio", "Aguardando...");
                        sleep_ms(2000);
                        estado_atual = ESTADO_AGUARDANDO;
                    }
                } else {
                    hardware_oled_exibir("ERRO NO SENSOR", "Verifique i2c0");
                    sleep_ms(2000);
                    estado_atual = ESTADO_AGUARDANDO;
                }
                break;

            case ESTADO_ALERTA_ATIVO:
            case ESTADO_ALERTA_CONFIRMADO: // A lógica de urgência e recolhimento é a mesma para os dois estados de alerta
                
                // LÓGICA DO BOTÃO DE URGÊNCIA (BOTÃO B)
                if (hardware_botao_urgencia_pressionado()) {
                    hardware_oled_exibir("URGENCIA", "Lider Notificado");
                    mqtt_publicar(TOPICO_URGENTE, "URGENTE: Retirar item frio imediatamente no Caixa 01!");
                    sleep_ms(3000); 
                    // Volta para a tela anterior ao de urgência
                    if (estado_atual == ESTADO_ALERTA_ATIVO) hardware_oled_exibir("ALERTA:", "ITEM FRIO!");
                    else hardware_oled_exibir("Alerta Visto!", "A caminho...");
                }

                // Lógica para quando o item é fisicamente recolhido
                if (!hardware_botao_presenca_pressionado()) {
                    hardware_oled_exibir("Item Recolhido!", "Obrigado!");
                    hardware_led_set(false); // DESLIGA O LED VERMELHO
                    mqtt_publicar(TOPICO_STATUS, "Alerta finalizado (item recolhido).");
                    sleep_ms(2000);
                    hardware_oled_exibir("AlertaFrio", "Aguardando...");
                    estado_atual = ESTADO_AGUARDANDO;
                }
                break;
        }
        sleep_ms(100);
    }
    return 0;
}