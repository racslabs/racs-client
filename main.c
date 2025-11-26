#include "src/client.h"
#include "src/socket.h"
#include "src/unpack.h"

unsigned char *read_file(const char *path, size_t *out_size) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;

    // Get file size
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (size < 0) {
        fclose(f);
        return NULL;
    }

    // Allocate buffer
    unsigned char *buf = malloc(size);
    if (!buf) {
        fclose(f);
        return NULL;
    }

    // Read entire file
    size_t read = fread(buf, 1, size, f);
    fclose(f);

    if (read != size) {
        free(buf);
        return NULL;
    }

    *out_size = size;
    return buf;
}

int main(void) {
    racs_client *client = racs_client_open("localhost", 6381);

    racs_result *res = racs_client_execute(client,
        "EXTRACT 'chopin' 2023-12-25T22:30:45.123Z 2026-05-27T02:56:16.123Z |>"
        "FORMAT 'audio/wav' 44100 2 16");

    FILE *fp = fopen("chopin.wav", "wb");
    fwrite(res->data, 1, res->size, fp);
    fclose(fp);


    // racs_result *res = racs_client_execute(client, "CREATE 'chopin' 44100 2 16");
    // racs_result_destroy(res);
    //
    // res = racs_client_execute(client, "OPEN 'chopin'");
    // racs_result_destroy(res);
    //
    // size_t size;
    // unsigned char *data = read_file("/home/corbin/racs-client/chopin.pcm", &size);
    // racs_int32 *_data = racs_s16_s32((racs_int16 *)data, size / 2);
    //
    // racs_client_stream(client, "chopin", 1024 * 32, _data, size / 2);
    //
    // racs_client_close(client);

    return 0;
}