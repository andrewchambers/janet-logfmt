(import _logfmt :prefix "" :export true)

(def log-buf @"")

(defn log
  [& args]
  (buffer/clear log-buf)
  (write-to log-buf ;args)
  (def out (dyn :logfmt/out stdout))
  (file/write out log-buf)
  (file/flush out)
  nil)