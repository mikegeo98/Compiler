make
./compiler < test.tony > out.txt
tail -n 1 out.txt
./compiler < test2.tony > out.txt
tail -n 1 out.txt
./compiler < test3.tony > out.txt
tail -n 1 out.txt
./compiler < test4.tony > out.txt
tail -n 1 out.txt
./compiler < test5.tony > out.txt
tail -n 1 out.txt
./compiler < test6.tony > out.txt
tail -n 1 out.txt
./compiler < lib_mess.tony > out.txt
tail -n 1 out.txt
./compiler < lval_fun.tony > out.txt
tail -n 1 out.txt
./compiler < nil_mess1.tony > out.txt
tail -n 1 out.txt
./compiler < nil_mess_advanced.tony > out.txt
tail -n 1 out.txt
./compiler < var_shadowing_extreme.tony > out.txt
tail -n 1 out.txt
