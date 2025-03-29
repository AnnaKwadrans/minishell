# GITHUB

Para traer los cambios de la rama main a tu rama actual, puedes seguir estos pasos:

1. Asegúrate de estar en tu rama:

Primero, verifica que estás en tu rama de trabajo:

```
git checkout nombre_de_tu_rama
```

2. Obtener los últimos cambios de main:

Si no tienes los últimos cambios de main en tu repositorio local, actualiza el repositorio:

```
git fetch origin
```

3. Fusionar los cambios de main en tu rama:

Ahora, puedes fusionar los cambios de main en tu rama actual. Esto lo haces con el comando merge:

git merge origin/main
