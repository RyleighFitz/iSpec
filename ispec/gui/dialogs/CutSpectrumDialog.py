#
#    This file is part of iSpec.
#    Copyright Sergi Blanco-Cuaresma - http://www.blancocuaresma.com/s/
#
#    iSpec is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Affero General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    iSpec is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Affero General Public License for more details.
#
#    You should have received a copy of the GNU Affero General Public License
#    along with iSpec. If not, see <http://www.gnu.org/licenses/>.
#
import numpy as np
from CustomDialog import *

class CutSpectrumDialog(CustomDialog):
    def __init__(self, parent, title, wave_base, wave_top):
        self.__parent = parent
        self.__title = title
        self.__components = []
        component = {}
        component["type"] = "Entry"
        component["text"] = "Base wavelength"
        component["text-type"] = "float" # float, int or str
        component["default"] = wave_base
        component["minvalue"] = 0.0
        component["maxvalue"] = np.inf
        self.__components.append(component)
        component = {}
        component["type"] = "Entry"
        component["text"] = "Top wavelength"
        component["text-type"] = "float" # float, int or str
        component["default"] = wave_top
        component["minvalue"] = 0.0
        component["maxvalue"] = np.inf
        self.__components.append(component)
        component = {}
        component["type"] = "Radiobutton"
        component["text"] = "Consider"
        component["options"] = ["Custom range (defined above)", "Segments", "Line masks"]
        component["default"] = component["options"][0]
        self.__components.append(component)
        component = {}
        component["type"] = "OptionMenu"
        component["text"] = "Replace by"
        #component["options"] = ["Zeros", "NaN", "Continuum", "Completely remove"]
        component["options"] = ["Zeros", "Completely remove"]
        component["default"] = component["options"][1]
        self.__components.append(component)

    def show(self):
        self.results = None
        CustomDialog.__init__(self, self.__parent, self.__title, self.__components)


