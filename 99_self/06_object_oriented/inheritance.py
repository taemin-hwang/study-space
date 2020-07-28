from person import Person

class Student(Person):
    def __init__(self, age):
        super().__init__(age)

sumin = Student(28)
print("Sumin's Age : ", sumin.GetAge())