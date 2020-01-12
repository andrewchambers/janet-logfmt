#define _POSIX_C_SOURCE 200809L
#include <assert.h>
#include <errno.h>
#include <janet.h>
#include <stdio.h>
#include <unistd.h>

static int ident_byte(uint8_t b) {
  return (b > ' ') && (b != '=') && (b != '"');
}

static void buf_quote(JanetBuffer *buf, int32_t from) {
  assert(from < buf->count);
  size_t ntoquote = buf->count - from;
  size_t needed = ntoquote + 2;
  for (size_t i = from; i < (size_t)buf->count; i++)
    if (buf->data[i] == '\"')
      needed += 1;
  uint8_t *quoted = janet_smalloc(needed);
  size_t offset = 0;
  quoted[offset++] = '\"';
  for (size_t i = from; i < from + ntoquote; i++) {
    if (buf->data[i] == '"') {
      quoted[offset++] = '\\';
      quoted[offset++] = '"';
    } else {
      quoted[offset++] = buf->data[i];
    }
  }
  quoted[offset++] = '\"';
  assert(offset == needed);
  janet_buffer_setcount(buf, from);
  janet_buffer_push_bytes(buf, quoted, needed);
  janet_sfree(quoted);
}

static Janet jlogfmt_fmt(int32_t argc, Janet *argv) {
  if (argc < 1)
    janet_panic("expected at least a buffer in slot #0");

  JanetBuffer *buf = janet_getbuffer(argv, 0);

  for (int32_t i = 1; i < argc; i += 2) {
    if (i != 1)
      janet_buffer_push_u8(buf, ' ');

    int32_t kstart = buf->count;
    janet_to_string_b(buf, argv[i]);

    for (size_t j = kstart; j < (size_t)buf->count; j++)
      if (!ident_byte(buf->data[j]))
        janet_panicf("log key in slot #%d not a logfmt ident", i);

    if (i + 1 >= argc || janet_checktype(argv[i + 1], JANET_NIL))
      continue;

    janet_buffer_push_u8(buf, '=');

    int32_t vstart = buf->count;
    janet_to_string_b(buf, argv[i + 1]);
    int needs_quote = 0;
    for (size_t j = vstart; j < (size_t)buf->count; j++)
      if (!ident_byte(buf->data[j]))
        needs_quote = 1;

    if (needs_quote)
      buf_quote(buf, vstart);
  }

  janet_buffer_push_u8(buf, '\n');
  return janet_wrap_buffer(buf);
}

static Janet jlogfmt_no_buffer_write(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 2);
  int flags;
  FILE *f = janet_getfile(argv, 0, &flags);

  if (flags & JANET_FILE_CLOSED)
    janet_panic("log file already closed");

  JanetBuffer *b = janet_getbuffer(argv, 1);

  int fd = fileno(f);
  uint8_t *data = b->data;
  size_t n = b->count;
  int nwritten = 0;
  do {
    nwritten = write(fd, data, n);
    if (nwritten > 0) {
      n -= nwritten;
      data += nwritten;
    }
  } while ((n > 0 && nwritten != -1) || (nwritten == -1 && errno == EINTR));
  if (nwritten < 0)
    janet_panicf("unable to write output: %s", strerror(errno));

  return janet_wrap_nil();
}

static const JanetReg cfuns[] = {
    {"no-buffer-write", jlogfmt_no_buffer_write, ""},
    {"fmt", jlogfmt_fmt,
     "(logfmt/fmt buf & args)\n\n"
     "Write logfmt formatting to buffer, if a value cannot be "
     "formatted the contents of buf may be partially written."},
    {NULL, NULL, NULL}};

JANET_MODULE_ENTRY(JanetTable *env) { janet_cfuns(env, "_logfmt", cfuns); }