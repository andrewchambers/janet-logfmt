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