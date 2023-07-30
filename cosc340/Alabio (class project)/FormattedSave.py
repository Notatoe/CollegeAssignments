'''
    Implementation of saving and loading formatted text
'''

import sys
import io
from PyQt5 import QtGui
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *

class Window(QMainWindow):
    def __init__(self):
        super().__init__()
        
        self.setGeometry(500, 500, 500, 500)

        self.setWindowTitle("Text Tools")

        #creates the central widget and text box
        self.text_box = QWidget()
        self.text_box = QTextEdit()

        self.setCentralWidget(self.text_box)

        #creates the menu bar and the tools menu
        menu = self.menuBar()
        fileMenu = menu.addMenu("File")
        toolsMenu = menu.addMenu("Tools")

        #directory used for saving purposes
        self.directory = ""

        #for saving a new file
        saveas_option = QAction("Save As", self)
        saveas_option.triggered.connect(self.saveas_option)
        fileMenu.addAction(saveas_option)

        #for saving the preexisting file in use
        save_option = QAction("Save", self)
        save_option.triggered.connect(self.save_option)
        fileMenu.addAction(save_option)

        #for loading a file
        load_option = QAction("Load", self)
        load_option.triggered.connect(self.load_option)
        fileMenu.addAction(load_option)

        #creates the font options action that opens up a window that allows for changing the font,
        #changing the font size, bolding, underlining, striking, and other options depending on the font selected
        font_options = QAction("Font Options", self)
        font_options.triggered.connect(self.font_options)
        toolsMenu.addAction(font_options)

        #creates the font color sub-menu that when hovered over shows some colors to change the text to
        fontColor = toolsMenu.addMenu("Font Color")

        #creates the black action which changes the text's color to black
        black = QAction("Black", self)
        black.triggered.connect(self.black)
        fontColor.addAction(black)

        #creates the red action which changes the text's color to red
        red = QAction("Red", self)
        red.triggered.connect(self.red)
        fontColor.addAction(red)

        #creates the yellow action which changes the text's color to yellow
        yellow = QAction("Yellow", self)
        yellow.triggered.connect(self.yellow)
        fontColor.addAction(yellow)

        #creates the blue action which changes the text's color to blue
        blue = QAction("Blue", self)
        blue.triggered.connect(self.blue)
        fontColor.addAction(blue)

        #creates the green action which changes the text's color to green
        green = QAction("Green", self)
        green.triggered.connect(self.green)
        fontColor.addAction(green)

        #creates the highlight sub-menu where you can toggle highlighting on or off
        highlight = toolsMenu.addMenu("Highlight")
        
        #creates the on action which turns highlighting on
        highlight1 = QAction("On", self)
        highlight1.triggered.connect(self.highlight1)
        highlight.addAction(highlight1)

        #creates the off action which turns highlighting off
        highlight2 = QAction("Off", self)
        highlight2.triggered.connect(self.highlight2)
        highlight.addAction(highlight2)

        self.show()

    #when font options is pressed, bring up the font menu and set the text to the selected options
    def font_options(self):
        font, ok = QFontDialog.getFont(self.text_box.font(), self)
        if ok:
            self.text_box.setFont(font)

    #when black is pressed, set the text color to black
    def black(self):
        self.text_box.setTextColor(QtGui.QColor("#000000"))

    #when red is pressed, set the text color to red
    def red(self):
        self.text_box.setTextColor(QtGui.QColor("#FF0000"))

    #when yellow is pressed, set the text color to yellow
    def yellow(self):
        self.text_box.setTextColor(QtGui.QColor("#FFFF00"))

    #when blue is pressed, set the text color to blue
    def blue(self):
        self.text_box.setTextColor(QtGui.QColor("#0000FF"))

    #when green is pressed, set the text color to green
    def green(self):
        self.text_box.setTextColor(QtGui.QColor("#00FF00"))

    #when highlight on is pressed, toggles the highlighter to on
    def highlight1(self):
        self.text_box.setTextBackgroundColor(QtGui.QColor("#CCFF00"))

    #when highlight off is pressed, toggles the highlighter to off
    def highlight2(self):
        self.text_box.setTextBackgroundColor(QtGui.QColor("#FFFFFF"))


    '''
        FORMATTED TEXT FUNCTIONS
    '''
    def saveas_option(self):
        directory, _ = QFileDialog.getSaveFileName(self, "Save file", "", "HTML documents (*.html)")
        self.directory = directory
        text = self.text_box.toHtml()
        file = io.open(directory, "w")
        file.write(text)
        file.close()

    def save_option(self):
        if(self.directory == ""):
            self.saveas_option()
        else:
            text = self.text_box.toHtml()
            file = io.open(self.directory, "w")
            file.write(text)
            file.close()

    def load_option(self):
        directory, _ = QFileDialog.getOpenFileName(self, "Open file", "", "HTML documents (*.html)")
        self.directory = directory
        file = io.open(directory, "r")
        text = file.read()
        self.text_box.setText(text)

if __name__ == '__main__':
    app = QApplication(sys.argv)
   
    window = Window()

    window.show()

    sys.exit(app.exec())