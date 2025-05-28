#include "main.h"
#include "Util.h"
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>


Util util;

int main() {

    // SSL Client Init
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    // Init Context
    const SSL_METHOD *method = TLS_client_method();
    SSL_CTX *ctx = SSL_CTX_new(method);
    if(!ctx){
      ERR_print_errors_fp(stderr);
      return 1;
    }

    // Load cert to ctx
    if (SSL_CTX_use_certificate_file(ctx, "cert/client/client.crt", SSL_FILETYPE_PEM) <= 0) {
      ERR_print_errors_fp(stderr);
      return 1;
    }

    // Load private key to ctx
    if (SSL_CTX_use_PrivateKey_file(ctx, "cert/client/client.key", SSL_FILETYPE_PEM) <= 0) {
      ERR_print_errors_fp(stderr);
      return 1;
    }

    // Load CA cert to verify server
    if (!SSL_CTX_load_verify_locations(ctx, "cert/CA/ca.crt", nullptr)) {
        ERR_print_errors_fp(stderr);
        return 1;
    }

    // Enable server certificate verification
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, nullptr);
    SSL_CTX_set_verify_depth(ctx, 1);

    // define socket handler
    int client_h = socket(AF_INET, SOCK_STREAM, 0); // SOCK_STREAM: safety, SOCK_DGRAM: fast

    // define socket object
    sockaddr_in tls_socket = {};
    tls_socket.sin_family = AF_INET; // AF_INET: IPv4
    tls_socket.sin_port = htons(TLS_PORT);

    // Server Info config
    inet_pton(AF_INET, SERVER_IP, &tls_socket.sin_addr);

    // Create Set SSL Object
    SSL *ssl = SSL_new(ctx); 
    SSL_set_fd(ssl, client_h);

    // Server Connect
    if (connect(client_h, (struct sockaddr *)&tls_socket, sizeof(tls_socket)) < 0) {
        std::cout << "Connect fail" << std::endl;
        close(client_h);
        SSL_CTX_free(ctx);
        return 1;
    }
    else{
      // Connect Success -> TLS HandShake
      std::cout << "Connect Success" << std::endl;

      if(SSL_connect(ssl) <= 0){
        std::cout << "TLS Handshake fail" << std::endl;
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        close(client_h);
        SSL_CTX_free(ctx);
      }

      std::cout << "TLS Handshake success" << std::endl;

    }

    // Test Send
    std::string msg = "Hello from client\n";
    SSL_write(ssl, msg.c_str(), msg.length());

    // Test Read
    char get_buffer[1024] = {0,};
    int read_value_size = SSL_read(ssl, get_buffer, sizeof(get_buffer) - 1);
    if (read_value_size > 0) {
        get_buffer[read_value_size] = '\0';
        std::cout << "Server: " << get_buffer << std::endl;
    }

    // clear context
    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(client_h);
    SSL_CTX_free(ctx);
    return 0;
}