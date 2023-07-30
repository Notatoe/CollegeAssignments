# Noah Morris
# nmorri11

# takes about 30 seconds to run on tesla/hydra machines

import csv
import requests
from bs4 import BeautifulSoup
import matplotlib.pyplot as plt

# puts evreything within the sitesToScrap.csv file into a list
inputFile = list(csv.reader(open('sitesToScrap.csv')))

# books is a list that carries the entirity of each book, dictionary holds every word from each book as well as how many books it appeared in, and
# dictionaries holds a personal dictionary for each book as well as how many times each word appears in that book
books = []
dictionary = {}
dictionaries = []

# for loop that goes through every book 
for i in range(len(inputFile)):
    # uses BeautifulSup and requests to get the text from the website and remove all html tags from it
    books.append(BeautifulSoup(requests.get(inputFile[i][0]).content, 'html.parser').get_text())

    # removes everything outside the *** START ... *** and *** END ... *** messages
    start = books[i].index("*** START OF THE PROJECT GUTENBERG EBOOK ") + len("*** START OF THE PROJECT GUTENBERG EBOOK " + inputFile[i][1] + " ***") + 1
    finish = books[i].index("*** END OF THE PROJECT GUTENBERG EBOOK ")
    books[i] = books[i][start:finish]

    # gets rid of newlines. May not be needed, but it helped me while working on it
    books[i] = books[i].replace("\r\n", ' ')

    # turns every character to lowercase
    books[i] = books[i].lower()

    # list for every char that needs to be removed and a list for every word that needs to be removed
    removeChars = [',','"','.','&','|',':','@',',','<','>','(',')','*','$','?','!','\\','/',';','=','”','“','‘','[',']']
    stopwords = ['ut', '\'re','.', ',', '--', '\'s','cf', '?', ')', '(', ':','\'','\"', '-', '}','â','£', '{', '&', '|', u'\u2014', '', ']' ]

    # for loop that removes each character that needs to be removed
    for j in removeChars:
        books[i] = books[i].replace(j, '')
    
    # — is special because it needs to be replaced with a space
    books[i] = books[i].replace('—', ' ')
    
    # splits the book's words into a list and removes every instance of a stopword
    bookList = books[i].split()
    bookList = [j for j in bookList if j not in stopwords]

    # removes every instance of numbers as a whole word, but not
    bookList = [j for j in bookList if not j.isdigit()]

    # brings the bookList back together into one string
    books[i] = ' '.join(bookList)

    # list and dictionary for every word that appears in the current book
    words = []
    bookDictionary = {}

    # for loop that goes through each word in the book
    for j in bookList:
        # if the word has not already appeared in the book, add it to words and bookDictionary set to 1
        if j not in words:
            words.append(j)
            bookDictionary[j] = 1
        # else it has already appeared and needs to be incremented in the dictionary
        else:
            bookDictionary[j] += 1

    # add the dictionary to the list of book dictionaries
    dictionaries.append(bookDictionary)

    # for loop that goes through each words that appeared in the book
    for j in words:
        # if it is not already in the master dictionary add it and set it to 1
        if j not in dictionary.keys():
            dictionary[j] = 1
        # else increment the number of books the word was in
        else:
            dictionary[j] += 1
    
# list that works like dictionaries but only the words exclusive to that book
uniqueDictionaries = []

# for loop that adds a dictionary of unique words for each of the books
for i in dictionaries:
    tempDictionary = {}
    # checks each word in the current words dictionary to see which words appeard in more than one book
    for j in dictionary.keys():
        # if it is not 1, than it has appeared in multiple books
        if dictionary[j] != 1:
            continue
        # else if it is not in the book then continue
        elif j not in i.keys():
            continue    
        # add the word to the temporary dictionary
        tempDictionary[j] = i[j]
    # add the temporary dictionary as a dictionary for unique words for the current book
    uniqueDictionaries.append(tempDictionary)

# sorts each book's entire dictionary
for i in range(len(dictionaries)):
    dictionaries[i] = sorted(dictionaries[i].items(), key=lambda x: x[1], reverse = True)

# sorts each book's unique dictionary
for i in range(len(uniqueDictionaries)):
    uniqueDictionaries[i] = sorted(uniqueDictionaries[i].items(), key=lambda x: x[1], reverse = True)

# for each book, print the most frequently used unique words
for i in range(len(books)):
    bookName = inputFile[i][1]
    bookFile = open(bookName + ".txt", "w+")
    for j in range(25):
        # if this apostrophe is used, print with quotations instead of apostrophes so the data can be parsed correctly with the checker
        if "'" in uniqueDictionaries[i][j][0]:
            bookFile.write('("' + uniqueDictionaries[i][j][0] + '", ' + str(uniqueDictionaries[i][j][1]) + ")\n")
        else:
            bookFile.write("('" + uniqueDictionaries[i][j][0] + "', " + str(uniqueDictionaries[i][j][1]) + ")\n")
    bookFile.close()

# list to hold data for the two axes of the full dictionary and unique dictionary
fullDictionaryGraphX = []
fullDictionaryGraphY = []
uniqueGraphX = []
uniqueGraphY = []

# adds the values to lists as needed for the each axis with the book chosen being Alice's Adventures in Wonderland
for i in range(25):
    fullDictionaryGraphX.append(dictionaries[2][i][0])
    fullDictionaryGraphY.append(dictionaries[2][i][1])
    uniqueGraphX.append(uniqueDictionaries[2][i][0])
    uniqueGraphY.append(uniqueDictionaries[2][i][1])
    
# sets up the figure as well as the two subplot graphs that will be displayed
# I DON'T KNOW WHY BUT THE GRAPHS OVERLAP SLIGHTLY AND DO NOT CHANGE WITH FIGSIZE
figure, (graph1,graph2) = plt.subplots(1,2, figsize = (3,7))

# inputs the information for the book's full dictionary and sets the graph to have blue bar with a .3 width and flips the x and y axis so the bars are horizontal
graph1.barh(fullDictionaryGraphX, fullDictionaryGraphY, color = 'blue')
graph1.grid(visible = True, color ='black',linestyle ='', linewidth = 0.3)
graph1.invert_yaxis()

# inputs the information for the book's unique dictionary and sets the graph to have blue bar with a .3 width and flips the x and y axis so the bars are horizontal
graph2.barh(uniqueGraphX, uniqueGraphY, color = 'green')
graph2.grid(visible = True, color ='black',linestyle ='', linewidth = 0.3)
graph2.invert_yaxis()

# labels each axis and graph to make it easy to read
graph1.set_xlabel('Frequency')
graph1.set_ylabel('Top 25 Words')
graph1.title.set_text("Graph for all words in Alice's Adventures In Wonderland")
graph2.set_xlabel('Frequency')
graph2.set_ylabel('Top 25 Unique Words')
graph2.title.set_text("Graph for unique words in Alice's Adventures In Wonderland")

# displays the graphs
plt.show()