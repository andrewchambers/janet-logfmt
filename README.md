# janet-logfmt

A logfmt library for janet.

# Quick examples

```
(import logfmt)

# default is stdout
(setdyn :logfmt/out stderr)

(logfmt/log :foo "bar" :baz 123)
foo=bar baz=123

(logfmt/write-to @"" :v 3 bang)
@"v=3 bang\n"

```