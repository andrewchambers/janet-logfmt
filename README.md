# janet-logfmt

A logfmt library for janet.

# Quick examples

```
(import logfmt)

(logfmt/log stderr :foo "bar" :baz 123)
foo=bar baz=123

(logfmt/fmt @"" :foo "bar")
@"foo=bar\n"
```

# Notes

- You should probably wrap this library with a macro or wrapper function
  adding a default output stream and timestamps.

- The only characters that are escaped are '"' '\r' and '\n' to keep one log entry per line.
  some logfmt implementation do this, others only escape '"'.