(import build/_logfmt :as _logfmt)

(def tests [
  [["foo" "abc"] `foo=abc`]
  [["foo" 123] `foo=123`]
  [["foo" (int/s64 123)] `foo=123`]
  [["foo" "abc def"] `foo="abc def"`]
  [["foo" "abc \" def"] `foo="abc \" def"`]
  [[:foo "abc"] `foo=abc`]
  [['foo "abc"] `foo=abc`]
  [['foo "abc" 'd] `foo=abc d`]
  [['foo "a\r\nbc"] `foo="a\r\nbc"`]
  [[:foo nil] `foo`]])

(each [args expected] tests
  (def actual (_logfmt/fmt @"" ;args))
  (unless (= (string actual) (string expected "\n"))
    (print "expected:")
    (pp (string expected "\n"))
    (print "actual:")
    (pp (string actual))
    (error "fail!")))