'''
    Implementation of Spell Checking

    This program implements a spell checker for the words typed out
'''

import sys
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

        menu = self.menuBar()
        toolsMenu = menu.addMenu("Tools")

        #adds the button for the spell check
        spellCheck = QAction("Spell Check", self)
        spellCheck.triggered.connect(self.spellCheck)
        toolsMenu.addAction(spellCheck)

        self.show()

    #spell cheker that highlights misspelled words
    def spellCheck(self):
        #converts everything in the text file to plain text
        text = self.text_box.toPlainText()
        words = text.split()

        #puts a cursor over the text file that goes down each word
        cursor = self.text_box.textCursor()
        cursor.movePosition(1, 0, 1)
        cursor.movePosition(14, 1, 1)

        #red highlight format for mispelled words
        highlight = QTextCharFormat()
        highlight.setBackground(QtGui.QColor("#FFCCCB"))

        #goes through every word in the text file
        for i in words:
            #if the word is found in a dictionary or has an uppercase, number, or symbol character found is set to 1
            found = 0

            #checks for capital letters
            for char in i:
                if char.isupper():
                    found = 1

            #checks for numbers or symbols
            if not i.isalnum() or i.isdigit():
                found = 1
            
            #goes through the dictionary file to check if the current word is present
            if found == 0:
                with open("dictionaries/dictionary.txt", "r") as file1:
                    for j in file1:
                        j = j.strip()
                        if i == j:
                            found = 1
                            break
            
            #goes through the custom dictionary file to check if the current word is present
            if found == 0:
                with open("dictionaries/custom_dictionary.txt", "r") as file2:
                    for k in file2:
                        if i == k:
                            found = 1
                            break
            
            #if the word was not found, mark it
            if found == 0:
                #set the word within the text file to be highlighted
                cursor.setCharFormat(highlight)

            #moves to the next word within the text file
            cursor.movePosition(18, 0, 1)
            cursor.movePosition(5, 0, 1)
            cursor.movePosition(14, 1, 1)
        

if __name__ == '__main__':
    app = QApplication(sys.argv)
   
    window = Window()

    window.show()

    sys.exit(app.exec())