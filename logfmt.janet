(import _logfmt)

(def log-buf @"")

(defn log
  [& args]
  (buffer/clear log-buf)
  (_logfmt/write-to log-buf ;args)
  (def out (dyn :logfmt/out stdout))
  (file/write out log-buf)
  (file/flush out)
  nil)