
import sys
from PyQt6.QtGui import QAction, QIcon, QPixmap, QColor
from PyQt6.QtWidgets import *

# from previous example - this is our central widget
class Canvas(QLabel):
    def __init__(self):
        super().__init__()

        pixmap = QPixmap(400, 400)
        pixmap.fill(QColor("white"))

        self.setPixmap(pixmap)

        self.prevX = None
        self.prevY = None

        self.penColor = QColor('#000530')

class Window(QMainWindow):
    def __init__(self):
        super().__init__()