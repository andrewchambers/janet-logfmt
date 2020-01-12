(declare-project
  :name "logfmt"
  :author "Andrew Chambers"
  :license "MIT"
  :url "https://github.com/andrewchambers/janet-logfmt"
  :repo "git+https://github.com/andrewchambers/janet-logfmt.git")

(declare-source
  :name "logfmt"
  :source ["logfmt.janet"])

(declare-native
  :name "_logfmt"
  :source ["logfmt.c"])