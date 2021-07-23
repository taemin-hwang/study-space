class Eyes(object):
    def See(self):
        print('See')
    def Close(self):
        print('Close')

class Animal(object):
    def __init__(self):
        self.eyes = Eyes()

    def __del__(self):
        self.eyes.Close()

    def See(self):
        self.eyes.See()

mouse = Animal()
mouse.See()
