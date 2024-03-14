class Vector:
    def __init__(self, values: list[None | int | float]):
        self.values = [value for value in values]
        self.n = len(values)

    def __str__(self) -> str:
        return self.values.__str__()

    def copy(self):
        return Vector([value for value in self.values])

    def __len__(self) -> int:
        return self.values.__len__()

    def __getitem__(self, index: int):
        return self.values[index]

    def __setitem__(self, index: int, value: int | float):
        self.values[index] = value

    def upload_values(self, values: list[list[None | int | float]]):
        self.values = [value for value in values]


class Matrix:
    def __init__(self, values: list[list[None | int | float] | Vector]):
        if type(values[0]) == Vector:
            self.values = [vector.copy() for vector in values]
        else:
            self.values = [Vector(row) for row in values]
        self.n: int = len(self.values)
        self.m: int = len(self.values[0])

    def __str__(self) -> str:
        m = '\n'.join([row.__str__() for row in self.values])
        return f"Shape = {self.get_shape()} \n{m}"

    def get_shape(self) -> tuple[int, int]:
        return self.n, self.m

    def copy(self):
        return Matrix([vect.copy() for vect in self.values])

    def upload_values(self, values: list[list[None | int | float]]):
        self.values = [[val for val in row] for row in values]

    def transposed(self):
        res = [[None] * self.n for _ in range(self.m)]
        for i in range(self.n):
            for j in range(self.m):
                res[j][i] = self.values[i][j]
        return Matrix(res)

    def __setitem__(self, index: int, value: Vector):
        self.values[index] = value

    def __getitem__(self, index: int):
        return self.values[index]