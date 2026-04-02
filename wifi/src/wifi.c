#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/tcp.h"
#include <stdio.h>
#include <string.h>

#define BUTTON_PIN  15
#define SERVER_HOST "192.168.8.131"
#define SERVER_PORT 8080
#define SERVER_PATH "/endpoint"

static volatile bool button_pressed = false;

void button_callback(uint gpio, uint32_t events) {
    printf("Button Pressed!\n");
    button_pressed = true;
}

void send_http_post() {
    struct tcp_pcb *pcb = tcp_new();
    ip_addr_t server_ip;
    
    // Convert string IP to numeric IP
    if (ipaddr_aton(SERVER_HOST, &server_ip)) {
        printf("Connecting to %s...\n", SERVER_HOST);
        
        char request[256];
        snprintf(request, sizeof(request),
            "POST %s HTTP/1.1\r\n"
            "Host: %s\r\n"
            "Content-Length: 0\r\n"
            "Connection: close\r\n\r\n",
            SERVER_PATH, SERVER_HOST);

        if (tcp_connect(pcb, &server_ip, SERVER_PORT, NULL) == ERR_OK) {
            tcp_write(pcb, request, strlen(request), TCP_WRITE_FLAG_COPY);
            tcp_output(pcb);
            printf("POST Sent.\n");
        }
    }
}

int main() {
    stdio_init_all();
    if (cyw43_arch_init()) return 1;

    cyw43_arch_enable_sta_mode();
    printf("Connecting to WiFi: %s\n", WIFI_SSID);

    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("Failed to connect.\n");
        return 1;
    }
    printf("Connected! IP: %s\n", ip4addr_ntoa(netif_ip4_addr(netif_list)));

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    while (true) {
        if (button_pressed) {
            button_pressed = false;
            send_http_post();
        }
        cyw43_arch_poll();
        sleep_ms(10);
    }
}
