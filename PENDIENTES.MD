# REDIRECCIONES

    cat <" fd1 "<" fd2 "<" fd3 > fasdf sa sdfsd"

split()
0 cat
1 " fd1 " >> "fd1"
2 " fd2 " >> "fd2"
3 " fd3 > fsfgdfg sdf" >> "fd3"

    debería verificar los 3 fd e imprimir error en el primero que encuentre. de no encontrar errores, la rediección final será la del último fd.

---

# COMANDOS VACÍOS

manejo errores del cat predeterminado

---

# ECHO (HECHO)

debería haber sólo "-n" o "-nnnnnnn" para que imprima. todo lo demás, deberá imprimir incluido el intento de flag.

---

# EXPAND VARS (HECHO)

manejo de comillas dobles, imprime innecesariamente. Y expansión regulada por un verificador que debemos implementar.

---

# PIPES

Errores de memoria (double free).
