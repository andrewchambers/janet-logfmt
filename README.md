# janet-logfmt

A logfmt library for janet.

# Quick examples

```
(import logfmt)

# default is stderr
(setdyn :logfmt/out stdout)
(logfmt/log :foo "bar" :baz 123)
foo=bar baz=123
```

# Notes

- The only characters that are escaped are '"' '\r' and '\n' to keep one log entry per line.
  some logfmt implementation do this, others only escape '"'.