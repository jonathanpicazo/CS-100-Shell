#/bin/sh
(echo wow && echo lol) || (echo c && echo d)
(echo a && echo b) && (echo c && echo d)
(echo a || echo b && echo c) && (echo d || echo e)
(echo a || echo b || echo c) || (echo d || echo e)
(echo a || echo b || echo c) && (echo d || echo e)
(echo no || echo dude) || (echo a && echo b && echo c)



exit
