#include "src/client.h"
#include "src/socket.h"
#include "src/unpack.h"

int main(void) {
    racs_client *client = racs_client_open("localhost", 6381);

    racs_result *res = racs_client_execute(client, "LS '*'");
    racs_result *s = ((racs_result **)res->data)[0];

    printf("%s", (char *)s->data);


    return 0;
}