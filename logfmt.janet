(import _logfmt)

(def log-buf @"")

(defn log
  "write a log entry to :logfmt/out which may be
  a buffer or file. log bypasses normal file buffering,
  so call file/flush first if needed.
  "
  [& args]
  (def out (dyn :logfmt/out stdout))
  (if (buffer? out)
    (do
      (_logfmt/fmt log-buf ;args)
      nil)
    (do 
      (buffer/clear log-buf)
      (_logfmt/fmt log-buf ;args)
      (_logfmt/no-buffer-write out log-buf)
      nil)))

