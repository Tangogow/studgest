# StudGest

Projet C.

## Dependences

gtk3.0

## JSON Structure


list: array
  student:  obj
    id:     int
    first:  str
    last:   str
    prom:   int
    class:  str
    courses: array
      idc:  int
      name: str
      coef: int
      grades: array
        idg: int
        coef: int
        grade: float
