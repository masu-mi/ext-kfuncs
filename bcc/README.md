bcc program
-----

This doesn't work correctly. We can't load it, because BCC has white list of callable functions.

ref. https://github.com/iovisor/bcc/blob/7a90c7b232a002f276dacaecc9c714dab75f68ab/src/cc/frontends/clang/b_frontend_action.cc#L1235
