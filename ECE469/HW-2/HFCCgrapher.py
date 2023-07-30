# HFCC graphs
# Noah Morris

from scipy.io import wavfile
from python_speech_features import mfcc
import matplotlib.pyplot as plt

# Opens the audio file
# FILE NEEDS TO BE MANUALLY SET TO OBTAIN MFCC GRAPH
frequency, sampleArray = wavfile.read("Presses\Space20.wav")

# MFCC features graphed out
MFCC = mfcc(sampleArray, frequency)
MFCC = MFCC.T
plt.matshow(MFCC)
plt.title('MFCC')
plt.show()