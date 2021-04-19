from tkinter import *
from tkinter import ttk

dds_vendor = ''

class DdsNode:
    def __init__(self):
        print('initialize DDS Node')
    def set_text_handler(self, data_size_handler, data_rate_handler):
        self.data_size = data_size_handler
        self.data_rate = data_rate_handler

    def set_param(self, data_size, data_rate):
        self.data_size = data_size
        self.data_rate = data_rate

class GuiInterface:
    def __init__(self):
        print('initialize GUI Interface')
        self.dds_list = []
        self.root = Tk()
        self.root.title('LGE RMW Performance Tester')
        self.root.geometry('720x540')

    def run(self):
        self.create_radio_mode()
        self.create_dds_vendor_list()
        self.create_dds_node()
        self.create_start_button()
        self.root.mainloop()

    def create_radio_mode(self):
        frame_radio_mode = LabelFrame(self.root, text='Status')
        frame_radio_mode.pack(fill='both')

        self.mode_var = StringVar()
        radio_mode1 = Radiobutton(frame_radio_mode, text='server', value='server', variable=self.mode_var)
        radio_mode2 = Radiobutton(frame_radio_mode, text='client', value='client', variable=self.mode_var)
        radio_mode3 = Radiobutton(frame_radio_mode, text='localhost', value='localhost', variable=self.mode_var)
        radio_mode3.select()

        radio_mode1.pack(side=LEFT)
        radio_mode2.pack(side=LEFT)
        radio_mode3.pack(side=LEFT)

    def create_dds_vendor_list(self):
        frame_dds_vendor = LabelFrame(self.root, text='DDS Vendor')
        frame_dds_vendor.pack(fill='both')

        self.list_dds_vendor = ttk.Combobox(frame_dds_vendor, values=["rmw_fastrtps_cpp", "rmw_cyclonedds_cpp"])
        self.list_dds_vendor.current(0)
        self.list_dds_vendor.pack(side=LEFT)

    def create_dds_node(self):
        frame_dds_node_bunch = LabelFrame(self.root, text='DDS Node')
        frame_dds_node_bunch.pack(fill='both')
        self.num_node = 0
        btn_add_node = Button(frame_dds_node_bunch, text='+', bg='white', command= lambda: self.Add_dds_node(frame_dds_node_bunch))
        btn_add_node.pack(fill='both')

    def Add_dds_node(self, frame_dds_node_bunch):
        self.num_node += 1
        dds_node = DdsNode()

        frame_dds_node = LabelFrame(frame_dds_node_bunch, text='Node #'+str(self.num_node))
        frame_dds_node.pack(fill='both')
        data_size = ttk.Combobox(frame_dds_node, values=["Array1k", "Array4k", "Array16k", "Array32k", "Array60k", "Array256k", "Array1m", "Array2m", "Array4m", "Array8m"])
        data_size.current(0)
        data_rate = Text(frame_dds_node, width=10, height=1)
        data_rate.insert(END, '1000')
        label_data_size = Label(frame_dds_node, text = 'Data Size ')
        label_data_rate = Label(frame_dds_node, text = ' Data Rate ')

        label_data_size.pack(side=LEFT)
        data_size.pack(side=LEFT)

        label_data_rate.pack(side=LEFT)
        data_rate.pack(side=LEFT)

        dds_node.set_text_handler(data_size, data_rate)
        self.dds_list.append(dds_node)

    def create_start_button(self):
        btn_start = Button(self.root, text='start', command=self.btn_start_handler)
        btn_start.pack()

    def btn_start_handler(self):
        print('handle start button')
        print('Status     : ' + self.mode_var.get())
        print('DDS Vendor : ' + str(self.list_dds_vendor.get()))

        cnt = 1
        for dds_node in self.dds_list:
            print('[Node #' + str(cnt) + ']')
            print(dds_node.data_size.get())
            print(dds_node.data_rate.get('1.0', END))
            cnt += 1

gui_interface = GuiInterface()
gui_interface.run()







