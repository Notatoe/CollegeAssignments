'''
    example.py
    Noah Morris

    simple text box application
'''
import sys
from PyQt6.QtGui import QAction, QIcon
from PyQt6.QtWidgets import QFileDialog, QTextEdit, QVBoxLayout, QWidget, QApplication, QMainWindow

class Window(QMainWindow):
    def __init__(self):
        super().__init__()
        
        self.setGeometry(500, 500, 500, 500)

        self.setWindowTitle("Our Example Application")

        #created our cental widget
        central_widget = QWidget()

        #created a vertical box layout
        layout = QVBoxLayout()

        #created a text box
        text_box = QTextEdit

        # add out text box widget to layout
        layout.addWidget(self.text_box)

        # adds the created layout to our central widget
        central_widget.setLayout(layout)

        # adding the entral widget to our QMainWindow
        self.setCentralWidget(central_widget)

        # dislay a status bar
        self.statusBar().showMessage("Important status...")

        # create a File toolbar with save option
        file_menu = self.menuBar().addMenu("File")

        save_icon = QIcon.fromTheme("document-save")
        self.save_action = QAction(save_icon, "Save", self)
        self.save_action.setShortcut("Crtl+S")
        self.save_action.triggered.connect(self.SaveEvent)

        file_menu.addAction(self.save_action)

        def SaveEvent(self):
            buffer = self.text_box.toPlainText()

            file_dialog = QFileDialog(self)

            file_name = file_dialog.getSaveFileName(self, "Save File")

            f = open(fileName[0], 'w')
            f.write(buffer)
            f.close()

if __name__ == '__main__':
    app = QApplication(sys.argv)
   
    window = Window()

    window.show()

    sys.exit(app.exec())