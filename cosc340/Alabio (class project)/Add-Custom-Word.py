'''
    This program implements the ability to add words to the custom dictionary
'''

import sys
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *

class addWindow(QMainWindow):
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

if __name__ == '__main__':
    app = QApplication(sys.argv)
   
    window = addWindow()

    window.show()

    sys.exit(app.exec())