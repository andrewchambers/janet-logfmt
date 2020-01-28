(import _logfmt)

(var log-buf @"")

(defn log
  "write a log entry to :logfmt/out which must be a file.
  The call bypasses normal file buffering,
  so call file/flush first if you are also using that file
  for other purposes.
  "
  [out & args]
  (buffer/clear log-buf)
  (_logfmt/fmt log-buf ;args)
  (_logfmt/no-buffer-write out log-buf)
  (if (< 8192 (length log-buf))
    (set log-buf @"")
    (buffer/clear log-buf))
  nil)

(def fmt _logfmt/fmt)