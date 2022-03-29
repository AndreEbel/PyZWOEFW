from PyZWOEFW.PyQt_Widget import FilterSelect
from PyQt5 import QtCore
from PyQt5.QtWidgets import QApplication
import sys

from PyZWOEFW import EFW

   
def ZwoEFW(library_file = None, verbose = False): 
    app = QtCore.QCoreApplication.instance()
    if app is None:
        app = QApplication(sys.argv)
    wheel = EFW(library_file, verbose)
    # print(wheel.IDs)
    wheel.SetFiltersNames(0, {0: 'empty', 
                                1: 'R', 
                                2: 'G', 
                                3: 'B', 
                                4: 'L'})
    a = FilterSelect(wheel, verbose)
    a.show()
    app.exec_()