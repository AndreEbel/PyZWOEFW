from PyQt5.QtWidgets import QWidget,QLabel,QVBoxLayout, QPushButton, QCheckBox, QButtonGroup

class FilterSelect_base(QWidget):
    """
    Base widget class for use in large, multi-widgets, PyQt application
    """
    def __init__(self, EFW, verbose = False):
        super().__init__()
                
        self.verbose = verbose
        
        # vertical box layout with: 
        ## 5 tick box, one for each filter 
        ## 1 label to tell wich filter is on 
        ## 1 button to set filter 
        self.EFW = EFW
        self.vbox = QVBoxLayout()
        ticks_group = QButtonGroup(self) #this is used to make the checkboxes exclusive
        ticks_group.setExclusive(True)
        self.ticks_filters = []
        for filter in self.EFW.FiltersSlots[0]:
            # print(filter) 
            tick = (QCheckBox(filter))
            self.ticks_filters.append(tick)
            ticks_group.addButton(tick)
        for tick in self.ticks_filters: 
            self.vbox.addWidget(tick)
        self.label_filter = QLabel('No filter')
        self.vbox.addWidget(self.label_filter)
        self.button_setFilter = QPushButton('Set filter',self)
        self.button_setFilter.clicked.connect(self.ClickSetFilter)
        self.vbox.addWidget(self.button_setFilter) 
        self.setLayout(self.vbox)

    def ClickSetFilter(self): 
        channel = []
        for i in range(len(self.ticks_filters)): 
            if self.ticks_filters[i].isChecked(): 
                channel.append(self.ticks_filters[i].text())
         
        if channel: 
            if len(channel)==1: 
                self.EFW.SetColor(0,channel[0])
                self.label_filter.setText('Filter slot is '+ channel[0])
                
class FilterSelect(FilterSelect_base):  
    """ 
    For single wigdet application
    """
    def __init__(self, EFW, verbose= False):
        super().__init__(EFW, verbose)

    def closeEvent(self, event):
        self.label_filter.setText('Closing')
        self.EFW.Close(0)
        event.accept()     