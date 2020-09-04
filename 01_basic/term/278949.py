class Menu(object) :
    def __init__(self, title) :
        self.title = title
    def setFunction(self, f) :
        self.func = f
    def command(self) :
        if(self.func() != None) :
            self.func()

class MenuManager(object) :
    def __init__(self):
        self.menus = []
    def addMenu(self, p):
        self.menus.append(p)
    def command(self):
        id = 1
        print("===============================================")
        for p in self.menus:
            print(id,". ", p.title)
            id += 1
        print(id,". ", "종료")
        user_id = int(input("메뉴를 선택하시오: "))
        if(user_id == id) :
            is_exit = input("프로그램을 종료하시겠습니까(y/n)? ")
            if(is_exit == 'n') :
                self.command()
            else :
                return
        else :
            self.menus[user_id-1].command()
            self.command()

class Device(object) :
    def __init__(self, name, num, date) :
        self.name = name
        self.num = num
        self.date = date

class DeviceManager(object) :
    def __init__(self):
        self.devices = []

    def init(self):
        self.menu_manager = MenuManager()
        input_menu = Menu("입력")
        output_menu = Menu("출력")
        search_menu = Menu("검색")
        input_menu.setFunction(self.inputData)
        output_menu.setFunction(self.outputData)
        search_menu.setFunction(self.searchData)
        self.menu_manager.addMenu(input_menu)
        self.menu_manager.addMenu(output_menu)
        self.menu_manager.addMenu(search_menu)

    def run(self):
        self.menu_manager.command()

    def inputData(self) :
        print("===============================================")
        name = input('장비명: ')
        num = int(input('수량: '))
        date = input('생산일(예:1990-01-01): ')
        self.devices.append(Device(name, num, date))
        ch = input('계속 입력하시겠습니까 (y/n)? ')
        if(ch == 'n'):
            return
        else:
            self.inputData()

    def outputData(self) :
        print("-----------------------------------------------")
        print("장비명 \t\t 수량 \t\t 생산일")
        print("-----------------------------------------------")
        for device in self.devices:
            print(device.name, "\t\t", device.num, "\t\t", device.date)

    def searchData(self) :
        device_name = input("검색할 장비명을 입력하세요: ")
        for device in self.devices:
            if(device.name == device_name) :
                print("-----------------------------------------------")
                print("장비명 \t\t 수량 \t\t 생산일")
                print("-----------------------------------------------")
                print(device.name, "\t\t", device.num, "\t\t", device.date)

menu = DeviceManager()
menu.init()
menu.run()