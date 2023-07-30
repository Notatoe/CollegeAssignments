'''
    Implementation of the Find Function

    This program implements a find function that tells you where every occurance of a word is located at.
'''

import sys
from PyQt5 import QtGui, QtWidgets, QtCore
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *

#Child window that pops up and takes in the word to find
class searchWindow(QWidget):

    text = QtCore.pyqtSignal(str)

    def __init__(self):
        super().__init__()

        #window size and title
        self.setGeometry(500, 500, 320, 120)
        self.setWindowTitle("Find")
        
        #small text box for inputting search word
        self.textbox = QTextEdit(self)
        self.textbox.move(20, 20)
        self.textbox.resize(280, 30)
        
        #button to close and send the inputted text
        self.button = QPushButton("OK", self)
        self.button.move(20, 70)
        self.button.clicked.connect(self.toText)

    #upon closing the window, the inputted string is converted to plaintext and emitted to be taken in by the parent window
    def toText(self):
        word = self.textbox.toPlainText()
        self.text.emit(word)
        self.close()

class addWindow(QWidget):
    def __init__(self):
        super().__init__()

        #window size and title
        self.setGeometry(500, 500, 320, 120)
        self.setWindowTitle("Add Word")
        
        #small text box for inputting words you want to add
        self.textbox = QTextEdit(self)
        self.textbox.move(20, 20)
        self.textbox.resize(280, 30)
        
        #button to add the inputted text
        self.button = QPushButton("Add", self)
        self.button.move(20, 70)
        self.button.clicked.connect(self.addWord)

    def addWord(self):
        #converts the text to a string and sets it to lowercase
        text = self.textbox.toPlainText()
        text = text.lower()

        #does not add the word if there are multiple words put in the text box
        if len(text.split()) > 1:
            popup = QMessageBox()
            popup.setText("Word Not Added: Multiple Words Entered")
            popup.exec_()
            return

        #does not add the word if the word contains a symbol or number
        if not text.isalnum() or text.isdigit():
            popup = QMessageBox()
            popup.setText("Word Not Added: Includes symbol/number")
            popup.exec_()
            return

        #makes sure the word does not already exist within the given dictionary
        with open("dictionaries/dictionary.txt", "r") as file1:
                    for j in file1:
                        j = j.strip()
                        if text == j:
                            popup = QMessageBox()
                            popup.setText("Word Not Added: Already In Dictionary")
                            popup.exec_()
                            return

        #makes sure the word does not already exist within the custom dictionary
        with open("dictionaries/custom_dictionary.txt", "r") as file2:
                    for k in file2:
                        if text == k:
                            popup = QMessageBox()
                            popup.setText("Word Not Added: Already In Custom Dictionary")
                            popup.exec_()
                            return

        #enters the word into the custom dictionary txt file   
        file = open("dictionaries/custom_dictionary.txt", "a")
        file.write("\n")
        file.write(text)
        file.close()

        #gives a popup letting the user know the word was added
        popup = QMessageBox()
        popup.setText("Word Added")
        popup.exec_()
        return


class Window(QMainWindow):
    def __init__(self):
        super().__init__()
        
        self.setGeometry(500, 500, 500, 500)

        self.setWindowTitle("Text Tools")

        self.text_box = QWidget()
        self.text_box = QTextEdit()

        self.setCentralWidget(self.text_box)

        menu = self.menuBar()
        toolsMenu = menu.addMenu("Tools")

        #find tool button added
        find = QAction("Find", self)
        find.triggered.connect(self.find)
        toolsMenu.addAction(find)

        #remove highlights tool button added
        remover = QAction("Remove Highlights", self)
        remover.triggered.connect(self.remover)
        toolsMenu.addAction(remover)

        adder = QAction("Add Word To Dictionary", self)
        adder.triggered.connect(self.adder)
        toolsMenu.addAction(adder)

        self.show()

    def adder(self):
        self.addWord = addWindow()
        self.addWord.show()

    #brings up the child window and continues to find2 upon closing
    def find(self):
        self.findBox = searchWindow()
        self.findBox.text.connect(self.find2)
        self.findBox.show()

    #upon closing the child window the inputted text is transfered over
    @QtCore.pyqtSlot(str)
    def find2(self, word):
        #search word, set to lowercase so the search is not case sensitive
        input = word
        input = input.lower()

        #takes in the text file
        text = self.text_box.toPlainText()
        words = text.split()

        #puts a cursor over the text file that goes down each word
        cursor = self.text_box.textCursor()
        cursor.movePosition(1, 0, 1)
        cursor.movePosition(14, 1, 1)

        #blue highlight format for the found words
        highlight = QTextCharFormat()
        highlight.setBackground(QtGui.QColor("#30C5FF"))

        #for every word in the text file
        for i in words:
            i = i.lower()

            #if the current word matches the input
            if  i == input:
                #set the word within the text file to be highlighted
                cursor.setCharFormat(highlight)
            
            #moves to the next word within the text file
            cursor.movePosition(18, 0, 1)
            cursor.movePosition(5, 0, 1)
            cursor.movePosition(14, 1, 1)

    def remover(self):
        #puts a cursor over the text file that goes down each word
        cursor = self.text_box.textCursor()
        cursor.movePosition(1, 0, 1)
        cursor.movePosition(11, 1, 1)

        clear = QTextCharFormat()
        clear.setBackground(QtGui.QColor("#FFFFFF"))

        cursor.setCharFormat(clear)

if __name__ == '__main__':
    app = QApplication(sys.argv)
   
    window = Window()

    window.show()

    sys.exit(app.exec())