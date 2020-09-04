class Person:
    age = 0
    def __init__(self, age):
        self.age = age
    def Play(self):
        print("play")
    def GetAge(self):
        return self.age
