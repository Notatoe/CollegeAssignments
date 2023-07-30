from PyQt5 import Qt, QtGui
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5.QtPrintSupport import *
from PyQt5.QtGui import *
import sys

class TextWindow(QWidget):
    def __init__(self):
        super().__init__()
        QWidget.__init__(self)
        
        layout = QGridLayout()
        self.setLayout(layout)
        
        
        menubar = QMenuBar()
        self.statusBar = QStatusBar
        layout.addWidget(menubar,0,0)
        
        #add window title
        text = "Untitled"
        self.title = QLabel(text)
        self.title.setWordWrap(True)
        self.title.setAlignment(Qt.AlignCenter)
        layout.addWidget(self.title)
       
        FBFile = menubar.addMenu("File")
        ### FBFile menu options 
        self.open_new_file_act = QAction("Open", self)
        FBFile.addAction(self.open_new_file_act)
        self.open_new_file_act.triggered.connect(self.open_new_file)

        self.save_current_file_act = QAction("Save", self)
        FBFile.addAction(self.save_current_file_act)
        self.save_current_file_act.triggered.connect(self.save_current_file)
        
        self.file_path = None

        toolsMenu = menubar.addMenu("Tools")

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

        self.scrollable_text_area = QTextEdit()

        layout.addWidget(self.scrollable_text_area)

        self.scrollable_text_area.textChanged.connect(self.WordCount)
        self.WordCount()

    def WordCount(self):
        #Count the number of words in a document
        #May have to rework this implementation
        text = self.scrollable_text_area.toPlainText()
        count = 0
        words = text.split()
        for word in words:
            count = count + 1
            
        message = "Word Count : " + str(count)
        self.statusBar().showMessage(message)
        return str(count)

    def open_new_file(self):
        self.file_path, filter_type = QFileDialog.getOpenFileName(self, "Open new file",
                "", "All files (*)")
        if self.file_path:
            with open(self.file_path, "r") as f:
                file_contents = f.read()
                self.title.setText(self.file_path)
                self.scrollable_text_area.setText(file_contents)
        else:
            self.invalid_path_alert_message()

    def save_current_file(self):
        if not self.file_path:
            new_file_path, filter_type = QFileDialog.getSaveFileName(self, "Save this file as...", "", "All files (*)")
            if new_file_path:
                self.file_path = new_file_path
            else:
                self.invalid_path_alert_message()
                return False
        file_contents = self.scrollable_text_area.toPlainText()
        with open(self.file_path, "w") as f:
            f.write(file_contents)
        self.title.setText(self.file_path)
    
    def invalid_path_alert_message(self):
        messageBox = QMessageBox()
        messageBox.setWindowTitle("Invalid file")
        messageBox.setText("Selected filename or path is not valid. Please select a valid file.")
        messageBox.exec()
    
    #when font options is pressed, bring up the font menu and set the text to the selected options
    def font_options(self):
        font, ok = QFontDialog.getFont(self.scrollable_text_area.font(), self)
        if ok:
            self.scrollable_text_area.setFont(font)

    #when black is pressed, set the text color to black
    def black(self):
        self.scrollable_text_area.setTextColor(QtGui.QColor("#000000"))

    #when red is pressed, set the text color to red
    def red(self):
        self.scrollable_text_area.setTextColor(QtGui.QColor("#FF0000"))

    #when yellow is pressed, set the text color to yellow
    def yellow(self):
        self.scrollable_text_area.setTextColor(QtGui.QColor("#FFFF00"))

    #when blue is pressed, set the text color to blue
    def blue(self):
        self.scrollable_text_area.setTextColor(QtGui.QColor("#0000FF"))

    #when green is pressed, set the text color to green
    def green(self):
        self.scrollable_text_area.setTextColor(QtGui.QColor("#00FF00"))

    #when highlight on is pressed, toggles the highlighter to on
    def highlight1(self):
        self.scrollable_text_area.setTextBackgroundColor(QtGui.QColor("#CCFF00"))

    #when highlight off is pressed, toggles the highlighter to off
    def highlight2(self):
        self.scrollable_text_area.setTextBackgroundColor(QtGui.QColor("#FFFFFF"))
    
if __name__ == '__main__':
    app = QApplication(sys.argv)
    screen = TextWindow()
    screen.showMaximized()
    sys.exit(app.exec_())